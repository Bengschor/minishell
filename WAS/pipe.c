#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void close_child(int **fd, int i, int const nbr_process)
{
	int j = 0;
	while (j < nbr_process + 1)
	{
		if (i != j)
			close(fd[j][0]);
		if (i + 1 != j)
			close(fd[j][1]);
		j++;
	}
}
void close_parent(int **fd, int i, int const nbr_process)
{
	int j;

	j = 0;
	while (j < nbr_process + 1)
	{
		if (nbr_process != j)
			close(fd[j][0]);
		if (0 != j)
			close(fd[j][1]);
		j++;
	}
}

void child_action(int **fd, int i)
{
	int x;

	if (read(fd[i][0], &x, sizeof(int)) == -1)
	{
		printf("error read 1\n");
		return 0;
	}
	printf("id %d got %d\n", i, x);
	//action child
	if (write(fd[i + 1][1], &x, sizeof(int)) == -1)
	{
		printf("error write\n");
		return (0);
	}
	printf("id %d send %d\n", i , x);
	close(fd[i][0]);
	close(fd[i + 1][1]);
}

void	parent_action(int **fd)
{
	int y;

	i = 0;
	if (write(fd[0][1], &y, sizeof(int)) == -1)
	{
		printf("error write\n");
		return (0);
	}
	if (read(fd[nbr_process][0], &y, sizeof(int)) == -1)
	{
		printf("error read 2\n");
		return (0);
	}
	printf("res :%d\n", y);
	close(fd[0][1]);
	close(fd[nbr_process][0]);
}

int super_pipex(int const nbr_process, char **argv)
{
	int fd[nbr_process + 1][2];
	int id[nbr_process];
	int i;
	int j;

	i = 0;
	while (i < nbr_process + 1)
	{
		if (pipe(fd[i]) == -1)
		{
			printf("error pipe\n");
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < nbr_process)
	{

		id[i] = fork();
		if (id[i] == -1)
		{
			printf("error fork\n");
			return (0);
		}
		if (id[i] == 0)
		{
			close_all(fd, i, nbr_process);
			child_action(fd, i);
			return (0);
		}
		i++;
	}
	j = 0;
	close_child(fd, i, nbr_process);
	parent_action(fd);
	i = 0;
	while (i < nbr_process)
	{
		wait(NULL);
		i++;
	}

	return 0;
}
