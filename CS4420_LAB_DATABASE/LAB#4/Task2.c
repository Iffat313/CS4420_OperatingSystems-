#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function( void *ptr );

main() {
    pthread_t thread1, thread2; //created two instances/objects of the struct thread
    char *message1 = "Thread 1"; //message1 is a pointer to a char
    char *message2 = "Thread 2"; //message2 is a pointer to a char
    int iret1, iret2; //created two variables fo an int type

    /* Create independent threads each of which will execute function */
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void*) message1); //intialized a int variable to hold the retruning int value from the the pthread_create() to create or start a new thread
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void*) message2); //intialized a int variable to hold the retruning int value from the the pthread_create() to create or start a new thread

	// use pthread_join() function to wait for the selected thread to finish and to grab the return value of the thread from the single function to which the thread runs on (which is the very same function of the third parameter of the pthread_create() function)
    //this function waits for the selected thread (in the arg) to finish
    /*
    pthread_join(first parameter is the instance of the thread struct or the selected thread were waiting on to finish,
    the second parameter is us grabbing the returning pointer from the void* function we created to which the thread will run on, the very same function that is used in the third arg of thread_create() )
    To add on, this second parameter is considered as the return value for thread we created
    */
    void* Return_Value_Thread;
    pthread_join(thread1, &Return_Value_Thread);

    // do the same for thread2
    pthread_join(thread2, &Return_Value_Thread);

	// print: the return value of each thread
  printf("return value of first thread: %s\n", message1);
  printf("return value of second thread: %s\n", message2);

    return(0);
}

void *print_message_function( void *ptr ) {
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
}
