HDRS = \
	main.h \
	philosopher.h \
	simulation.h \
	sustenance_ustensile.h \

SRCS = \
	main.c \
	philosopher.c \
	simulation.c \
	sustenance_ustensile.c \

OBJS = ${SRCS:.c=.o}

NAME = philo_one

CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -lpthread
CC = clang

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME} ${CFLAGS} ${LIBFLAGS}

${OBJS}: ${HDRS}

all: ${NAME}

clean:
	rm -f *.o

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: re all clean fclean