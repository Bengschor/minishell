# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bschor <bschor@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/13 16:15:18 by bschor            #+#    #+#              #
#    Updated: 2024/07/24 18:57:42 by bschor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

RL		= -ltermcap -lreadline -L ~/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include

# src / obj files
SRC		=	lexer.c \
			lexer_utils.c \
			chained_list.c	\
			free.c \
			expander.c \
			expander_utils.c \
			syntax.c \
			parser.c \
			parser_utils.c \
			heredoc.c \
			syntax_utils.c \
			signals.c \
			main.c \
			ft_pipex.c \
			exec.c \
			get_path.c	\
			builtins.c	\
			builtins_utils.c	\
			command.c	\
			unset.c		\
			unset_utils.c	\
			cd_utils.c	\
			export.c	\
			export_utils.c	\
			ft_env.c		\
			ft_env_utils.c	\
			readstr.c	\

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft

# directories
SRCDIR		= ./srcs/
INCDIR		= ./incl/minishell.h
OBJDIR		= ./obj/

all: obj $(FT_LIB) $(NAME)


obj:
	@mkdir $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(FT_INC) -o $@ -c $<

$(FT_LIB):
	@make -C $(FT)
	@echo "COMPILING LIBFT"

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(FT_LIB) $(RL) -o $(NAME)


clean:
	rm -rf $(OBJDIR)
	@make -C $(FT) clean
	@echo "REMOVING LIBFT"

fclean: clean
	rm -rf $(NAME)
	@make -C $(FT) fclean

re: fclean all

.PHONY:	all clean fclean re bonus
