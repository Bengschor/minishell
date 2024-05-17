/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:56:46 by bschor            #+#    #+#             */
/*   Updated: 2024/05/17 16:39:19 by bschor           ###   ########.fr       */
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
	int		last;
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
	int			pid;
	t_parser	*parser;
	int			status;
}	t_system;

// builtins.c
int do_echo(int argc, char **argv);
int do_cd(const char *path, t_system *systm) ;
int do_pwd(int argc);
int do_env(int argc, char **env);
int do_exit();

// builtins_utils.c
void ch_oldpwd();
int	if_same_word(char *s1, char *s2);
int if_blank(char c);
char **ft_split_in_2(char *str);
int if_key(char *str, char *var);
int ft_setenv(char *key, char *value, char ***env);

// command.c
int is_builtins(char *cmd);
int get_argc(char **strs);
int do_builtins(t_system *systm, char **argv);

// export_unset.c
int get_pos(char *env, char c);
int if_in_env(char *var, char **env);
// int do_unset(char **tab, int argc, char **env);
int get_res(char *str);
int do_export(int argc, char **tabb, char ***env);

// free.c
void	ft_crash(t_system *systm);
t_lexer	*find_first(t_lexer *node);
void	ft_free_systm(t_system *systm);

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
void	print_nl(int signal);
void    ft_suppress_output(void);
void	new_prompt(int signal);
void    ft_include_output(void);
void	ft_handle_sigquit(int signal);

// get_path.c
char	*ft_strtok(char *str, char c, int nbr, t_system *systm);
char	*join_and_free(char *s1, char *s2, t_system *systm);
char 	*get_path(char *cmd, t_system *systm);

// ft_pipex.c
int		ft_pipex(t_system *systm, int pars_i, int stdout);

// exec.c
int		execution(t_system *systm);

// readline
void 	rl_replace_line (const char *, int);

#endif