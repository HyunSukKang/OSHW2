#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
 
#define NUM_THREADS 2 // number of threads
 
int number = 1;

// Thread function that each thread starts from
void* thread_function(void* argument) {
  pid_t pid = getpid();           // process id
  pthread_t tid = pthread_self(); // thread id
  unsigned int ui_pid = (unsigned int)pid;
  unsigned int ui_tid = (unsigned int)tid;


  int th_num = *((int*) argument); // passed value
  printf("pid: %u, tid: %x, th_num: %d, ", ui_pid, ui_tid, th_num);
 
  return NULL;
}

void* thread_counting(void* argument)
{ // ****** You implement this function ******
  pid_t pid = getpid();           // process id
  pthread_t tid = pthread_self(); // thread id
  unsigned int ui_pid = (unsigned int)pid;
  unsigned int ui_tid = (unsigned int)tid;

  int th_num = *((int*) argument);
  for(; number<30; number++){
    sleep(2);
    printf("pid: %u, tid: %x, th_num: %d, number : %d\n", ui_pid, ui_tid, th_num, number);
  }
  
  return NULL;
}

int main(int argc, char** argv) {
  pthread_t threads[NUM_THREADS];
  int init_value[NUM_THREADS];
  int thr_id;
  int result_code;
  unsigned index;
 
  // create all threads one by one
  for (index = 0; index < NUM_THREADS; index++) {
    init_value[index] = index;
    printf("main: creating thread %d\n", index);

    // Creating a thread with parameters
    // thr_id = pthread_create(&threads[index], NULL, thread_function, &init_value[index]);
    thr_id = pthread_create(&threads[index], NULL, thread_counting, &init_value[index]); // Use this for Problem 1
    assert(!thr_id);
    sleep(1);
  }
 
  for (index = 0; index < NUM_THREADS; index++) {
    // block until ith thread completes
    result_code = pthread_join(threads[index], NULL);
    assert(!result_code); // if error_code (non-zero value) returned than terminate.
  }
 
  exit(EXIT_SUCCESS);
}