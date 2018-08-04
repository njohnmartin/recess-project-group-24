# Recess Project Group24 - String Task Server

## Installation
Download / Clone the project from github 
```
git clone https://github.com/njohnmartin/recess-project-group-24 stringtaskserver
cd stringtaskserver
```

To compile the project, run **make** in the terminal if you have it installed  
```
make
```

OR 
```
gcc -o server server.c string_funcs.c priority_queue.c  
gcc -o client client.c
```  

## Running 
Start the server and leave it running 
```
./server
```

![Run Server](/screenshots/runserver.png?raw=true "Starting the string task server")  

Open any number of client programs in a different terminal
```
./client
```
![Run Client](/screenshots/runclient.png?raw=true "Starting the string task client")  
