CC = gcc

CFLAGS = -Wall \
	 -Wextra \
	 -Werror

NAME = lemipc 

SRCS = src/main.c \
       src/init_sem.c \
       src/init_shm.c \
       src/init_msgq.c \
       src/clear_ipcs.c \
       src/routine.c \
       src/helpers.c \
       src/mouvements.c

LIBFT = -L. libft/libft.a 

OBJS = ${SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	@make -C libft all
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}


clean:
	@rm -f ${OBJS}
	@make -C libft clean

fclean: clean
	@rm -f ${NAME}
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
