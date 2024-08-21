#include "../include/lem-ipc.h"

int	main()
{
	t_data	data;
	short	area[64];

	ft_memset(area, 0, sizeof(short) * 64);

	data.sem = init_sem();
	data.shm_id = init_shm();
	data.msgq = init_msgq();

	if (data.sem == NULL || data.shm_id == -1 || data.msgq == 0)
		return clear_ipcs(data.sem, data.shm_id, data.msgq);

	//Do some stuff
	
	return clear_ipcs(data.sem, data.shm_id, data.msgq);

	return	0;
}
