#include "../include/lem-ipc.h"

t_data *data;
t_player player;
volatile sig_atomic_t loop = 1;


void	signalHandler(int _)
{
	/* Signal endler, here to execute atexit() */
	(void)_;
	loop = 0;
	if (player.is_first == IS_FIRST)
		data->is_end = IS_END;
	if (player.sem)
		sem_post(player.sem);
}

void	print_usage()
{
	ft_putstr_fd("lem-ipc invalid usage\n", 1);
	ft_putstr_fd("use: ./lem-ipc [team]\n", 1);
	ft_putstr_fd("team need to be a valid number between [0-6]\n", 1);
}

int	main(int argc, char **argv)
{
	if (argc != 2 || ft_strlen(argv[1]) > 1 
			|| !ft_isdigit(argv[1][0])
			|| ft_atoi(argv[1]) > 6) {
		print_usage();
		exit(EXIT_FAILURE);
	}
	
	player.team_id = ft_atoi(argv[1]);

	/* Catch return and execute clear_ipcs function */
	int cr = atexit(clear_ipcs);
	assert(cr == 0);

	/* Catch signal to execute clear_ipcs on ctrl + * */
	signal(SIGINT, signalHandler);
	signal(SIGQUIT, signalHandler);

	srand(time(NULL));

	/* Init data */
	data = init_shm();

	/* Start game routine */
	start_routine();
	
	return	0;
}
