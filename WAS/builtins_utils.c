#include "minishell.h"

void ch_oldpwd()
{
	char *str;
	char *str2;
	int i;

	str = getenv("OLDPWD");
	str2 = getenv("PWD");
	ft_bzero(str, ft_strlen(str));
	i = 0;
	while (str2[i])
	{
		str[i] = str2[i];
		i++;
	}
	str[i] = '\0';
}