#include "../include/lem-ipc.h"

static void
print_team_color(int i, int j, int id) 
{
	if (j == 0)
		ft_printf("|");
	if (id == 0) {
		ft_printf("   |", data->board[i][j]);
		return;
	}
	switch(get_player_team(id)) {
		case 0:
			ft_printf(RED);
			break;
		case 1:
			ft_printf(GRN);
			break;
		case 2:
			ft_printf(YEL);
			break;
		case 3:
			ft_printf(BLU);
			break;
		case 4:
			ft_printf(MAG);
			break;
		case 5:
			ft_printf(CYN);
			break;
		case 6:
			ft_printf(WHT);
			break;
	}
	ft_printf(")*(" RESET, data->board[i][j]);
	ft_printf("|");
}

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

int
get_player_team(int player_id)
{
	for(size_t i = 0; i < 7; i++) {
		for(size_t j = 0; j < 60; j++) {
			if (data->team_id[i][j] == player_id)
				return i;
		}
	}
	return 66;
}

void
del_team_player()
{
	for(size_t i = 0; i < 60; i++) {
		if (data->team_id[player.team_id][i] == player.player_id) {
			data->team_id[player.team_id][i] = 0;
			break;
		}
	}
}

void
add_team_player()
{
	for(size_t i = 0; i < 60; i++) {
		if (data->team_id[player.team_id][i] == 0) {
			data->team_id[player.team_id][i] = player.player_id;
			break;
		}

	}
}

void
print_board()
{
	/* Get number of team alive */
		
	/* Print board and infos about team */
	print_team_spec();
	for(size_t i = 0; i < BOARD_WIDTH; i++) {
		for(size_t j = 0; j < BOARD_HEIGHT; j++) {
			print_team_color(i, j, data->board[i][j]);
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
