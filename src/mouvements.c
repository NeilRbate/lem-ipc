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

	if (pos.width == BOARD_WIDTH - 1)
		return -1;
	ret = data->board[pos.width + 1][pos.height];
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

	if (pos.width == 0)
		return -1;
	ret = data->board[pos.width - 1][pos.height];
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

	if (pos.height == BOARD_WIDTH - 1)
		return -1;
	ret = data->board[pos.width][pos.height + 1];
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

	if (pos.height == 0)
		return -1;
	ret = data->board[pos.width][pos.height - 1];
	if (ret != 0)
		return get_player_team(ret) == player.team_id ? 2 : 1;
	return 0;
}

static int
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

	if (ennemy_count >= 2) {
		ft_printf("I'm dead\n");
		if (player.is_first != IS_FIRST && data->player_count > 1) {
			exit(EXIT_SUCCESS);
		}
		player.im_alive = 0;
		data->player_count--;
		data->team_player[player.team_id]--;
		clear_player_position();

		return -1;
	}
	return 0;
}

void
go_up(t_player_pos pos)
{
	data->board[pos.width - 1][pos.height] = player.player_id;
	data->board[pos.width][pos.height] = 0;
}

void
go_down(t_player_pos pos)
{
	data->board[pos.width + 1][pos.height] = player.player_id;
	data->board[pos.width][pos.height] = 0;
}

void
go_right(t_player_pos pos)
{
	data->board[pos.width][pos.height + 1] = player.player_id;
	data->board[pos.width][pos.height] = 0;
}

void
go_left(t_player_pos pos)
{
	data->board[pos.width][pos.height - 1] = player.player_id;
	data->board[pos.width][pos.height] = 0;
}

static void
mouv_to_target(int target_id)
{
	(void)target_id;
	t_player_pos	pos = find_player_position(player.player_id);

	ft_printf("left -> %d right -> %d up -> %d down -> %d\n", player.around.left, player.around.right, 
			player.around.up, player.around.down);

	if (player.nearest_target.width < pos.width && player.around.up == 0) {
		if ((pos.width - 1) < 0)
			return;
		go_up(pos);
	} else if (player.nearest_target.width > pos.width && player.around.down == 0) {
		if ((pos.width + 1) >= BOARD_WIDTH)
			return;
		go_down(pos);
	} else if (player.nearest_target.height > pos.height && player.around.right == 0) {
		if ((pos.height + 1) >= BOARD_HEIGHT)
			return;
		go_right(pos);
	} else if (player.nearest_target.height < pos.height && player.around.left == 0) {
		if ((pos.height - 1) < 0)
			return;
		go_left(pos);
	} else {
		int	r = rand() % 4;

		switch(r) {
			case 0:
				go_up(pos);
				break;
			case 1:
				go_down(pos);
				break;
			case 2:
				go_right(pos);
				break;
			case 3:
				go_left(pos);
				break;

		}
	}
}

static void
send_target_id(int target)
{
	char	*buff;

	buff = ft_itoa(target);

	if (!buff) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	if (mq_send (player.msgq, buff, ft_strlen(buff), 0) == -1)
		perror("error mq_send");
	free(buff);
	return;
}

static void
game_routine()
{
	char	buff[8200];
	int	target;

	ft_bzero(buff, 8200);


	/* Check if msg is present in msgq */
	if (mq_receive (player.msgq, buff, 8200, NULL) == -1) {
		/* No msg, set a target, send it to other and goto target */
		target = find_nearest_target();
		if (target != -1 && target != player.player_id
			&& get_player_team(target) != player.team_id) {
			send_target_id(target);
			mouv_to_target(target);
			ft_printf("Nearest target id -> %d\n", target);
		}
		return;
	}
	/* Msg on msgq, get target id, resend it to player and goto target */
	target = atoi(buff);
	ft_printf("Target id -> %d\n", target);
	send_target_id(target);
	player.nearest_target = find_player_position(target);
	mouv_to_target(target);

	return;
}

static void
clear_player_data()
{
	ft_bzero(&player.around, sizeof(t_player_around));
	ft_bzero(&player.nearest_target, sizeof(t_player_pos));
}

int
mouv()
{
	if (im_alive() == -1)
		return 0;

	game_routine();

	clear_player_data();

	return 0;
}
