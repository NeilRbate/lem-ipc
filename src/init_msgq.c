#include "../include/lem-ipc.h"


mqd_t
init_msgq()
{
	/* Create shared msgq and return status */
	mqd_t	mq;
	struct	mq_attr	attr;

	attr.mq_flags = O_NONBLOCK;
	attr.mq_maxmsg = MSGQ_COUNT;
	attr.mq_msgsize = MSGQ_SIZE;
	attr.mq_curmsgs = 0;

	mq = mq_open(MSGQ_KEY[player.team_id], 
			O_CREAT | O_RDWR | O_NONBLOCK, 0644, &attr);

	player.msgq_attr = attr;

	if ((int)mq == -1) {
		perror("msgq error");
		sem_post(player.sem);
		exit(EXIT_FAILURE);
	}

	player.msgq = mq;


	return 0;
}
