#include "../include/lem-ipc.h"

sem_t
*init_sem()
{
	return sem_open(SEM_KEY, O_RDWR | O_CREAT, 0664, 0); 
}
