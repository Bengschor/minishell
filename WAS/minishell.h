#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>


typedef struct s_shell
{
	char **env;
	char *input;
}	t_shell;
//main

//env
char *get_input();
int if_key(char *str, char **env);
int ft_setenv(char *key, char *value, char ***env, int size);

//split
size_t	ft_strlcpy(char *dest, char *src, size_t size);
int	free_tab(char **tab, int i);
unsigned long	count_words(char *s, char c);
int	add_str(char **str, char *s, char c);
char	**ft_split(char const *s, char c, int *ac);

//builtins
int do_echo(int argc, char **argv);
int do_cd(const char *path, t_shell *shell);
void	ch_oldpwd();
int do_pwd(int argc);
int do_env(int argc, char **env);
int do_exit();

//utils
int ft_strlen(char *str);
int if_blank(char c);
int	if_same_word(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
char **ft_split_in_2(char *str);

//utils2
int is_blank(char *str);
char *ft_strjoin(char *s1, char *s2);
int ft_setenv(char *key, char *value, char ***env, int size);
char *ft_strrchr(char *str, char c);

//do_unset
int get_pos(char *env, char c);
int if_in_env(char *var, char **env);
int do_unset(char **tab, int argc, char **env);
int get_res(char *str);
int do_export(int argc, char **tab, char ***env);

//execve
int do_ls(char **env);
int do_clear(char **env);

//tools
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putstr_fd(char *s, int fd);
char *join_and_free(char *s1, char *s2);
char	*ft_strdup(char *src);

#endif