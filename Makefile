SERVER_OBJS	= string_funcs.o server.o priority_queue.o
CLIENT_OBJS = client.o
CC 		= gcc
FLAGS	= -g -c -Wall
LFLAGS	= 

all: server client

	
server: $(SERVER_OBJS) 
	$(CC) -g $(SERVER_OBJS) -o server $(LFLAGS)

client: $(CLIENT_OBJS)
	$(CC) -g $(CLIENT_OBJS) -o client $(LFLAGS)

string_funcs.o: string_funcs.c string_funcs.h
	$(CC) $(FLAGS) string_funcs.c 

server.o: server.c
	$(CC) $(FLAGS) server.c 

priority_queue.o: priority_queue.c priority_queue.h
	$(CC) $(FLAGS) priority_queue.c 

client.o: client.c
	$(CC) $(FLAGS) client.c


clean:
	rm -f $(OBJS) server client