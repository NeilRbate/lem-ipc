#include "../include/lem-ipc.h"

void
print_board()
{
	for(size_t i = 0; i < BOARD_WIDTH; i++) {
		for(size_t j = 0; j < BOARD_HEIGHT; j++) {
			if (j == 0)
				ft_printf("|");
			ft_printf("%d|", data->board[i][j]);
		}
		ft_printf("\n");
	}
	
}

void	
start_routine()
{
	ft_printf("player [%d] in team [%d] is ready !", 
			player.player_id,
			player.team_id);
	while(1){
		if (player.is_first == 1) {
			sem_wait(player.sem);
			print_board();
			sleep(2);
			sem_post(player.sem);
		}
	}
	return;
}
