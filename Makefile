NAME = pipex

SRCS = mandatory/main.c \
	   mandatory/child_process.c \
	   mandatory/utils.c \
	   mandatory/utils_2.c

BSRCS = bonus/main_bonus.c \
	bonus/child_process_bonus.c \
	bonus/utils_bonus.c \
	bonus/utils_2_bonus.c \
	bonus/error_bonus.c

INCLUDE = includes/pipex.h

BINCLUDE = includes/pipex_bonus.h

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

OBJS = ${SRCS:.c=.o}

BOBJS = ${BSRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ${INCLUDE}
	${CC} ${OBJS} -o ${NAME}

bonus: ${BOBJS} ${BINCLUDE}
	${CC} ${BOBJS} -o ${NAME}

clean: 
	${RM} ${OBJS}
	${RM} ${BOBJS}

fclean: 
	${RM} ${OBJS}
	${RM} ${BOBJS}
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
