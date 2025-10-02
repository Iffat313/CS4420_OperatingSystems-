#include<pthread.h>
#include<stdio.h>
/*

the pthread library is a c library that allows us to create and manage multi-
threaded programs.

2) Provides the following functions:
- pthread_create -> creates or starts a new thread
- pthread_join -> wait for threads to finish. What this function does and it's parameter requirements will be discussed in task2.c
 - stack size, detach state -> THis allows us modify the extra attibutes of a thread


*/



#define NUM_THREADS 5

/*
 1) What is a thread?: Assume that you have a process in your memroy and it's
 using your RAM. Then you fork it to create process 2. At that point of fork
 it is going to clone that image and creare another deep copy.

 With a thread, you may have a single process. WIthin that process, you'll have
 one thread (one line of execution). We can create a number of threads to act like
 worker bees to create tasks at the same time or to comeplete another task as we
 wait for other process to comeplete.

 UNlike forking where you're working with multiple deep copies that are independent
of each other with threads its all in the same shared memory. It should be noted
that you cannot have multiple threads working on the same memory address, instead
you should split it up.
*/
   //What does the * mean in the signature? This function will return a pointer to anything, -
    //This the function that the thread will run on
    //What does the * mean in the paramater? WHen you see void* ... this means the function TAKES a pointer to anything we dont know it yet.
void *PrintHello(void *threadid) //As you can see there is only one single argument in this function
{
    long tid;
    tid = (long)threadid;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    pthread_exit(NULL);
}
int main (int argc, char *argv[])
{
	// create an array of thread struct instances with appropriate length, where each element is an instance of the struct thread.
  pthread_t TSI[NUM_THREADS]; //the array is already intialized of the 5 isnatnce of the struct thread, via the declaration

    long t;
    for(t=0; t<NUM_THREADS; t++){ //the for loop will traverse through the array ensuring each instance is ran through the pthread_create() function and the function on line 38 for the thread to be ran on
        printf("In main: creating thread %ld\n", t);
        // start a new thread and call the appropriate routine with. You need to handle errors.
        //first parameter requires memory address of the object or instance of the struct thread
        //second parameter requires NULL as this goes to the extra unessary attributes of the thread
        //third parameter is function the thread should run on. THis is the function pointer mentioned above
        //fourth parameter is the single argument you pass for the function mentioned in the third parameter.
        int check = pthread_create(&TSI[t], NULL, PrintHello, (void *)t); //pthread_create(....) returns an integer on success, use this info on how to handle errors. Keep in mind this pthread_create() does NOT return the value of a thread, rather the succes or fail value
        if(check != 0){
          printf("Error occured for thread #%ld, will exit", t);
          break;
        }
        pthread_create(&TSI[t], NULL, PrintHello, (void *)t);
        // args of the routine should be cast as (void *)t
    }
    /* Last thing that main() should do */
    pthread_exit(NULL);
}
