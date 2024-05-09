#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <fcntl.h>
 
#define SIZE 20
 
typedef struct {
    int user_id;
    int byte_size;
    struct timespec time_insert;
    struct timespec time_dequeue;
} print_job_t;

typedef int buffer_t;
print_job_t* buffer;
int num_jobs_consumed;
int* num_jobs_produced;
int* buffer_index;
int segment_id, segment_id1, segment_id2, segment_id3, segment_id4, segment_id5, segment_id6;
int* producers_done;
int num_prod;
double total_wait;

pthread_mutex_t* buffer_mutex;
/* initially buffer will be empty.  fullsem
   will be initialized to buffer SIZE, which means
   SIZE number of producer threads can write to it.
   And emptysem will be initialized to 0, so no
   consumer can read from buffer until a producer
   thread posts to emptysem */
sem_t* fullsem;  /* when 0, buffer is full */
sem_t* emptysem; /* when 0, buffer is empty. Kind of
                    like an index for the buffer */
 
 
 
void insertbuffer(print_job_t value) {
     if (*buffer_index < SIZE) {
        *(buffer + (*buffer_index)) = value; 
        (*buffer_index)++;
        
    } else {
        printf("Buffer overflow\n");
    }
}
 
print_job_t dequeuebuffer() {
    if (*buffer_index > 0) {
        (*buffer_index)--;
        return *(buffer + *buffer_index);
    }
    else {
        printf("Buffer underflow\n");
        return;
    }
    
}
 
 
void *producer() {
    srand(getpid());
    int num_jobs = rand() % 20;
    print_job_t job;
    buffer_t byte_size;
    int i = 0;
    //printf("Producer %d (%d) with jobSize = %d\n", pid, num, jobSize);
    while (i++ < num_jobs) {
        sleep(0.5);
        byte_size = (rand() % (1000 - 100 + 1)) + 100;
        job.byte_size = byte_size;
        int user_id = getpid();
        job.user_id = user_id;
        sem_wait(fullsem); // sem=0: wait. sem>0: go and decrement it
        /* possible race condition here. After this thread wakes up,
           another thread could aqcuire mutex before this one, and add to list.
           Then the list would be full again
           and when this thread tried to insert to buffer there would be
           a buffer overflow error */
        pthread_mutex_trylock(buffer_mutex); /* protecting critical section */
        clock_gettime(CLOCK_REALTIME, &job.time_insert);
        insertbuffer(job);
        (*num_jobs_produced)++;
        printf("Producer %d added %d to buffer\n", user_id, byte_size);
        pthread_mutex_unlock(buffer_mutex);
        sem_post(emptysem); // post (increment) emptybuffer semaphore
        
        
        
    }
    (*producers_done)++;
}
 
void *consumer(void *thread_n) {
    print_job_t value;
    
    while (*producers_done != num_prod || *buffer_index != 0) {
        sem_wait(emptysem);
        /* there could be race condition here, that could cause
           buffer underflow error */
        pthread_mutex_trylock(buffer_mutex);
        value = dequeuebuffer();
        num_jobs_consumed++;
        printf("Consumer %u dequeue %d, %d from buffer\n", (unsigned int) pthread_self(), value.user_id, value.byte_size);
        sleep(value.byte_size * 0.01);
        clock_gettime(CLOCK_REALTIME, &value.time_dequeue);
        pthread_mutex_unlock(buffer_mutex);
        sem_post(fullsem); // post (increment) fullbuffer semaphore
        total_wait += ( value.time_dequeue.tv_sec - value.time_insert.tv_sec ) + (double)( value.time_dequeue.tv_nsec - value.time_insert.tv_nsec ) / (double)1000000000L;
        
   }
    pthread_exit(0);
}
 

void sigHandler (int sig) {
    pthread_mutex_destroy(buffer_mutex);
    //sem_destroy(fullsem);
    //sem_destroy(emptysem);

    shmdt(buffer);
    shmctl(segment_id, IPC_RMID, NULL);

    shmdt(buffer_index);
    shmctl(segment_id1, IPC_RMID, NULL);

    shmdt(buffer_mutex);
    shmctl(segment_id2, IPC_RMID, NULL);

    //shmdt(fullsem);
    //shmctl(segment_id3, IPC_RMID, NULL);

    //shmdt(emptysem);
    //shmctl(segment_id4, IPC_RMID, NULL);

    shmdt(producers_done);
    shmctl(segment_id5, IPC_RMID, NULL);

    shmdt(num_jobs_produced);
    shmctl(segment_id6, IPC_RMID, NULL);

    sem_close(fullsem);
    sem_close(emptysem);

    sem_unlink("/fullsem");
    sem_unlink("/emptysem");

    exit(0);
}

int main(int argc, char* argv[]) {
    struct timespec time_start, time_end;
    double total_execution;

    num_prod = atof(argv[1]);
    int num_cons = atof(argv[2]);
    signal(SIGINT, sigHandler);

    clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);
    

    


    segment_id = shmget(5781, SIZE*sizeof(print_job_t*), IPC_CREAT | 0600);
    /** attach the shared memory segment */
    buffer = (print_job_t *) shmat(segment_id, NULL, 0);

    // shared memory for buffer_index
    segment_id1 = shmget(5782, sizeof(int*), IPC_CREAT | 0600);
    /** attach the shared memory segment */
    buffer_index = (int *) shmat(segment_id1, NULL, 0);

    // shared memory for buffer_mutex
    segment_id2 = shmget(5783, sizeof(pthread_mutex_t*), IPC_CREAT | 0600);
    /** attach the shared memory segment */
    buffer_mutex = (pthread_mutex_t*) shmat(segment_id2, NULL, 0);

     // shared memory for fullsem   
    //segment_id3 = shmget(5784, sizeof(sem_t*), IPC_CREAT | 0600);
    /** attach the shared memory segment */
    //fullsem = (sem_t*) shmat(segment_id3, NULL, 0);

    // shared memory for emptysem
    //segment_id4 = shmget(5785, sizeof(sem_t*), IPC_CREAT | 0600);
    /** attach the shared memory segment */
    //emptysem = (sem_t*) shmat(segment_id4, NULL, 0);

    // shared memory for num_prod
    segment_id5 = shmget(5786, sizeof(int*), IPC_CREAT | 0600);
    /** attach the shared memory segment */
    producers_done = (int*) shmat(segment_id5, NULL, 0);

    // shared memory for num_prod
    segment_id6 = shmget(5787, sizeof(int*), IPC_CREAT | 0600);
    /** attach the shared memory segment */
    num_jobs_produced = (int*) shmat(segment_id6, NULL, 0);

    fullsem = sem_open("/fullsem", O_CREAT, 0600, SIZE);
    emptysem = sem_open("/emptysem", O_CREAT, 0600, 0);

    

 


    total_wait = 0;
    *buffer_index = 0;
    num_jobs_consumed = 0;
    *num_jobs_produced = 0;
    *producers_done = 0;
    
    int i;
 
    pthread_mutex_init(buffer_mutex, NULL);
    /*sem_init(fullsem, // sem_t *sem
             1, // int pshared. 0 = shared between threads of process,  1 = shared between processes
             SIZE); // unsigned int value. Initial value
    sem_init(emptysem,
             1,
             0);
     fullsem is initialized to buffer size because SIZE number of
       producers can add one element to buffer each. They will wait
       semaphore each time, which will decrement semaphore value.
       emptysem is initialized to 0, because buffer starts empty and
       consumer cannot take any element from it. They will have to wait
       until producer posts to that semaphore (increments semaphore
       value) */
    

    for (i = 0; i < num_prod; i++) { // creating the producer process
        int pid = fork();
        if(pid == 0) {
            producer();
            exit(0);
        }
    }

    pthread_t thread[num_cons];
    int thread_numb[num_cons];

    for (i = 0; i < num_cons; i++) {
        thread_numb[i] = i;
        // playing a bit with thread and thread_numb pointers...
        pthread_create(&thread[i], // pthread_t *t
                       NULL, // const pthread_attr_t *attr
                       consumer, // void *(*start_routine) (void *)
                       &thread_numb[i]);  // void *arg
    }
 
    //for (i = 0; i < numCon; i++)
       // pthread_join(thread[i], NULL);

    int status;
    for(i = 0; i < num_prod; i++) {
        wait(&status);
    }  

    while (*buffer_index != 0) {

    }
    //sleep(10);

    for(i = 0; i < num_cons; i++) {
        pthread_cancel(thread[i]);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &time_end);

    total_execution = ( time_end.tv_sec - time_start.tv_sec ) + (double)( time_end.tv_nsec - time_start.tv_nsec ) / (double)1000000000L;
    double average_wait = total_wait / *num_jobs_produced;
    printf("Total number of jobs produced was %d\n", *num_jobs_produced);
    printf("Total number of jobs consumed was %d\n", num_jobs_consumed);
    printf("Total execution time of the program is %f seconds.\n", total_execution);
    printf("Average waiting time for the jobs is %f seconds.\n", average_wait);

    pthread_mutex_destroy(buffer_mutex);
    //sem_destroy(fullsem);
    //sem_destroy(emptysem);

    shmdt(buffer);
    shmctl(segment_id, IPC_RMID, NULL);

    shmdt(buffer_index);
    shmctl(segment_id1, IPC_RMID, NULL);

    shmdt(buffer_mutex);
    shmctl(segment_id2, IPC_RMID, NULL);

    //shmdt(fullsem);
    //shmctl(segment_id3, IPC_RMID, NULL);

    //shmdt(emptysem);
    //shmctl(segment_id4, IPC_RMID, NULL);

    shmdt(producers_done);
    shmctl(segment_id5, IPC_RMID, NULL);

    shmdt(num_jobs_produced);
    shmctl(segment_id6, IPC_RMID, NULL);

    sem_close(fullsem);
    sem_close(emptysem);

    sem_unlink("/fullsem");
    sem_unlink("/emptysem");

 
    return 0;
}