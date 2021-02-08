SRCS = main.c

OBJS = ${SRCS:.c=.o}

NAME = philo_one

CFLAGS = -Wall -Wextra -Werror
CC = clang

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME} ${CFLAGS}

all: ${NAME}

clean:
	rm -f *.o

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: re all clean fclean