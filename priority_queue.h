#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct {
	char command[12];
	char taskString[80];
	char taskStrOptions[30];
	char resultStr[1200]; 
	char senderID[12];
	int sender;
	int priority;
	int strlength;
	int pid;
	int linenum;
} Task;

void process_queue();

int make_task(int sender, char *message, int clientsock, Task *t);

int enqueue_task(Task t);

int get_sender(char *senderid);

void get_highest_priority_task(Task *t);

int user_has_jobs_queued(int sender);

#endif