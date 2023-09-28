NAME = pipex

SRCS = mandatory/main.c \
	   mandatory/child_process.c \
	   mandatory/utils.c \
	   mandatory/utils_2.c

INCLUDE = includes/pipex.h

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ${INCLUDE}
	${CC} ${OBJS} -o ${NAME}

clean: 
	${RM} ${OBJS}

fclean: 
	${RM} ${OBJS}
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
