HDRS = \
	main.h \
	chronos.h \
	fated_list_of_minor_prophecies.h \
	philosopher.h \
	simulation.h \
	sustenance_ustensile.h \

SRCS = \
	main.c \
	chronos.c \
	fates.c \
	philosopher.c \
	philosopher_main.c \
	simulation.c \
	sustenance_ustensile.c \

LIBS = \
	minilibft/libminift.a \


OBJS = ${SRCS:.c=.o}

NAME = philo_one

CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -lpthread
CC = clang

${NAME}: ${OBJS}
	${CC} ${OBJS} ${LIBS} -o ${NAME} ${CFLAGS} ${LIBFLAGS}

${OBJS}: ${HDRS} ${LIBS}

%.a: sub_makefile
	make $(@F) -C $(@D)

all: ${NAME}

clean:
	rm -f *.o

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: \
	re all clean fclean \
	sub_makefile \