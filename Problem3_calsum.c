#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
 
#define NUM_THREADS 2
#define N 10000
long long sum = 0;
long long subsum[NUM_THREADS];

// matrix multiplication: c = a * b;
void calsum()
{
  int i=1;
  for(i=1;i<=N;i++)
  {
    sum+=i;
    usleep(100);
  }
}
// Thread function
// Each thread calculates the summation over (N / NUM_THREADS) numbers
// For example, if N = 10 and NUM_THREADS = 2
// then thread 0 calculates the sum of [1 2 3 4 5]
// and thread 1 calcualtes the sum of [6 7 8 9 10]
void* thread_function(void* argument) {
// ****** Implement this function *******
  long long token = N / NUM_THREADS;
  // printf("token : %lld\n", token);
  long long  th_num = *((int*) argument);
  printf("thread %lld : add %lld to %lld\n", th_num, (th_num*token)+1, (th_num+1)*token);
  long long  j = (th_num * token) + 1;
  subsum[th_num] = 0;
  for(; j<=(th_num+1) * token; j++){
    subsum[th_num] += j;
    usleep(100);
  }
  sum += subsum[th_num];

  return NULL;
}

// Creates threads
void calsum_MultiThread()
{
 // ****** Implement this function *******
  pthread_t threads[NUM_THREADS];
  int init_value[NUM_THREADS];
  int thr_id;
  int result_code;
  unsigned index;

  for (index = 0; index < NUM_THREADS; index++) {
    init_value[index] = index;

    // Creating a thread with parameters
    thr_id = pthread_create(&threads[index], NULL, thread_function, &init_value[index]);
    assert(!thr_id);
  }

  for (index = 0; index < NUM_THREADS; index++) {
    // block until ith thread completes
    result_code = pthread_join(threads[index], NULL);
    assert(!result_code); // if error_code (non-zero value) returned than terminate.
  }

}

int main(int argc, char** argv) {
  float uSec_s, uSec_m;
  long long sum_s, sum_m;
  time_t start_t, end_t;

  // single thread
  start_t = clock();
  calsum();
  sum_s = sum;
  end_t = clock();
  uSec_s = 1000000*(float)(end_t - start_t)/CLOCKS_PER_SEC;
  
  sum = 0;

  // multi thread
  start_t = clock();
  calsum_MultiThread();
  sum_m = sum;
  end_t = clock();
  uSec_m = 1000000*(float)(end_t - start_t)/CLOCKS_PER_SEC;
  

  printf("Single: sum = %lld\t%f\n", sum_s,uSec_s);
  printf("Multip: sum = %lld\t%f\n", sum_m,uSec_m);
}


