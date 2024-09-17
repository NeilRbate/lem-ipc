#ifndef __LEM_IPC__
#define __LEM_IPC__


/*******INCLUDE ZONE*******/

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

/* For rand */
#include <time.h>

/*******DEFINE ZONE******/

#define PLAYER_MAX	60
#define	BOARD_WIDTH	16
#define	BOARD_HEIGHT	16

#define	SEM_KEY		"/SEM_KEY\0"

#define	MSGQ_SIZE	32
#define	MSGQ_COUNT	8

#define	SHM_KEY		"/SHM_KEY\0"
#define	SHM_SIZE	sizeof(t_data)

#define	SUCCESS		0x000
#define	FAILURE		0xfff

#define IS_FIRST	0
#define IS_END		1

#define RESET		"\x1B[0m"
#define RED		"\x1B[31m"
#define GRN		"\x1B[32m"
#define YEL		"\x1B[33m"
#define BLU		"\x1B[34m"
#define MAG		"\x1B[35m"
#define CYN		"\x1B[36m"
#define WHT		"\x1B[37m"

/*******PROTO ZONE*******/

static const char MSGQ_KEY[7][9] = { "/MSGKEY0", "/MSGKEY1","/MSGKEY2"
	, "/MSGKEY3","/MSGKEY4", "/MSGKEY5","/MSGKEY6"};

/* Use to stock array content between player */
typedef struct {
	int left;
	int right;
	int up;
	int down;
} t_player_around;

/* Use for return value to get player position */
typedef	struct {
	int	width;
	int	height;
} t_player_pos;

/* Struct for player data, each player have is own */
typedef struct {
	int		player_id;
	int		team_id;
	int		is_first;
	int		im_alive;
	struct		mq_attr	msgq_attr;
	sem_t		*sem;
	mqd_t		msgq;
	t_player_around	around;
	t_player_pos	nearest_target;
} t_player;

/* SHM data structure, each player can access it */
typedef struct {

	int		shm_fd;
	int		is_end;
	int		is_start;
	short		player_count;
	short		team_player[7];
	short		board[BOARD_WIDTH][BOARD_HEIGHT];
	short		team_id[7][60];

} t_data;

/* Global variable */
extern t_data	*data;
extern t_player player;
extern volatile sig_atomic_t loop;

/*
 * Init IPC semaphore and return sem_t struct
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


/* Game routine */
void	
start_routine();

/* Tool who put player on board using rand placement */
void	
put_player_on_board();

/* Tool to fin position of player on the board */
t_player_pos
find_player_position(int player_id);

/* Tool used to print game board and some usefull informations */
void
print_board();

/* Delete player ID on is team */
void
del_team_player();

/* Add player ID on is team */
void
add_team_player();

/* Get team number of player */
int
get_player_team(int player_id);

/* Check if IPC is alive and if it can mouv, do mouv depend on msgq*/
int
mouv();

/* Find nearest target from player pos
 * Return target ID or -1 if no target is on board 
 * */
int
find_nearest_target();

/* Return number of active team, use to define when game start */
int
get_active_team();

/* Clear position of player on data->board */
void
clear_player_position();

/* Create ID for new player */
int
get_new_player_id();


#endif
