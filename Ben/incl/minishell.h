/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:56:46 by bschor            #+#    #+#             */
/*   Updated: 2024/05/15 18:23:41 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <signal.h>

# define TKNSTX "minishell: syntax error near unexpected token `%c'\n"
# define TKNSSTX "minishell: syntax error near unexpected token `%s'\n"
# define NLSTX "minishell: unexpected token `newline'\n"
# define XOKACC "minishell: %s: Permission denied\n"

/*
tokens are written as their characters to make the conditions more readable
in the parser.
This obviously didnt work with the APPEND and HERED because they are two 
characters long so I addapted with characters that reminded me of them.
This does not create any problem because the only tokens to be compared to
their actual value are the 1 character long.
*/
# define DQUOTE '"'
# define SQUOTE '\''
# define INTO '<'
# define OUTTO '>'
# define HERED '='
# define APPEND '#'
# define PIPE '|'

typedef struct s_parser
{
	char	**strs;
	int		infile;
	int		outfile;
	char	*path;
}	t_parser;

typedef struct s_lexer
{
	char			*str;
	int				token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_system
{
	char		*prompt;
	char		**env;
	char		**tmp;
	t_lexer		*lexer;
	t_parser	*parser;
	int			status;
}	t_system;

// crash.c
void	ft_crash(t_system *systm);
t_lexer	*find_first(t_lexer *node);

// lexer_utils.c
char	*handle_quote(t_system *systm, int *i);
char	*handle_word(t_system *systm, int *i);
int		handle_token(t_system *systm, int *i);
int		ft_nodjoin(t_lexer *first, t_lexer *second);
void	del_node(t_lexer **node);

// lexer.c
void	ft_lexer(t_system	*systm);

// syntax.c
int		quotes_by_pair(char *str, t_system *systm);
int		check_syntax(t_system *systm);
int		finish_by_pipe(char *str);
int		last_pipe(t_system *systm);

// syntax_utils.c
char	*tkntostr(int token);

// expander.c
void	expander(t_system *systm);
void	expand_str(char **str, t_system *systm);

// expander_utils.c
int		ft_strrpl(char **origin, int start, int len_del, char *rpl);
int		find_next_alnum(char *str);
char	*find_env_var(char *str);
char	*is_env_var(char *str, char **env);

// parser.c
int		ft_parser(t_system *systm);

// parser_utils.c
int		count_pipes(t_lexer *lexer);
int		add_word(t_system *systm, int exec_i);
void	free_strs(char **strs);

// heredoc.c
int		heredoc(t_system *systm, int exec_i);

// signals.c
int		init_termcap(void);
void    ft_suppress_output(void);
void	new_prompt(int signal);

// get_path.c
char	*ft_strtok(char *str, char c, int nbr);
char	*join_and_free(char *s1, char *s2);
char	*check_path(char *cmd);

// readline
void 	rl_replace_line (const char *, int);

#endif