#include "../include/lem-ipc.h"

int
init_shm(t_data *data)
{
	int	fd;
	
	/* Create shared memory map */
	fd = shm_open(SHM_KEY, O_RDWR | O_CREAT, 
			S_IRUSR | S_IWUSR);
	if (fd == -1) {
		perror("lem_ipc error: ");
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

	data->shm_fd = fd;

	return SUCCESS;

failure:

	perror("lem-ipc error: ");
	close(fd);
	exit(EXIT_FAILURE);

	return FAILURE;
}
