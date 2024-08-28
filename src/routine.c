#include "../include/lem-ipc.h"

void	
start_routine()
{
	ft_printf("player [%d] in team [%d] is ready !", 
			player.player_id,
			player.team_id);
	return;
}
