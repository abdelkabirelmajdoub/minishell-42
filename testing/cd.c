#include "mini.h"

// void run_cd(char *path)
// {
// 	if (chdir(path) == -1)
// 		perror("cd");
// }
void run_cd(char *path)
{
	if (chdir(path) == -1)
		perror("cd");
}

void free_args(char **args)
{
	int i;	

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
void	cd_cmd(char **args, char **envp)
{
	if (args[1])
		run_cd(args[1]);
	else
		run_cd(getenv("HOME"));
}