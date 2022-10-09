FUNC_NAMES_M =	issign isspace isalpha isdigit isalnum isascii			\
		isprint strlen memset bzero memcpy memmove strlcpy		\
		strlcat isupper islower toupper tolower				\
		strchr strrchr strchr_set strrchr_set				\
		strcmp strncmp memchr memcmp memclear strnstr			\
		atoi atol atoi_base itoa 					\
		calloc strlcat substr strjoin strtrim strdup			\
		split split_set split_space					\
		strmapi striteri						\
		putchar_fd putstr_fd putendl_fd putnbr_fd			\
		pow abs sqrt							\
		strlower strupper
			
FUNC_NAMES_X =	ft_printf ft_eprintf ft_vprintf ft_random ft_clamp fperror 	\
		malloc_free get_next_line get_next_line_utils ft_deltatime_usec \
		strtab_utils find_file_in_env substring_substitution set_errno	\
		ft_swap 							\
		variable_length_array variable_length_array_utils		\
		variable_length_array_ops variable_length_array_ops2		\
		variable_length_array_tests variable_length_array_min_max

FUNC_NAMES_B =	lstnew lstcreate lstinsert lstadd_front lstadd_back lstsize	\
		lstlast lstdelone lstclear lstiter lstmap lstpop lstmap lstprint

PREF		= ft_
SUF_M		= .c

SRCS_TEMP_M	= ${addprefix ${PREF}, ${FUNC_NAMES_M}} ${FUNC_NAMES_X}
SRCS_M		= ${addsuffix ${SUF_M}, ${SRCS_TEMP_M}}

SRCS_TEMP_B	= ${addprefix ${PREF}, ${FUNC_NAMES_B}}
SRCS_B		= ${addsuffix ${SUF_M}, ${SRCS_TEMP_B}}

OBJS_M		= ${SRCS_M:.c=.o}
OBJS_B		= ${SRCS_B:.c=.o}

CC		= gcc
CFLAGS		= -Wall -Wextra -Werror

AR		= ar -rcs

RM		= rm -f

NAME		= libft.a

%.o: 		%.c
			-${CC} ${CFLAGS} -I./ -c $< -o $@

${NAME}:	${OBJS_M}
			${AR} ${NAME} ${OBJS_M}

all:		${NAME}

clean:
			${RM} ${OBJS_M} ${OBJS_B}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

bonus:		${OBJS_B}
			ar -rs ${NAME} ${OBJS_B}
