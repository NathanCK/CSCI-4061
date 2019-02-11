# CSCI 4061: Multi-Threaded Web Server

CSci4061 F2018 Assignment 2
login: chanx393 (login used to submit)
date: 11/10/18
name: Kin Nathan Chan, Cyro Chun Fai Chak, Isaac Aruldas (for partner(s))
id: 5330106- chanx393, 5312343 - chakx011, 5139488 - aruld002

This code is acts as a basic multithreaded server whose job is to retrieve data for the clients, and will
then retrieve the data from the disk or the cache .It will also be able to create new threads or kill
existing threads depending on the workload. It is also capable of using the LFU used policy to get rid of
the stuff in the cache when it runs out of space.

### Individual Contribution
Cyro: Initial draft of the application, BugFix, Phase 1 coding, README
Isaac: Initial draft of the application, BugFix, Phase 1 coding, README
Nathan: Final draft of the application, Bug Fix, Phase 1 coding, README

### Getting Started
1. _cp_ the project to your personal repo
2. If `web_server` is in the directory, ignore this step. At the top level inside the directory from OS
Command Primpt: `make`
3. At the Command Prompt: `./webserver <port> <path> <num_dispatcher> <num_worker> <
dynamic_flag> < Quene_length> <cache_entries> ` to run the server.
4. Once the server is running, you can open another terminal at your path to download files with `wget`

## Code Explanation
The main function runs first. It will collect the required parameters detailing the , port_num,
num_dispatcher, num_workers , dynamic_flag , queue_length and cache_size. The code also checks the
number ports, number of dispatcher threads , number of worker threads as well as the length of the
queue and makes sure that the values given are valid .the code will then create and then detaches the
required dispatcher threads from the main thread
The worker thread when it gets the lock is responsible for checking the queue for unattended request.
The code will check if the request is already present in the cache present using the getCacheIndex()
function. The get cache index function will return the given cache index if already present. Then it will
retrieve the file from the cache. Else, it will have to automatically retrieve the code on its own using the
read From Disk function. If it cannot find the code at all, it will simply return an error .The code will
record the time taken to retrieve the code, either from the hard disk or from the cache memory itself.
Then the code will output the results in the terminal as well as the log file that is created to store the
results of what has been done. The worker thread will also add the retrieved data into the cache then it
sends the data into the path.
 
The code will have the dispatch thread, whose job is to receive the request from the client and to add it
to the queue. The code will then form a connection. The code will get the request from the client and
will then store it in the buffer filename. The code will then use the get request to collect the data from
the client. The code will then add the request into the queue for the worker thread to use to work on.
 
### Extra Credit 
The cache is used so that the code does not need to read previous request from disk. The cache we use
implements the least recently used scheme to remove cache entries when the cache becomes full. It is
implemented in the get cache index function.
The code will then create the dynamic pool thread which it will use to kill the unnecessary threads which
are not doing enough work. It can also create new threads to help reduce the workload within the limits
set by the parameter of the main function. It waits for half a second for the other threads to start up.
The code will then wait until it can get the Lock and will try to calculate the usage of the individual
threads with respect to the average thread usage. Threads that are utilized less than 10 % of the average
usage will be discarded as they are no longer need for the job. If there are threads which are at 90% of
the average usage the code the dynamic boss fire up more threads by the number of active workers
minus the threads size goal or the threads size goal minus the number of active workers.
