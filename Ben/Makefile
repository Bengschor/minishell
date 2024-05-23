# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bschor <bschor@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/13 16:15:18 by bschor            #+#    #+#              #
#    Updated: 2024/05/23 11:17:46 by bschor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

RL		= -ltermcap -lreadline -L ~/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include

# TERMCAP	= -lncurses -L ~/homebrew/opt/ncurses/lib -I /opt/homebrew/opt/ncurses/include /opt/homebrew/opt/ncurses/bin/*

# src / obj files
SRC		=	lexer.c \
			lexer_utils.c \
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
			get_path.c \
			builtins.c \
			builtins_utils.c \
			command.c \
			export_unset.c \

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g

# ft library
FT		= ../libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ../libft

# directories
SRCDIR		= ./srcs/
INCDIR		= ./incl/minishell.h
OBJDIR		= ./obj/

all: obj $(FT_LIB) $(NAME)


obj:
	@mkdir $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	@make -C $(FT)
	@echo "COMPILING LIBFT"

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(RL) $(OBJ) $(FT_LIB) -o $(NAME)


clean:
	rm -rf $(OBJDIR)
	@make -C $(FT) clean
	@echo "REMOVING LIBFT"

fclean: clean
	rm -rf $(NAME)
	@make -C $(FT) fclean

re: fclean all

.PHONY:	all clean fclean re bonus