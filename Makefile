
SRC_DIR		= src/
SRC_B_DIR		= src_bonus/

_SRC	=	push_swap_main.c			\
			push_swap_algo.c			\
			cook_book.c				\
			parse_inputs.c			\
			error_handling.c			\
			stack_utils.c				\
			stack_moves.c				\
			stack_moves2.c			\
			stack_moves_test_env.c	\
			stack_moves2_test_env.c	\
			stack_moves_tec.c			\
			stack_moves2_tec.c		\
			checker_funcs.c			\
			sort_3_5.c				\
			dist_funcs.c				\
			analysis_funcs.c			\
			analysis_funcs2.c			\
			chunkers.c				\
			pathfinding_funcs.c		\
			pathfinding_recursive_funcs.c		\
			chunk_stack_utils.c		\
			chunk_stack_utils2.c		\
			test_env_utils.c			\
			test_env_chunks_utils.c

_SRC_B	=	checker_main_bonus.c	\
			error_handling_bonus.c			\
			parse_inputs_bonus.c			\
			stack_moves_bonus.c			\
			stack_utils_bonus.c

SRC_M		= $(addprefix $(SRC_DIR), $(_SRC))
SRC_B		= $(addprefix $(SRC_B_DIR), $(_SRC_B))


OBJ_M		= $(SRC_M:.c=.o)
OBJ_B		= $(SRC_B:.c=.o)

INCL		= include/

LIBFT		= libft/libft.a

CC		= gcc
CFLAGS		= -g -Wall -Wextra -Werror

NAME		= push_swap
NAME_BONUS	= checker

%_bonus.o:	%.c
		-$(CC) $(CFLAGS) -I$(INCL) -c $< -o $@
%.o:		%.c
		-$(CC) $(CFLAGS) -I$(INCL) -c $< -o $@

$(NAME):	$(LIBFT) $(OBJ_M)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ_M) $(LIBFT)

$(NAME_BONUS):	$(LIBFT) $(OBJ_B)
		$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_B) $(LIBFT)

$(LIBFT):
		make -C libft/

all:		$(NAME)

bonus:		$(NAME_BONUS)

clean:
		rm -f $(OBJ_M) $(OBJ_B) $(LIBFT)

fclean:		clean
		rm -f $(NAME) $(NAME_BONUS)

re:			fclean all
