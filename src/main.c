#include "../include/lem-ipc.h"

t_data *data;
t_player player;

void	signalHandler(int _)
{
	/* Signal endler, here to execute atexit() on ctrl-c */
	(void)_;
	ft_printf("signal catch !\n");
	exit(EXIT_FAILURE);
}

int	main()
{
	/* Catch return and execute clear_ipcs function */
	int cr = atexit(clear_ipcs);
	assert(cr == 0);

	/* Catch signal to execute clear_ipcs on close */
	signal(SIGINT, signalHandler);

	/* Init data */
	data = init_shm();

	ft_printf("hello from %d player !\n", player.player_id);

	while(1) {}
	//Do some stuff
	
	return	0;
}
