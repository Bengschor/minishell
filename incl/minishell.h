/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:56:46 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 18:52:29 by bschor           ###   ########.fr       */
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
# include <readline/history.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <string.h>

# define TKNSTX "minishell: syntax error near unexpected token `%c'\n"
# define TKNSSTX "minishell: syntax error near unexpected token `%s'\n"
# define NLSTX "minishell: syntax error near unexpected token `newline'\n"
# define XOKACC "minishell: %s: Permission denied\n"
# define ISADIR "minishell: %s: is a directory\n"
# define UNXEOF "\x1b[1A\x1b[2Cminishell: syntax error: \
	unexpected end of file\n"
# define UNCQUO "minishell: not interpreting unclosed quotes\n"
# define EXNOTVID "minishell: export: `%s': not a valid identifier\n"
# define CRASH 1
# define CHILL 0

# define DQUOTE '"'
# define SQUOTE '\''
# define INTO '<'
# define OUTTO '>'
# define HERED '='
# define APPEND '#'
# define PIPE '|'

int	g_status;

typedef struct s_env
{
	char			*key_value;
	struct s_env	*next;
}	t_env;

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
	t_env		**env;
	char		**tmp;
	t_lexer		*lexer;
	int			pid;
	t_parser	*parser;
	int			status;
	int			std[2];
	int			mallocked_prompt;
}	t_system;

/*----------------  ft_env_utils.c  ---------------*/
char	*get_key(char *key_value);
char	*ft_getenv(char *key, t_env **env);
t_env	*ft_super_getenv(char *key, t_env **env);
void	add_elem(t_env **env, char *envp, int *count, t_system *systm);

/*----------------  builtins.c  ---------------*/
int		do_echo(int argc, char **argv);
int		do_cd(char *path, t_system *systm);
int		do_pwd(t_system *systm);
int		do_env(int argc, char **argv, t_env **env);
int		do_exit(int ac, char **av, t_system *systm);

/*----------------  syntax_utils.c  ---------------*/
int		ft_print_syntax(char *str, t_system *systm);
char	*tkntostr(int token);
int		last_pipe(t_system *systm);

/*----------------  ft_pipex.c  ---------------*/
int		ft_pipex(t_system *systm, int pars_i);

/*----------------  exec.c  ---------------*/
int		execution(t_system *systm);

/*----------------  expander.c  ---------------*/
void	expand_str(char **str, t_system *systm);
void	expander(t_system *systm);

/*----------------  command.c  ---------------*/
int		is_builtins(char *cmd);
int		get_argc(char **strs);
int		do_builtins(t_system *systm, char **argv);

/*----------------  readstr.c  ---------------*/
char	*readstr(int fd);

/*----------------  cd_utils.c  ---------------*/
int		ch_oldpwd(t_env **env, t_system *systm);
int		keyword_path(t_system *systm, char *str, char *key);
int		get_last_c(char *str, char c);
int		get_ex_code(char *str);

/*----------------  lexer.c  ---------------*/
void	ft_lexer(t_system	*systm);
int		start_by_space(char *str);

/*----------------  unset.c  ---------------*/
int		check_unset_argv(char **argv, int *c, int *save);
void	remove_elem(char **argv, t_env **env);
int		do_unset(char **argv, t_env **env);

/*----------------  export_utils.c  ---------------*/
int		if_key(char *str, char *var);
int		get_pos(char *str, char c);
char	**if_in_env(char *key_value, t_env **env);
int		ft_add_new(t_env **env, char *str);

/*----------------  parser_utils.c  ---------------*/
void	free_strs(char **strs);
int		add_word(t_system *systm, int exec_i);
int		count_pipes(t_lexer *lexer);

/*----------------  main.c  ---------------*/
int		main(int argc, char **argv, char *envp[]);

/*----------------  free.c  ---------------*/
void	free_env(t_system *systm);
void	ft_free_systm(t_system *systm);
void	free_all(t_system *systm, int flag);

/*----------------  heredoc.c  ---------------*/
int		heredoc(t_system *systm, int exec_i);

/*----------------  ft_env.c  ---------------*/
char	*check_shlvl(char *shlvl);
void	ft_env(t_env **env, char **envp, t_system *systm);
void	ft_lstclear(t_env **lst);
void	ft_sort(t_env **current, t_env **sorted);
void	ft_lstsort(t_env **lst);

/*----------------  chained_list.c  ---------------*/
void	ft_lstadd_back(t_env **lst, t_env *new);
void	ft_lstadd_front(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *lst);
t_env	*ft_lstnew(char *key_value);
int		ft_lstsize(t_env *lst);

/*----------------  export.c  ---------------*/
int		do_export(char **argv, t_env **env);
int		do_sort_env(t_env **env);
int		get_res(char *str);
int		ft_setenv(char *str, int x, t_env **env);

/*----------------  expander_utils.c  ---------------*/
int		ft_strrpl(char **origin, int start, int len_del, char *rpl);
int		find_next_alnum(char *str);
char	*is_env_var(char *str, t_env **env);

/*----------------  syntax.c  ---------------*/
int		finish_by_pipe(char *str);
int		quotes_by_pair(char *str, t_system *systm, int i);
int		check_syntax(t_system *systm);

/*----------------  parser.c  ---------------*/
int		ft_parser(t_system *systm);

/*----------------  lexer_utils.c  ---------------*/
void	del_node(t_lexer **node);
int		ft_nodjoin(t_lexer *first, t_lexer *second);
char	*handle_quote(t_system *systm, int *i);
char	*handle_word(t_system *systm, int *i);
int		handle_token(t_system *systm, int *i);

/*----------------  builtins_utils.c  ---------------*/
int		if_same_word(char *s1, char *s2);
int		if_blank(char c);
char	*ft_realloc(char *s, char *cpy, t_system *systm);
int		if_option(char *arg);
int		is_all_digit(char *str);

/*----------------  get_path.c  ---------------*/
char	*join_and_free(char *s1, char *s2, t_system *systm);
char	*ft_strtok(char *str, char c, int nbr, t_system *systm);
char	*get_path(char *cmd, t_system *systm, char *paths);

/*----------------  unset_utils.c  ---------------*/
int		is_syntax(int c);
int		is_id_invalid(int c);
int		ft_check_syntax(char s, int *c, int res);
void	ft_lstdelone(t_env *curr, t_env **env);
int		in_unset_env(char *key, t_env **env);

/*----------------  signals.c  ---------------*/
void	update_glob(int signal);
void	print_nl(int signal);
void	new_prompt(int signal);
void	ft_suppress_output(void);
void	ft_include_output(void);

// readline
void	rl_replace_line(const char *str, int num);

/*
// linux portability
void	add_history(const char *ptr);
void	clear_history(void);
pid_t	wait(int *status);
pid_t	waitpid(pid_t pid, int *status, int options);
*/

# define INTRO "\033[0;31m___  ________ _   _ _____ \
_____ _   _  _____ _      _\n\
|  \\/  |_   _| \\ | |_   _/  ___| | | ||  ___| |    | |\n\
| .  . | | | |  \\| | | | \\ `--.| |_| || |__ | |    | |\n\
| |\\/| | | | | . ` | | |  `--. \\  _  ||  __|| |    | |\n\
| |  | |_| |_| |\\  |_| |_/\\__/ / | | || |___| |____| |____\n\
\\_|  |_/\\___/\\_| \\_/\\___/\\____/\\_| |_/\\____/\\_____/\\_____/\n\
\033[0m"

#endif