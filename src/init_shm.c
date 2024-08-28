#include "../include/lem-ipc.h"

extern t_data	*data;
extern t_player player;

t_data
*init_shm()
{
	int	fd;
	
	/*Try to open existing shared memory */
	fd = shm_open(SHM_KEY, O_RDWR, S_IRUSR | S_IWUSR);
	if (fd != -1) {
		data = mmap(NULL, sizeof(t_data), 
			PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

		if (data == MAP_FAILED)
			goto failure;

		ft_printf("Existing shared memory join !\n");
		ft_printf("data->sem %d\n", data->sem);

		//Sem lock
		sem_wait(data->sem);
		data->player_count++;
		player.player_id = data->player_count;
		sem_post(data->sem);

		return data;
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

	if (data == MAP_FAILED)
		goto failure;

	/* Init semaphore and message queue */
	if ((data->sem = init_sem()) == NULL)
		goto failure;

	if ((data->msgq = init_msgq(data)) == -1)
		goto failure;

	ft_printf("Create new shared memory !\n");

	close(fd);
	sem_wait(data->sem);
	data->player_count++;
	player.player_id = data->player_count;
	sem_post(data->sem);
	return data;

failure:

	perror("shm_init error");
	close(fd);
	exit(EXIT_FAILURE);

	return NULL;
}
