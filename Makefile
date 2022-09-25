
SRC_DIR		= src/

_SRC	=	push_swap_main \
			parse_inputs	\
			error_handling	\
			stack_moves		\
			stack_moves2		\
			checker_funcs	\
			reference_arr_utils \
			print_stacks		\
			sort_3_5		\
			dist_funcs		\
			analysis_funcs

SRC			= $(addprefix $(SRC_DIR), $(_SRC))

SRC_M		= $(addsuffix .c, $(SRC))
#SRC_B		= $(addsuffix _bonus.c, $(SRC))

OBJ_M		= $(SRC_M:.c=.o)
#OBJ_B		= $(SRC_B:.c=.o)

INCL		= include/

LIBFT		= libft/libft.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

NAME		= push_swap
#NAME_BONUS	= pipex_bonus

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
