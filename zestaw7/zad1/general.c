#include <time.h>
#include <stdio.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include "general.h"

void init_queue(struct queue *q, int size) {

    q -> max_size = size;
    q -> current_size = 0;
    q -> front = 0;
    q -> back = 1;
}

int enqueue(struct queue *q, pid_t client_pid) {

    if(q -> current_size >= q -> max_size)
        return -1;

    int position = (q -> back - 1 + q -> max_size) % q -> max_size;
    q -> clients[position] = client_pid;
    q -> back = position;
    q -> current_size++;

    return 0;
}

pid_t dequeue(struct queue *q) {

    if(q -> current_size == 0)
        return -1;

    pid_t result = q -> clients[q -> front];
    q -> front = (q -> front - 1 + q -> max_size) % q -> max_size;
    q -> current_size--;

    return result;
}

void print_time_message(const char *message) {

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    fprintf(stdout, "%ld.%06ld sec. - pid %d: %s", ts.tv_sec, ts.tv_nsec / 1000, getpid(), message);
    fflush(stdout);
}

// Decreases semaphore's value by one (assumes that there is only one semaphore in the whole set)
int sem_decrease(int sem_id) {

    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;

    return semop(sem_id, &buf, 1);
}

// Increases semaphore's value by one (assumes that there is only one semaphore in the whole set)
int sem_increase(int sem_id) {

    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;

    return semop(sem_id, &buf, 1);
}

// Blocks until semaphore's value becomes 0
int sem_wait_for_zero(int sem_id) {

    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 0;
    buf.sem_flg = 0;

    return semop(sem_id, &buf, 1);
}
