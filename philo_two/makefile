HDRS = \
	main.h \
	chronos.h \
	fated_list_of_minor_prophecies.h \
	philosopher.h \
	philosopher_ustensile.h \
	simulation.h \
	sustenance_ustensile.h \
	thanatos.h \

SRCS = \
	main.c \
	chronos.c \
	chronos_wait.c \
	fates.c \
	philosopher.c \
	philosopher_main.c \
	philosopher_ustensile.c \
	simulation.c \
	sustenance_ustensile.c \
	thanatos.c \

LIBS = \
	minilibft/libminift.a \


OBJS = ${SRCS:.c=.o}

NAME = philo_two

CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -lpthread
CC = clang


${NAME}: ${OBJS}
	${CC} ${OBJS} ${LIBS} -o ${NAME} ${CFLAGS} ${LIBFLAGS} -D ${NAME}

${OBJS}: ${HDRS} ${LIBS}


chronos: chronos.out
chronos.out: chronos.c chronos_wait.c chronos_test_main.c ${LIBS} chronos.h 
	${CC} chronos.c chronos_wait.c chronos_test_main.c ${LIBS} \
		-o chronos.out \
		-Wall -Wextra \
		${LIBS} \
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