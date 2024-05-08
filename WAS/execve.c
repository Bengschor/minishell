#include "minishell.h"

int do_ls(char **env)
{
	int id = fork();
	if (id == 0)
	{
		char *arg[] = {"ls", NULL};
		execve("/bin/ls", arg, env);
		return (0);
	}
	waitpid(id, NULL, 0);
	return (1);
}
int do_clear(char **env)
{
	int id = fork();
	if (id == 0)
	{
		char *arg[] = {"clear", NULL};
		execve("/usr/bin/clear", arg, env);
		return (0);
	}
	waitpid(id, NULL, 0);
	return (1);
}

// int do_grep(char **env, char *str, int fd)
// {
	
// }