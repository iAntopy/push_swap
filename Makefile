
SRC_DIR		= src/

_SRC	=	push_swap_main			\
			push_swap_algo			\
			cook_book				\
			parse_inputs			\
			error_handling			\
			stack_utils				\
			stack_moves				\
			stack_moves2			\
			stack_moves_test_env	\
			stack_moves2_test_env	\
			stack_moves_tec			\
			stack_moves2_tec		\
			checker_funcs			\
			print_stacks			\
			sort_3_5				\
			dist_funcs				\
			analysis_funcs			\
			analysis_funcs2			\
			chunkers				\
			pathfinding_funcs		\
			chunk_stack_utils		\
			chunk_stack_utils2		\
			test_env_utils			\
			test_env_chunks_utils

SRC			= $(addprefix $(SRC_DIR), $(_SRC))

SRC_M		= $(addsuffix .c, $(SRC))
#SRC_B		= $(addsuffix _bonus.c, $(SRC))

OBJ_M		= $(SRC_M:.c=.o)
#OBJ_B		= $(SRC_B:.c=.o)

INCL		= include/

LIBFT		= libft/libft.a

CC			= gcc
CFLAGS		= -g -Wall -Wextra -Werror

NAME		= push_swap
#NAME_BONUS	= checker_bonus

%.o:		%.c
		-$(CC) $(CFLAGS) -I$(INCL) -c $< -o $@

$(NAME):	$(LIBFT) $(OBJ_M)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ_M) $(LIBFT)

#$(NAME_BONUS):	$(LIBFT) $(OBJ_B)
#		$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_B) $(LIBFT)

$(LIBFT):
		make -C libft/

all:		$(NAME)

bonus:		$(NAME_BONUS)

clean:
		rm -f $(OBJ_M) $(LIBFT)

fclean:		clean
		rm -f $(NAME)

re:			fclean all
