HDRS = \
	main.h \
	chronos.h \
	hermes.h \
	omnilock.h \

SRCS = \
	main.c \
	chronos.sleep.c \
	hermes_getset.c \
	hermes_init.c \
	hermes_run.c \
	omnilock.semaphore.c \

LIBS = \
	minilibft/libminift.a \


OBJS = ${SRCS:.c=.o}

NAME = philo_three

CFLAGS = -Wall -Wextra -Werror -D ${NAME}
LIBFLAGS = -lpthread
CC = clang


${NAME}: ${OBJS}
	${CC} ${OBJS} ${LIBS} -o ${NAME} ${CFLAGS} ${LIBFLAGS}

${OBJS}: ${HDRS} ${LIBS}


chronos: chronos.out
chronos.out: chronos.*.c chronos_wait.*.c chronos_test_main.c ${LIBS} chronos.h 
	${CC} chronos.*.c chronos_wait.*.c chronos_test_main.c ${LIBS} \
		-o chronos.out \
		-Wall -Wextra \
		${LIBFLAGS} \
		-D ${NAME} \
		;


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
	chronos \