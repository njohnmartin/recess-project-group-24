#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include "string_funcs.h"


#define PORT 2053
 
char busylist[100];

void process_task(char *message, char *response)
{   

	char str[MAX_STRING], token_str[MAX_STRING], result[MAX_STRING], command[16];
	char **tokens;
	char *messageptr = message;
	int bytes_read = 0;
        char senderid[1024];	
	struct timespec start, end;

         printf("---%s",senderid);
	clock_gettime(CLOCK_MONOTONIC, &start);

	sscanf(messageptr, "%s%n", command, &bytes_read);
	messageptr += bytes_read;
	printf("%s",messageptr);

	if (strcmp(command, "double") == 0)
	{
		sscanf(messageptr, "%s%n", str, &bytes_read);
		messageptr += bytes_read;
		string_double(str, result);
		sprintf(response, "String after double: %s\n", result);
	}
	else if (strcmp(command, "rev") == 0)
	{
		sscanf(messageptr, "%s%n", str, &bytes_read);
		messageptr += bytes_read;
		string_reverse(str, result);
		sprintf(response, "String after reverse: %s\n", result);
	}
	else if (strcmp(command, "delete") == 0)
	{
		sscanf(messageptr, "%s%n", str, &bytes_read);
		messageptr += bytes_read;
		
		sscanf(messageptr, "%[^\n]", token_str);
		string_delete(str, messageptr, result);
		sprintf(response, "String after delete: %s\n", result);
	}
	else if (strcmp(command, "replace") == 0)
	{
		sscanf(messageptr, "%s%n", str, &bytes_read);
		messageptr += bytes_read;
		
		sscanf(messageptr, "%[^\n]", token_str);
		string_replace(str, token_str, result);
		sprintf(response, "String after replace: %s\n", result);
	}
	else if (strcmp(command, "encrypt") == 0)
	{
		sscanf(messageptr, "%s%n", str, &bytes_read);
		messageptr += bytes_read;
		string_encrypt(str, result);
		sprintf(response, "String after encrypt: %s\n", result);
	}
	else if (strcmp(command, "decrypt") == 0)
	{
		sscanf(messageptr, "%s%n", str, &bytes_read);
		messageptr += bytes_read;
		string_decrypt(str, result);
		sprintf(response, "String after decrypt: %s\n", result);
	}

	clock_gettime(CLOCK_MONOTONIC, &end);


	time_t now = time(NULL);
	struct tm *dt = localtime(&now);

	FILE *ready_jobs = fopen("ready_jobs.csv", "a");
	fprintf(ready_jobs, "%s ,%s, %s,", "U002", command, result);
	fprintf(ready_jobs, "%ld, ", end.tv_nsec - start.tv_nsec);
	fprintf(ready_jobs, "%02d/%02d/%04d, ", dt->tm_mday, dt->tm_mon+1, dt->tm_year+1900);
	fprintf(ready_jobs, "%02d:%02d:%02d\n", dt->tm_hour, dt->tm_min, dt->tm_sec);
	//fprintf(ready_jobs, "%s", result);
	fclose(ready_jobs);
}



int main()
{
    /* 	servers BLAB
     * 	B - Bind to socket
     * 	L - Listen for connections
     * 	A - Accept connections
     * 	B - Begin talking (recv, send)
     */

	char message[MAX_STRING], response[MAX_STRING];
        char senderid[1024];	
	int serversock, clientsock, bytes_read;
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

	while (1)
	{
		struct sockaddr_in client_addr;
        // Accept Connections
		client_length = sizeof(client_addr);
		clientsock = accept(serversock, (struct sockaddr *)&client_addr, &client_length);
                  
       // Begin talking now
		bzero(message, MAX_STRING);
		

	    // recv(clientsock, senderid, strlen(senderid), 0);
		bytes_read = recv(clientsock, message, MAX_STRING - 1, 0);


        // printf("\n\nUser ID is...%s",senderid);
                
	       
	
		char *tasks[24];

		int count = string_split(message, ";", tasks);
		printf("\n\nReceived %d commands.\n", count);

		for (int i = 0; i < count; ++i)
		{
			printf("Processing task %d: %s\n", i+1, tasks[i]);
			bzero(response, MAX_STRING);
			process_task(tasks[i], response);
			send(clientsock, response, strlen(response), 0);
			printf("Done sir\n");
		}

		//printf("done.\n");
		send(clientsock, "done\n", 5, 0);


		//close(clientsock);
	}

}
