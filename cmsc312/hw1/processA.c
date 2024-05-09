/* header files */ 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h> /* for exit */
#include <unistd.h> /* for sleep */

/* 
* SHMSZ defined 
* SHMZ specifies the size of shared memory segment
*/
#define SHMSZ     27
int 
main()
{
    char c;
    int *a;
    int shmid;
    key_t key;
    char *shm, *s;
    
    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 5678;

    /*
     * shared memory segment is created using shmget()
     * if creation is successful then shared memory identifier
     * stored in variable shmid is returned. 
     */
    if( (shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0 )
    {
        perror("shmget");
        exit(1);
    }
    
    /*
     * Now we attach the segment to our data space using shmat()
     * if segment attaches then a char pointer is returned stored 
     * in variable shm 
     */
    if( (shm = shmat(shmid, NULL, 0)) == (char *) -1 )
    {
        perror("shmat");
        exit(1);
    }

    /*
     * Now put some things into the shared memory segment 
     * for the other process to read.
     */
    a = (int *) shm;
    *a = 10; 

    /* writes into string shared memory location */
    s = shm;
    shm = "I am Process A\n";
    printf("%s\n", s);
    return 0;

    /*
     * Finally, we wait until the other process 
     * changes the first character of our memory
     * to '*', indicating that it has read what 
     * we put there.
     */
    while( *shm != '*' )
        sleep(1);
    return 0;
} /*program exits*/
