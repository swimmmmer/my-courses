/*header files*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ     27
int
main()
{
    int shmid;
    key_t key;
    char *shm, *s;
    int c;
    /*
     * We need to get the segment named
     * "5678", created by the server.
     */
    key = 5678;
    /*
     * Locate the segment.
     */
    if( (shmid = shmget(key, SHMSZ, 0666)) < 0 )
    {
        perror("shmget");
        exit(1);
    }
    /*
     * Now we attach the segment to our data space.
     */
    if( (shm = shmat(shmid, NULL, 0)) == (char *) -1 )
    {
        perror("shmat");
        exit(1);
    }

    /*
    Attach integer shared memory segment 
    */
    if ( (c = shmat(shmid, NULL, 0)) == (int *) -1 )
    {
        perror("shmat");
        exit(1);
    }

    /*
     * Now read what the server put in the memory.
     */
    for( s = shm; *s != (char) NULL; s++ )
        putchar(*s);
    putchar('\n');

    /* waits for process B to write integer 
    shared memory location 
    */
    while(*shm != 20) {
        sleep(1);
    }

    /*
    writes into string memory location */
    s = shm;
    s = "I am Process C\n";
    printf("%s\n", s);
    return 0;

    /* writes 20 into shared memory location when completed */
    *c = 30;

    /*
     * Finally, change the first character of the 
     * segment to '*', indicating we have read 
     * the segment.
     */
    *shm = '*';
    return 0;
}