#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

int N;

void isPrime(int n);
void *perform_work(void *arguments){
  int index = *((int *)arguments);
  // int sleep_time = 1 + rand() % NUM_THREADS;
  // printf("THREAD %d: Started.\n", index);
  // printf("THREAD %d: Will be sleeping for %d seconds.\n", index, sleep_time);
  // sleep(sleep_time);
  // printf("THREAD %d: Ended.\n", index);

  int i = 0;
  int max = N;
  max = max/2;

  while(i < max){
    isPrime(index);
    i++; index++;
  } 

  return 0;
}

int main(void) {
  pthread_t threads[NUM_THREADS];
  int thread_args[NUM_THREADS];
  int i;
  int result_code;
  int num;

  int T = 0;

  scanf("%d", &N);
  scanf("%d", &T);
  
  //create all threads one by one
  for (i = 0; i < T; i++) {
    //printf("IN MAIN: Creating thread %d.\n", i);
    thread_args[i] = ((N/T)*i + 1);
    result_code = pthread_create(&threads[i], NULL, perform_work, &thread_args[i]);
    //assert(!result_code);
  }

  //printf("IN MAIN: All threads are created.\n");

  for (i = 0; i < T; i++) {
    result_code = pthread_join(threads[i], NULL);
    //printf("IN MAIN: Thread %d has ended.\n", i);
  }

  //printf("MAIN program has ended.\n");
  return 0;
}

void isPrime(int n){
  int i, flag = 0;

    for(i = 2; i <= n/2; ++i){
        if(n%i == 0){
            flag = 1;
            break;
        }
    }

    if (n == 1) {
      printf("1 is neither a prime nor a composite number.\n");
    }else{
        if (flag == 0)
          printf("%d is a prime number.\n", n);
        else
          printf("%d is not a prime number.\n", n);
    }
}