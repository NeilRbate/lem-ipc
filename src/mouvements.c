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
im_alive()
{
	t_player_pos pos = find_player_position(player.player_id);

	player.around.left = check_left(pos);
	player.around.right = check_right(pos);
	player.around.up = check_up(pos);
	player.around.down = check_down(pos);

	int	ennemy_count = 0;
	if (player.around.left == 1)
		ennemy_count++;
	if (player.around.right == 1)
		ennemy_count++;
	if (player.around.up == 1)
		ennemy_count++;
	if (player.around.down == 1)
		ennemy_count++;

	if (ennemy_count > 1)
		exit(EXIT_SUCCESS);
}

/* Return target id of -1 if no target */
/*
static int
find_nearest_target()
{
	for(size_t i = 0; i < BOARD_WIDTH; i++) {
		for(size_t j = 0; j < BOARD_HEIGHT; j++) {

		}
	}
		

	return -1;
}
*/

/*
static void
mouv_to_target(int target_id)
{
	(void)target_id;
	//Find nearest target
	//Find best mouv (left/right/up/down)
	
}
*/

static void
game_routine()
{
	char	buff[8200];
	int	retval;

	ft_bzero(buff, 8200);

	/* Check if msg is present in msgq */
	if ((retval = mq_receive (player.msgq, buff, 8200, NULL)) == -1) {
		/* No msg, set a target, send it to other and goto target */
		//target = find_nearest_target();
		//return;
	}

	/* Target in msgq, resend to other player and goto target */
	if ((retval = mq_send (player.msgq, buff, ft_strlen(buff), 0)) == -1)
		perror("error mq_send");
	ft_printf("msgq -> %s\n", buff);
	return;

	//Set a target for team
	char	*c_id = ft_itoa(player.player_id);
	buff[0] = 'I';
	buff[1] = 'D';
	ft_printf("c_id -> %s\n", c_id);
	for(size_t  i = 2; i < (ft_strlen(c_id) + 2); i++)
		buff[i] = c_id[i - 2];
	free(c_id);

	if ((retval = mq_send (player.msgq, buff, ft_strlen(buff), 0)) == -1)
		perror("error mq_send");

}

int
mouv()
{
	im_alive();
	game_routine();

	return 0;
}
