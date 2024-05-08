NAME = minishell

INCLUDE = minishell.h

CFLAGS = -Wall -Werror -Wextra

SRCS =	main.c				\
		builtins.c			\
		utils.c				\
		utils2.c			\
		ft_split.c			\
		export_unset.c		\
		execve.c			\
		tools.c				\
		builtins_utils.c	\
		env.c				\

OBJ = $(SRCS:.c=.o)

# READ_FLAGS = -L .brew/opt/readline/lib -I .brew/opt/readline/include

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -lreadline -o $(NAME)

clean :
	rm  -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re