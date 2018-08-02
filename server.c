#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "string_funcs.h"
#include "priority_queue.h"


#define PORT 2052



void handle_client(int clientsock)
{

	char message[MAX_STRING], response[MAX_STRING];
    char senderid[1024];
    int sender;	
    int bytes_read;
    int pid = getpid();
    
   	// Begin talking now
    recv(clientsock, senderid, 24, 0);
    printf("\n\nUser ID: %s\n", senderid);
	
	sender = get_sender(senderid);
	bzero(message, MAX_STRING);
	bytes_read = recv(clientsock, message, MAX_STRING - 1, 0);

	char *shm;
	int shmid;

	if ((shmid = shmget(pid, MAX_STRING, IPC_CREAT | 0666)) < 0)
		fprintf(stderr, "Err srv shmget\n");

	if ((shm = shmat(shmid, 0, 0)) == (char *) -1)
		fprintf(stderr, "Err serv shmat\n");
    	
    while (strncmp(message, "exit", 4)) { 

		char *tasks[24];

		int count = string_split(message, ";", 0, tasks);
		printf("Received %d commands.\n", count);

		for (int i = 0; i < count; ++i)
		{
			Task t;
			if (make_task(sender, tasks[i], pid, &t)) {
				enqueue_task(t);
			}
		}


		for (int i = 0; i < count; ++i)
		{
			while (*shm != '*')
				sleep(1);

			strcpy(response, shm + 1);
			*shm = '\0';

			send(clientsock, response, strlen(response), 0);
		}

		send(clientsock, "done\n", 5, 0);
		bzero(message, MAX_STRING);
		
		bytes_read = recv(clientsock, message, MAX_STRING - 1, 0);
	}

	close(clientsock);
}


int main()
{
    /* 	servers BLAB
     * 	B - Bind to socket
     * 	L - Listen for connections
     * 	A - Accept connections
     * 	B - Begin talking (recv, send)
     */

	int serversock, clientsock, pid, pid2;
	socklen_t client_length;
	struct sockaddr_in server_addr;

	// create server socket
	serversock = socket(AF_INET, SOCK_STREAM, 0);
	bzero((char *) &server_addr, sizeof(server_addr));
	printf("Starting String Task Server...\n");

	// setup server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	// bind to a port
	if (bind(serversock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		perror("Error: Unable to bind to port");
		exit(1);
	}

   // Listen for connections
	listen(serversock, 5);
	printf("Listening on port %d\n", PORT);



	pid2 = fork();
	if (pid2 < 0) {
		perror("ERROR on fork");
	 	exit(1);
	}

	if (pid2 == 0) {
	 /* This is the child process */		
		process_queue();
		exit(0);
	}

	while (1)
	{
		struct sockaddr_in client_addr;
        // Accept Connections
		client_length = sizeof(client_addr);
		clientsock = accept(serversock, (struct sockaddr *)&client_addr, &client_length);
          
		/* Create child process */
		pid = fork();

		if (pid < 0) {
			perror("ERROR on fork");
		 	exit(1);
		}

		if (pid == 0) {
		 /* This is the child process */
			close(serversock);
			
			handle_client(clientsock);

			exit(0);
		}
		else {
			close(clientsock);
		}        
       

		//close(clientsock);
	}

}
