#include "../include/lem-ipc.h"

int
init_shm()
{
	return shm_open(SHM_KEY, O_RDWR | O_CREAT, 0664); 

}
