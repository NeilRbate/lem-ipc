#include "../include/lem-ipc.h"

static int
id_exist(int id) 
{
	for(size_t i = 0; i < BOARD_WIDTH; i++) {
		for(size_t j = 0; j < BOARD_HEIGHT; j++) {
			if (data->board[i][j] == id)
				return -1;
		}
	}
	return 0;
}

int
get_new_player_id()
{
	int id = rand() % 99;
	if (id_exist(id) == 0)
		return id;
	return get_new_player_id();
}

static void
print_team_color(int i, int j, int id) 
{
	if (j == 0)
		ft_printf("|");
	if (id == 0) {
		ft_printf("   |");
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
	if (data->board[i][j] < 10)
		ft_printf(" ");
	ft_printf("%d " RESET, data->board[i][j]);
	ft_printf("|");
}

static void
print_team_spec()
{
	ft_printf(RED "Team [0]: %d player\n" RESET, data->team_player[0]);
	ft_printf(GRN "Team [1]: %d player\n" RESET, data->team_player[1]);
	ft_printf(YEL "Team [2]: %d player\n" RESET, data->team_player[2]);
	ft_printf(BLU "Team [3]: %d player\n" RESET, data->team_player[3]);
	ft_printf(MAG "Team [4]: %d player\n" RESET, data->team_player[4]);
	ft_printf(CYN "Team [5]: %d player\n" RESET, data->team_player[5]);
	ft_printf(WHT "Team [6]: %d player\n" RESET, data->team_player[6]);
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

int
get_active_team()
{
	int	active_team = 0;

	if (data->team_player[0] > 0)
		active_team++;
	if (data->team_player[1] > 0)
		active_team++;
	if (data->team_player[2] > 0)
		active_team++;
	if (data->team_player[3] > 0)
		active_team++;
	if (data->team_player[4] > 0)
		active_team++;
	if (data->team_player[5] > 0)
		active_team++;
	if (data->team_player[6] > 0)
		active_team++;

	return active_team;
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

int
find_nearest_target()
{
	t_player_pos	pos = find_player_position(player.player_id);
	t_player_pos	nearest_pos;

	/* If other player is near current player, return is ID */
	if (player.around.left == 1)
		return data->board[pos.width - 1][pos.height];
	else if (player.around.right == 1)
		return data->board[pos.width + 1][pos.height];
	else if (player.around.up == 1)
		return data->board[pos.width][pos.height - 1];
	else if (player.around.down== 1)
		return data->board[pos.width][pos.height + 1];
		
	nearest_pos.width = 100;
	nearest_pos.height = 100;
	/* Find nearest player in array */
	for(int i = 0; i < BOARD_WIDTH; i++) {
		for(int j = 0; j < BOARD_HEIGHT; j++) {
			int	id = data->board[i][j];
			if (id != 0 && id != player.player_id 
				&& get_player_team(id) != player.team_id) {
				if (abs(i - pos.width) < nearest_pos.width
					&& abs(j - pos.height) < nearest_pos.height) {
					nearest_pos.width = i;
					nearest_pos.height = j;
				}
			}
		}
	}
	if (nearest_pos.width != 100 && nearest_pos.height != 100) {
		player.nearest_target = nearest_pos;
		return data->board[nearest_pos.width][nearest_pos.height];
	}
	return -1;
}
