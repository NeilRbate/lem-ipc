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

/* For atexit */
#include <stdlib.h>
#include <assert.h>

/* For Signal */
#include <signal.h>

//*******DEFINE ZONE******

#define PLAYER_MAX	60

#define	SEM_KEY		"/SEM_KEY\0"

#define	MSGQ_KEY	"/MSG_KEY\0"
#define	MSGQ_SIZE	1024
#define	MSGQ_COUNT	32

#define	SHM_KEY		"/SHM_KEY\0"
#define	SHM_SIZE	sizeof(t_data)

#define	SUCCESS		0x000
#define	FAILURE		0xfff

//*******PROTO ZONE*******

typedef struct {

	int	shm_fd;
	short	player_count;
	short	team_player[9];

} t_data;

typedef struct {
	int	player_id;
	int	team_id;
	int	is_first;
	sem_t	*sem;
	mqd_t	msgq;
	struct mq_attr	msgq_attr;
} t_player;


extern t_data	*data;
extern t_player player;

/*
 * Init IPC semaphoreand return sem_t struct
 */
sem_t
*init_sem();

/*
 * Init IPC shared memory, if it already exist, return it's ID
 * Return NULL on error;
 */
t_data
*init_shm();

/*
 * Init IPC msgq, if it already existm return it's ID
 * Return -1 on error;
 */
int
init_msgq();


/*
 * Clear IPC shared memory and semaphore, exit if fail
 */
void
clear_ipcs();


/*
 * Game routine
 */
void	
start_routine();


#endif
