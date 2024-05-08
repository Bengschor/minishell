#include "minishell.h"

int do_echo(int argc, char **argv)
{
	int i;
	int nw_line;

	nw_line = 1;
	i = 1;
	if (if_same_word(argv[i] , "-n"))
	{
		nw_line = 0;
		i++;
	}
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
	if (nw_line)
		printf("\n");
	return 1;
}

int do_cd(const char *path, t_shell *shell) 
{
	char *str;
	(void)shell;
	if (if_same_word((char*)path, "-"))
	{
		str = getenv("OLDPWD");//ft_getenv 
		chdir(str);
		return (0);
	}
    if (chdir(path) != 0) {
        ft_putstr_fd("cd: no such file or directory: ", 2);
        ft_putstr_fd((char*) path, 2);
        ft_putstr_fd("\n", 2);
        return (-1);
    }
    else
    	ch_oldpwd();
    return 0;
}

int do_pwd(int argc)
{
	char cwd[1024];

	if (argc == 1)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("%s\n",  cwd);
		else
			perror("getcwd");
	}
	else
		printf("pwd: too many arguments\n");
	return 1;
}

int do_env(int argc, char **env)
{
	int i;

	if (argc > 1)
	{
		printf("env: too many arguments\n");
		return (0);
	}
	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (1);
}

int do_exit()
{
	exit(1);
	return (0);
}