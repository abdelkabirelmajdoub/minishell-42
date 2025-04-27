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

void	exec(char **args)
{
	char *path;

	path = ft_strjoin("/bin/", args[0]);
	if (execve(path, args, NULL) == -1)
		printf("command not found: %s", args[0]);
	free(path);
	printf("\n");
}
void procces_cmd(char **s)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		exec(s);
	else
		waitpid(pid, NULL, 0);
}
int check_cmd(char **s, t_env	**my_env)
{
	if (!ft_strncmp(s[0], "env", 3) && ft_strlen(s[0]) == 3)
		env(*my_env);
	else if (!ft_strncmp(s[0], "unset", 5) && ft_strlen(s[0]) == 5)
		ft_unset(s[1], my_env);
	else if (!ft_strncmp(s[0], "pwd", 3) && ft_strlen(s[0]) == 3)
		get_pwd();
	else if (!ft_strncmp(s[0], "cd", 2) && ft_strlen(s[0]) == 2)
		cd_cmd(s);
	else if (!ft_strncmp(s[0], "exit", 4) && ft_strlen(s[0]) == 4)
		minishell_exit(s);
	else if (!ft_strncmp(s[0], "export", 6) && ft_strlen(s[0]) == 6)
		ft_export(s, my_env);//////////////// BA9i masalitha
	else
		procces_cmd(s);
	return (0);
}
int main(int ac, char **av, char **envp)
{
	char	*input;
	char	**cmds;
	t_env	*my_env;

	my_env = creat_env(envp);
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
		check_cmd(cmds, &my_env);
		free(input);
		free_args(cmds);
	}
	(void)ac;
	(void)av;
	
}