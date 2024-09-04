#include "../include/lem-ipc.h"

static void
print_team_spec()
{
	ft_printf(RED"Team [0]: %d player\n" RESET, data->team_player[0]);
	ft_printf(GRN"Team [1]: %d player\n" RESET, data->team_player[1]);
	ft_printf(YEL"Team [2]: %d player\n" RESET, data->team_player[2]);
	ft_printf(BLU"Team [3]: %d player\n" RESET, data->team_player[3]);
	ft_printf(MAG"Team [4]: %d player\n" RESET, data->team_player[4]);
	ft_printf(CYN"Team [5]: %d player\n" RESET, data->team_player[5]);
	ft_printf(WHT"Team [6]: %d player\n" RESET, data->team_player[6]);
	
}

static void
print_active_team()
{
	int	active_team = 0;
	for(size_t i = 0; i < 9; i++) {
		if (data->team_player[i] != 0)
			active_team++;
	}
	ft_printf("Active player: %d\n", data->player_count);
	ft_printf("Active team :%d\n", active_team);
}

void
print_board()
{
	/* Get number of team alive */
	system("clear");
		
	/* Print board and infos about team */
	print_active_team();
	print_team_spec();
	for(size_t i = 0; i < BOARD_WIDTH; i++) {
		for(size_t j = 0; j < BOARD_HEIGHT; j++) {
			if (j == 0)
				ft_printf("|");
			if (data->board[i][j] < 9)
				ft_printf(" ");
			ft_printf("%d|", data->board[i][j]);
		}
		ft_printf("\n");
	}
	ft_printf("\n");
	
}

t_player_pos
find_player_position(int player_id)
{
	t_player_pos	ret;

	for(ret.width = 0; ret.width < BOARD_WIDTH; ret.width++) {
		for(ret.height = 0; ret.height < BOARD_HEIGHT; ret.height++) {
			if (data->board[ret.width][ret.height] == player_id) {
				return ret;
			}
		}
	}
	return ret;
}

void	
put_player_on_board()
{
	int i = rand() % BOARD_WIDTH;
	int j = rand() % BOARD_HEIGHT;

	sem_wait(player.sem);
	if (data->board[i][j] == 0)
		data->board[i][j] = player.player_id;
	else {
		sem_post(player.sem);
		put_player_on_board();
	}
	sem_post(player.sem);
}
