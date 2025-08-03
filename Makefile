NAME := philo
CC := cc
FLAGS := -Wall -Wextra -Werror

SRCS := main.c \
    	run.c \
        check_and_parse.c \
        time.c \
	    utils.c \
		libft_func.c \
		eat.c \
		init.c \
		monitor.c \
                          
OBJS := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${CC} ${FLAGS} -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			@ ${RM} *.o

fclean:		clean
			@ ${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
