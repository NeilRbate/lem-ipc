#include "../include/lem-ipc.h"

void
print_board()
{
	//system("clear");
	int	active_team = 0;
	for(size_t i = 0; i < 9; i++) {
		if (data->team_player[i] != 0)
			active_team++;
	}
		
	ft_printf("Active player: %d, Active Team: %d\n", 
			data->player_count, active_team);
	for(size_t i = 0; i < BOARD_WIDTH; i++) {
		for(size_t j = 0; j < BOARD_HEIGHT; j++) {
			if (j == 0)
				ft_printf("|");
			if (data->board[i][j] < 9)
				ft_printf(".");
			ft_printf("%d|", data->board[i][j]);
		}
		ft_printf("\n");
	}
	ft_printf("\n");
	
}

void	
start_routine()
{
	while(loop){
		sleep(1);
		sem_wait(player.sem);
		if (data->is_end == IS_END)
			break;
		if (player.is_first == IS_FIRST) {
			print_board();
		}
		else
			ft_printf("I'm player [%d]\n", player.player_id);
		sem_post(player.sem);
	}
	return;
}
