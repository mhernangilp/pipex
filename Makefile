#####################
#      SETUP        #
#####################

NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
#####################
#      COLORS       #
#####################

NOC = \033[0m
YELLOW = \033[1;33m
GREEN = \033[1;32m
RED = \033[1;31m

#####################
#      FILES        #
#####################

HEADER_SRC = pipex.h pipex_bonus.h
HEADER_PATH = includes/
HEADER = $(addprefix $(HEADER_PATH), $(HEADER_SRC))

MSRC = main.c child_process.c error.c
MSRC_PATH = mandatory/
MAN = $(addprefix $(MSRC_PATH), $(MSRC))
OBJ = $(MAN:.c=.o)

BSRC = main_bonus.c child_process_bonus.c \
       utils_bonus.c error_bonus.c heredoc_bonus.c
BSRC_PATH = bonus/
BON = $(addprefix $(BSRC_PATH), $(BSRC))
BOBJ = $(BON:.c=.o)

#####################
#     LIBRARIES     #
#####################

LIBFT_PATH = libft/
LIBFT = libft/libft.a

GNL_HEADER = gnl/get_next_line_bonus.h
GNL_SRC = get_next_line_bonus.c get_next_line_utils_bonus.c
GNL_PATH = gnl/bonus/
GNL = $(addprefix $(GNL_PATH), $(GNL_SRC))
GNL_OBJ = $(GNL:.c=.o)

#####################
#      FILES        #
#####################

%.o: %.c $(HEADER) $(GNL_HEADER)
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@

all: $(NAME)

$(LIBFT):
	@make -sC $(LIBFT_PATH)

start:
	@echo "$(YELLOW)Compiling pipex ...$(NOC)"

$(NAME): start $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -I $(LIBFT_PATH) -o $(NAME)
	@echo "$(GREEN)Pipex compiled ✓$(NOC)"

bonus: start $(LIBFT) $(BOBJ) $(GNL_OBJ)
	@$(CC) $(CFLAGS) $(BOBJ) $(GNL_OBJ) $(LIBFT) -I $(LIBFT_PATH) -o $(NAME)
	@echo "$(GREEN)Pipex compiled with bonus ✓$(NOC)"

clean: 
	@make clean -sC $(LIBFT_PATH)
	@rm -f $(OBJ)
	@rm -f $(BOBJ)
	@echo "$(RED)Pipex objects deleted ✓$(NOC)"

fclean:	
	@make fclean -sC $(LIBFT_PATH)
	@rm -f $(OBJ)
	@rm -f $(BOBJ)
	@echo "$(RED)Pipex objects deleted ✓$(NOC)"
	@rm -f $(LIBFT)
	@rm -f $(NAME)
	@echo "$(RED)Pipex deleted ✓$(NOC)"

re: fclean all

.PHONY: all clean fclean re
