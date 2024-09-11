#include "../include/lem-ipc.h"

static void
clear_player_position()
{
	t_player_pos pos = find_player_position(player.player_id);
	if (data->board[pos.width][pos.height] == player.player_id)
		data->board[pos.width][pos.height] = 0;
	del_team_player();
}

void
clear_ipcs()
{
	if (!data)
		return;
	sem_wait(player.sem);
	data->player_count--;
	data->team_player[player.team_id]--;
	clear_player_position();
	if (player.is_first == IS_FIRST)
		data->is_end = IS_END;
	if (data->team_player[player.team_id] == 0)
		mq_unlink(MSGQ_KEY[player.team_id - 1]);
	sem_post(player.sem);
	if (data->player_count <= 0) {
		sem_close(player.sem);
		sem_unlink(SEM_KEY);
		mq_unlink(MSGQ_KEY[player.team_id]);
		shm_unlink(SHM_KEY);
		munmap(data, sizeof(t_data));
	}
}
