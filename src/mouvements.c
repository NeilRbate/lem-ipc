#include "../include/lem-ipc.h"

/* TODO :
 * - Make function to check all case between me, Left/Right/Up/Down: OK
 * - Check if i'm alive: OK
 * - Choose mouv to do
 */

static int
check_down(t_player_pos pos)
{
	/* Return 0 if case is empty, 1 for ennemy, 2 for allies*/
	/* Return  -1 if out of bound */

	int	ret;

	if (pos.height == BOARD_HEIGHT - 1)
		return -1;
	ret = data->board[pos.width][pos.height + 1];
	if (ret != 0)
		return get_player_team(ret) == player.team_id ? 2 : 1;
	return 0;
}


static int
check_up(t_player_pos pos)
{
	/* Return 0 if case is empty, 1 for ennemy, 2 for allies*/
	/* Return  -1 if out of bound */

	int	ret;

	if (pos.height == 0)
		return -1;
	ret = data->board[pos.width][pos.height - 1];
	if (ret != 0)
		return get_player_team(ret) == player.team_id ? 2 : 1;
	return 0;
}

static int
check_right(t_player_pos pos)
{
	/* Return 0 if case is empty, 1 for ennemy, 2 for allies*/
	/* Return  -1 if out of bound */

	int ret;

	if (pos.width == BOARD_WIDTH - 1)
		return -1;
	ret = data->board[pos.width + 1][pos.height];
	if (ret != 0)
		return get_player_team(ret) == player.team_id ? 2 : 1;
	return 0;

}

static int
check_left(t_player_pos pos)
{
	/* Return 0 if case is empty, 1 for ennemy, 2 for allies*/
	/* Return  -1 if out of bound */

	int ret;

	if (pos.width == 0)
		return -1;
	ret = data->board[pos.width - 1][pos.height];
	if (ret != 0)
		return get_player_team(ret) == player.team_id ? 2 : 1;
	return 0;
}

static void
im_alive(int left, int right, int up, int down)
{
	int	ennemy_count = 0;
	if (left == 1)
		ennemy_count++;
	if (right == 1)
		ennemy_count++;
	if (up == 1)
		ennemy_count++;
	if (down == 1)
		ennemy_count++;

	if (ennemy_count > 1)
		exit(EXIT_SUCCESS);
}

static t_player_pos
find_nearest_target()
{

}

static void
mouv_to_target(int target_id)
{
	//Find nearest target
	//Find best mouv (left/right/up/down)
	
}

static void
check_msgq()
{
	char	buff[8200];
	int		retval;

	ft_bzero(buff, 8200);

		if ((retval = mq_receive (player.msgq, buff, 8200, NULL)) == -1) {
			//Set target
				break;
		}
		else {
			//Goto target send target to other and return
			if ((retval = mq_send (player.msgq, buff, ft_strlen(buff), 0)) == -1)
				perror("error mq_send");
			ft_printf("msgq -> %s\n", buff);
			return;
		}
	}

	//Set a target for team
	char	*c_id = ft_itoa(player.player_id);
	buff[0] = 'I';
	buff[1] = 'D';
	ft_printf("c_id -> %s\n", c_id);
	for(size_t  i = 2; i < (ft_strlen(c_id) + 2); i++)
		buff[i] = c_id[i - 2];

	if ((retval = mq_send (player.msgq, buff, ft_strlen(buff), 0)) == -1)
		perror("error mq_send");

}

int
mouv()
{
	t_player_pos pos = find_player_position(player.player_id);

	int left, right, up, down;

	left = check_left(pos);
	right = check_right(pos);
	up = check_up(pos);
	down = check_down(pos);

	im_alive(left, right, up, down);
	check_msgq();

	return 0;

}
