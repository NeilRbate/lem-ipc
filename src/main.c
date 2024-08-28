#include "../include/lem-ipc.h"

int	main()
{
	t_data	data;
	short	area[64];

	ft_memset(area, 0, sizeof(short) * 64);

	init_shm(&data);
	data.sem = init_sem();
	data.msgq = init_msgq();

	if (data.sem == NULL || data.msgq == 0)
		return clear_ipcs(&data);

	//Do some stuff
	
	return clear_ipcs(&data);

	return	0;
}
