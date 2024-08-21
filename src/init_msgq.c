#include "../include/lem-ipc.h"

mqd_t
init_msgq()
{
	return mq_open(MSGQ_KEY, O_RDWR | O_CREAT , 0664, 0); 
}
