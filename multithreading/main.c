#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

int fib(intptr_t *x)
{
    if(*x <= 1)
    {
	return 1; 
    } 

    intptr_t a = *x-1;
    intptr_t b = *x-2; 

    return fib(&a) + fib(&b); 
}

void* multithread_fib(void *arg)
{
    void* finished = (void*)!0;

    int result = fib((intptr_t *)arg);

    printf("Fibonacci: %d\n", result);
    
    finished = (void*)1;

    return finished;
}

int main()
{
    intptr_t value = 10;
    pthread_t thread_t;
    pthread_create(&thread_t, NULL, multithread_fib, &value); 
    pthread_join(thread_t, NULL);

    return 0;
}
