#include "mini.h"

void	get_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		printf("%s\n", path);
		free(path);
	}
	else if (!path)
		write(2, "error to path\n", 14);
}

void	exec(char **args, char **envp)
{
	char *path;

	path = ft_strjoin("/bin/", args[0]);
	if (execve(path, args, envp) == -1)
		printf("command not found: %s", args[0]);
	free(path);
	printf("\n");
}
void procces_cmd(char **s, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		exec(s, envp);
	else
		waitpid(pid, NULL, 0);
}
int check_cmd(char **s, char **envp)
{
	if (!ft_strncmp(s[0], "env", 3) && ft_strlen(s[0]) == 3)
		env(envp);
	else if (!ft_strncmp(s[0], "pwd", 3) && ft_strlen(s[0]) == 3)
		get_pwd();
	else if (!ft_strncmp(s[0], "cd", 2) && ft_strlen(s[0]) == 2)
		cd_cmd(s, envp);
	else
		procces_cmd(s, envp);
	return (0);
}
int main(int ac, char **av, char **envp)
{
	char *input;
	char **cmds;

	while (1)
	{
		input = readline("\033[32mminishell$>\033[0m ");
		if (!input)
		{
			printf("\n");
			break;
		}
		if (input)
			add_history(input);
		cmds  = ft_split(input, ' ');
		if (!*cmds || !cmds[0])
		{
			free(input);
			free_args(cmds);
			continue;
		}
		check_cmd(cmds, envp);
		free(input);
		free_args(cmds);
	}
	
}