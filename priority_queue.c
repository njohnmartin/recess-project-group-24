#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "string_funcs.h"
#include "priority_queue.h"

Task busylist[100];
int user_job_count[100];
char users[100][100];

int busycount = 0;
int usercount = 0;

void delete_line_from_file(char *filename, int linenum)
{
	FILE *temp = fopen("temp.csv", "w");
	FILE *f = fopen(filename, "r");
	char line[1024];
	int currline = 0;

	while (fgets(line, 1023, f) != NULL)  {
		if (currline != linenum)
			fputs(line, temp);

		currline++;
	}

    fclose(f);
    fclose(temp);
    remove(filename);  		// remove the original file 
    rename("temp.csv", filename);           
                
}

void process_queue()
{
	printf("Process Queue process started\n");
	while (1) 
	{
		char line[256];
		int linenum = 0;
		busycount = 0;

		bzero(user_job_count, sizeof(user_job_count));
		sleep(2);

		FILE *waiting_jobs = fopen("waiting_jobs.csv", "r");
		
		while (fgets(line, 255, waiting_jobs) != NULL)  {
			Task t;
			char command[12];
			char taskString[80];
			char taskStrOptions[30];
			char resultStr[1200]; 
			char senderID[12];

			char *tokens[24];

			int count = string_split(line, ",", 0, tokens);
			
			if (count > 1) {
				t.sender = atoi(tokens[0]);
				strcpy(t.senderID, tokens[1]); 
				strcpy(t.command, tokens[2]);
				strcpy(t.taskString, tokens[3]);
				strcpy(t.taskStrOptions, tokens[4]);
				t.priority = atoi(tokens[5]);
				t.pid = atoi(tokens[6]);
				t.strlength = strlen(t.taskString);

				user_job_count[t.sender]++;

			}

		    t.linenum = linenum;
		    busylist[busycount++] = t;
		    linenum++;
		}
		//fprintf(waiting_jobs, "%s", result);
		fclose(waiting_jobs);

		if (busycount > 0) {
			Task t;
			get_highest_priority_task(&t);

			struct timespec start, end;
			char result[MAX_STRING], response[MAX_STRING];

			clock_gettime(CLOCK_MONOTONIC, &start);

			printf("Processing task: %s %s\n", t.command, t.taskString);
			if (strcmp(t.command, "double") == 0)
			{
				string_double(t.taskString, result);
				sprintf(response, "String after double: %s\n", result);
			}
			else if (strcmp(t.command, "rev") == 0)
			{	
				string_reverse(t.taskString, result);
				sprintf(response, "String after reverse: %s\n", result);
			}
			else if (strcmp(t.command, "delete") == 0)
			{	
				string_delete(t.taskString, t.taskStrOptions, result);
				sprintf(response, "String after delete: %s\n", result);
			}
			else if (strcmp(t.command, "replace") == 0)
			{	
				string_replace(t.taskString, t.taskStrOptions, result);
				sprintf(response, "String after replace: %s\n", result);
			}
			else if (strcmp(t.command, "encrypt") == 0)
			{
				string_encrypt(t.taskString, result);
				sprintf(response, "String after encrypt: %s\n", result);
			}
			else if (strcmp(t.command, "decrypt") == 0)
			{	
				string_decrypt(t.taskString, result);
				sprintf(response, "String after decrypt: %s\n", result);
			}

			clock_gettime(CLOCK_MONOTONIC, &end);
			printf("Done\n");

			char *shm; int shmid;
			if ((shmid = shmget(t.pid, MAX_STRING, 0666)) < 0)
				fprintf(stderr, "err pq shmget %d\n", t.pid);

			if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
				fprintf(stderr, "err pq shmat\n");

			strcpy(shm + 1, response);
			*shm = '*';
			

			delete_line_from_file("waiting_jobs.csv", t.linenum);
			

			time_t now = time(NULL);
			struct tm *dt = localtime(&now);

			FILE *ready_jobs = fopen("ready_jobs.csv", "a");
			fprintf(ready_jobs, "%s ,%s, %s,", t.senderID, t.command, result);
			fprintf(ready_jobs, "%ld, ", end.tv_nsec - start.tv_nsec);
			fprintf(ready_jobs, "%02d/%02d/%04d, ", dt->tm_mday, dt->tm_mon+1, dt->tm_year+1900);
			fprintf(ready_jobs, "%02d:%02d:%02d\n", dt->tm_hour, dt->tm_min, dt->tm_sec);
			//fprintf(ready_jobs, "%s", result);
			fclose(ready_jobs);

		}
	}
}

int calculate_priority(Task task)
{
	int priority = 0;
	int length = task.strlength;
	int has_min_length = 1;
	int user_has_most_jobs = 1;

	for (int i = 0; i < busycount; ++i)
	{
		if (length > busylist[i].strlength) {
			has_min_length = 0;
			break;
		}	
	}

	for (int i = 0; i < busycount; ++i)
	{
		if (user_job_count[task.sender] <= user_job_count[busylist[i].sender]) {
			user_has_most_jobs = 0;
			break;
		}	
	}

	if (has_min_length) priority += 1;
	if (user_has_most_jobs) priority += 2;
	if (!strncmp(task.command, "replace", 7)) priority += 3;

	return priority;
}

int enqueue_task(Task t)
{
	
	if (strlen(t.taskString) > 50) {

		time_t now = time(NULL);
		struct tm *dt = localtime(&now);


		FILE *failed_jobs = fopen("failed_jobs.csv", "a");
		fprintf(failed_jobs, "%s, %s, %s, String length longer than 50, ", 
			t.senderID, 
			t.command, 
			t.taskString 
			
		);
		fprintf(failed_jobs, "%02d/%02d/%04d, ", dt->tm_mday, dt->tm_mon+1, dt->tm_year+1900);
		fprintf(failed_jobs, "%02d:%02d:%02d\n", dt->tm_hour, dt->tm_min, dt->tm_sec);
				
		fclose(failed_jobs);

		return 0;
	}

	t.priority = calculate_priority(t);
	user_job_count[t.sender]++;
	
	FILE *waiting_job = fopen("waiting_jobs.csv", "a");
	fprintf(waiting_job, "%d, %s, %s, %s, %s, %d, %d\n", 
		t.sender, 
		t.senderID, 
		t.command, 
		t.taskString, 
		t.taskStrOptions,
		t.priority,
		t.pid
	);
	fclose(waiting_job);
	printf("Queued %s\n", t.command);

	return 1;

}

int make_task(int sender, char *message, int pid, Task *t)
{
	char *tokens[24];
	int count = string_split(message, " ", 3, tokens);
	t->pid = pid;
	t->sender = sender;

	if (count > 0) {
		strcpy(t->command, tokens[0]);
		strcpy(t->taskString, tokens[1]);
		strcpy(t->senderID, users[sender]); 
		t->strlength = strlen(t->taskString);

		
		if (count > 2)
			strcpy(t->taskStrOptions, tokens[2]);
		else
			strcpy(t->taskStrOptions, "NULL");
		

		return 1;
	}

	return 0;
}

int get_sender(char *senderid)
{
	int sender = -1;
	int user_exists = 0;

	for (int i = 0; i < usercount; ++i)
	{
		if (!strcmp(users[i], senderid)) {
			sender = i; 
			user_exists = 1; 
			break;
		}
	}

	if (!user_exists) {
		strcpy(users[usercount], senderid);
		user_job_count[usercount] = 0;
		sender = usercount;
		usercount++;
	}

	return sender;
}


void get_highest_priority_task(Task *t)
{
	int highest = -1;
	int index = -1;

	for (int i = 0; i < busycount; ++i)
	{
		if (highest < busylist[i].priority) {
			highest = busylist[i].priority;
			index = i;
		}	
	}

	*t = busylist[index];

	for (int i = index; i < busycount - 1; ++i)
	{
		busylist[i] = busylist[i + 1];
	}

	busycount--;
}





// int main() 
// {
// 	char *command = "a";
// 	char *str = "wer";
// 	char *stropts = "d";
// 	char *senderid = "U001";

// 	enqueue_task("as", "sdss", "", "U001");
// 	enqueue_task("replace", "sd", "", "U002");
// 	enqueue_task("as", "sdsdsfs", "", "U001");
	
// 	for (int i = 0; i < busycount; ++i)
// 	{
// 		printf("%s %d\n", busylist[i].command, busylist[i].priority);
// 	}
	
// }