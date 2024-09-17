#include "../include/lem-ipc.h"

static void
init_player()
{
	sem_wait(player.sem);
	data->player_count++;
	player.player_id = get_new_player_id();
	player.im_alive = 1;
	data->team_player[player.team_id]++;
	add_team_player();
	sem_post(player.sem);
}

t_data
*init_shm()
{
	int	fd;
	
	/*Try to open existing shared memory */
	fd = shm_open(SHM_KEY, O_RDWR, S_IRUSR | S_IWUSR);
	if (fd != -1) {
		/* Shared memory already exist, just get data */
		data = mmap(NULL, sizeof(t_data), 
			PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

		/* Close shm fd */
		close(fd);

		if (data == MAP_FAILED)
			goto failure;
		player.is_first = 1;
		goto exist;
	}

	/* Create shared memory */
	fd = shm_open(SHM_KEY, O_RDWR | O_CREAT, 
			S_IRUSR | S_IWUSR);
	if (fd == -1) {
		perror("shm_open error");
		exit(EXIT_FAILURE);
	}

	/* Set shm size */
	if (ftruncate(fd, sizeof(t_data)) == -1)
		goto failure;
	/* Create mmap to fill on shared memory */
	data = mmap(NULL, sizeof(t_data), 
			PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	/* Close shm fd */
	close(fd);
	if (data == MAP_FAILED)
		goto failure;

	/* Set t_data to 0 */
	ft_memset(data, 0, sizeof(t_data));

exist:
	/* init semaphore and message queue */
	player.sem = init_sem();

	init_msgq();
	
	/* Init player value */
	//if (player.is_first != IS_FIRST)
		init_player();

	return data;

failure:

	perror("shm_init error");
	exit(EXIT_FAILURE);
}
