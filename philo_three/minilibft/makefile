HDRS = \
	minilibft.h \

SRCS = \
	minilibft.c \
	math.c \
	stringgen.c \
	throw.c \

OBJS = ${SRCS:.c=.o}

NAME = libminift.a

CFLAGS = -Wall -Wextra -Werror
CC = clang


${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

${OBJS}: ${HDRS}


all: ${NAME}

clean:
	rm -f *.o

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: re all clean fclean