#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
 
#define NUM_THREADS 2
#define N 1e4
long long sum = 0;


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



  
  return NULL;
}

// Creates threads
void calsum_MultiThread()
{
 // ****** Implement this function *******




}

int main(int argc, char** argv) {
  float uSec_s, uSec_m;
  long long sum_s, sum_m;
  time_t start_t, end_t;

  // single thread
  start_t = clock();
  calsum();sum_s = sum;
  end_t = clock();
  uSec_s = 1000000*(float)(end_t - start_t)/CLOCKS_PER_SEC;
  

  sum = 0;
  // multi thread
 // start_t = clock();
 // calsum_MultiThread();sum_m = sum;
 // end_t = clock();
 // uSec_m = 1000000*(float)(end_t - start_t)/CLOCKS_PER_SEC;
  

  printf("Single: sum = %lld\t%f\n", sum_s,uSec_s);
 // printf("Multip: sum = %lld\t%f\n", sum_m,uSec_m);
}


