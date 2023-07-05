NAME = pipex

SRCS = src/main.c \
	   src/child_process.c \
	   src/utils.c

INCLUDE = ./pipex.h

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ${INCLUDE}
	${CC} ${SRCS} -o ${NAME}

clean: ${RM} ${OBJS}

fclean: 
	${RM} ${OBJS}
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
