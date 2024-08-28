#ifndef __LEM_IPC__
#define __LEM_IPC__


//*******INCLUDE ZONE*******

//Libft proto
#include "../libft/libft.h"

//For all ipc relative stuff

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <mqueue.h>

/* For perror */
#include <stdio.h>
#include <errno.h>



//*******DEFINE ZONE******

#define PLAYER_MAX	60

#define	SEM_KEY		"/SME_KEY\0"

#define	MSGQ_KEY	"/MSG_KEY\0"

#define	SHM_KEY		"/SHM_KEY\0"
#define	SHM_SIZE	sizeof(t_data)

#define	SUCCESS		0x000
#define	FAILURE		0xfff

//*******PROTO ZONE*******

typedef struct {

	int	shm_fd;
	sem_t	*sem;
	mqd_t	msgq;
	short	player_count;

} t_data;


/*
 * Init IPC semaphoreand return sem_t struct
 */
sem_t
*init_sem();

/*
 * Init IPC shared memory, if it already exist, return it's ID
 * Return -1 on error;
 */
int
init_shm(t_data *data);

/*
 * Init IPC msgq, if it already existm return it's ID
 * Return -1 on error;
 */
int
init_msgq();


/*
 * Clear IPC shared memory and semaphore, exit if fail
 * Return 0 on success
 */
int
clear_ipcs(t_data *data);


#endif
