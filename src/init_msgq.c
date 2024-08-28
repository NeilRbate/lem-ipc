#include "../include/lem-ipc.h"

extern t_data	*data;

mqd_t
init_msgq()
{
	mqd_t	mq;
	struct	mq_attr	attr;

	attr.mq_maxmsg = MSGQ_COUNT;
	attr.mq_msgsize = MSGQ_SIZE;

	mq = mq_open(MSGQ_KEY, O_CREAT | O_RDWR, 
			S_IRUSR | S_IWUSR, NULL);

	data->msgq_attr = attr;

	if (mq == -1) {
		perror("msgq error");
		exit(EXIT_FAILURE);
	}


	return 0;
}
