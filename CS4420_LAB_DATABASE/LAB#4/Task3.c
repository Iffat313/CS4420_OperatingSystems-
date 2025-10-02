#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *functionC();

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

main() {
    int rc1, rc2;
    pthread_t thread1, thread2;
    /* Create independent threads each of which will execute functionC */
    if((rc1=pthread_create( &thread1, NULL, functionC , NULL))) {
        printf("Thread creation failed: %d\n", rc1);
    }
    if((rc2=pthread_create( &thread2, NULL, functionC , NULL))) {
        printf("Thread creation failed: %d\n", rc2);
    }
    pthread_join(thread1 , NULL);
    pthread_join(thread2 , NULL);
    return(0);
}
void *functionC() {
/*
- pthread_mutex_lock&unlock are expecting a pointer to a mutex or a variable of type pthread_mutex_t.
- Thus, the parameter of the functions stated above require the memory address so they can directly the mutex in order to fit the definition of a pointer
- Keep in mind, that this void *functionC() only has access to the variables that are within it's scope. In other words,
the vairables in main() are local scope (meaning only accessible) in the main() and not in this function. YOu can see This
function uses counter as evidence of this and therefor it only makes sense to use mutex1 is some manner here to fill the blank
*/

    pthread_mutex_lock(&mutex1);
    counter++;
    printf("Counter value: %d\n",counter);
    pthread_mutex_unlock(&mutex1);
}
