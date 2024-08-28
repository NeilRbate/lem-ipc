#include "../include/lem-ipc.h"

t_data *data;
t_player player;

void	signalHandler(int _)
{
	/* Signal endler, here to execute atexit() on ctrl-c */
	(void)_;
	ft_printf("signal catch !\n");
	clear_ipcs();
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	if (argc != 2 || ft_strlen(argv[1]) > 1 || !ft_isdigit(argv[1][0])) {
		ft_printf("lem-ipc invalid usage\nuse: ./lem-ipc [team]\nteam need to be a valid number between [0-9]\n");
		exit(EXIT_FAILURE);
	}
	
	player.team_id = ft_atoi(argv[1]);

	/* Catch return and execute clear_ipcs function */
	int cr = atexit(clear_ipcs);
	assert(cr == 0);

	/* Catch signal to execute clear_ipcs on close */
	signal(SIGINT, signalHandler);

	/* Init data */
	data = init_shm();

	ft_printf("hello from player[%d] in team [%d] !\n", player.player_id, player.team_id);

	start_routine();
	
	return	0;
}
