#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int top;
sem_t mutex;
sem_t empty;
sem_t full;

void* producer(){
    int i = 0;
    int e, f;
    do{ 
        sem_wait(&empty);
        sem_wait(&mutex);

        printf("======producer======\n");

        if(top < BUFFER_SIZE){
            int nextp = rand() % 10000;

            buffer[++top] = nextp;
            printf("produced item : %d, current index : %d\n", nextp, top);
        }
        else {
            printf("Buffer is full\n");
        }
        for(int j=0; j<=top; j++){
            printf("buffer[%d] = %d\n", j, buffer[j]);
        }
        
        sem_post(&mutex);
        sem_post(&full);
        
        sem_getvalue(&empty, &e);
        sem_getvalue(&full, &f);

        printf("Current state of semaphores, Empty : %d, Full : %d\n", e, f);

        i++;
        usleep(200);

    } while(i<20);

    return NULL;
}

void* consumer(){
    int i = 0;
    int e, f;
    do{ 
        usleep(170);
        sem_wait(&full);
        sem_wait(&mutex);

        printf("======consumer======\n");
        int nextc;
        if(top>=0){
            nextc = buffer[top--];

            printf("consumed item : %d, current index : %d\n", nextc, top);

        }
        else{
            printf("Buffer is empty\n");
        }
        for(int j=0; j<=top; j++){
            printf("buffer[%d] = %d\n", j, buffer[j]);
        }
        
        sem_post(&mutex);
        sem_post(&empty);
        
        sem_getvalue(&empty, &e);
        sem_getvalue(&full, &f);

        printf("Current state of semaphores, Empty : %d, Full : %d\n", e, f);

        i++;
    } while(i<20);

    return NULL;
}

int main(){
    pthread_t prod, cons;
    int thr_id1, thr_id2;
    int result_code1, result_code2;
    unsigned index;
    int init_value1 = 0;
    int init_value2 = 1;

    top = -1;
    int e;

    sem_init(&mutex, 0, 0);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 10);

    sem_getvalue(&empty, &e);
    printf("initail value of empty : %d\n", e);

    thr_id1 = pthread_create(&prod, NULL, &producer, &init_value1);
    assert(!thr_id1);
    thr_id2 = pthread_create(&cons, NULL, &consumer, &init_value2);
    assert(!thr_id2);

    result_code1 = pthread_join(prod, NULL);
    assert(!result_code1);
    result_code2 = pthread_join(cons, NULL);
    assert(!result_code2);

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}