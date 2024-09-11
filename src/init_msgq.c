#include "../include/lem-ipc.h"

//#define	MSGQ_SIZE	32
//#define	MSGQ_COUNT	32


mqd_t
init_msgq()
{
	/* Create shared msgq and return status */
	mqd_t	mq;
	struct	mq_attr	attr;

	ft_memset(&attr, 0x00, sizeof(struct mq_attr));


	attr.mq_maxmsg = (long)MSGQ_COUNT;
	attr.mq_msgsize = (long)MSGQ_SIZE;

	mq = mq_open(MSGQ_KEY[player.team_id], O_CREAT | O_RDWR | O_NONBLOCK, 0644, NULL);


	if ((int)mq == -1) {
		perror("msgq error");
		sem_post(player.sem);
		exit(EXIT_FAILURE);
	}

	player.msgq_attr = attr;
	player.msgq = mq;


	return 0;
}
