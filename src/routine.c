#include "../include/lem-ipc.h"

void
start_routine()
{
	put_player_on_board();

	sem_wait(player.sem);

	if (get_active_team() > 1 && data->is_start == 0)
		data->is_start = 1;

	sem_post(player.sem);

	while(loop){
		sleep(1);
		sem_wait(player.sem);

		system("clear");

		if (data->is_end == IS_END 
		|| (data->is_start == 1 && get_active_team() == 1)) {
			ft_printf("Team [%d] win !\n", player.team_id);
			sem_post(player.sem);
			break;
		}
		if (player.is_first == IS_FIRST)
			print_board();
		if (player.im_alive == 1)
			mouv();

		sem_post(player.sem);
	}
	return;
}
