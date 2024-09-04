#include "../include/lem-ipc.h"


mqd_t
init_msgq()
{
	/* Create shared msgq and return status */
	mqd_t	mq;
	struct	mq_attr	attr;

	attr.mq_maxmsg = MSGQ_COUNT;
	attr.mq_msgsize = MSGQ_SIZE;

	mq = mq_open(MSGQ_KEY, O_CREAT | O_RDWR, 
			S_IRUSR | S_IWUSR, NULL);

	player.msgq_attr = attr;

	if (mq == -1) {
		perror("msgq error");
		sem_post(player.sem);
		exit(EXIT_FAILURE);
	}

	player.msgq = mq;


	return 0;
}
