#include "../include/lem-ipc.h"

void
start_routine()
{
	put_player_on_board();
	while(loop){
		sleep(1);
		sem_wait(player.sem);
		if (data->is_end == IS_END)
			break;
		if (player.is_first == IS_FIRST) {
			print_board();
		}
		mouv();
		sem_post(player.sem);
	}
	return;
}
