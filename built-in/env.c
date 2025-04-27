#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "mini.h"

char	*ft_strndup(const char *s, int size)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	i = -1;
	while(s[++i] && i < size)
		str[i] = s[i];
	str[i] = '\0';
	return (str);
}

t_env	*new_env_node(const char *key, const char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_env	*empty_env(void)
{
	t_env	*head;
	t_env	*current;
	t_env	*new;
	char	cwd[1337];

	head = NULL;
	current = NULL;
	head = new_env_node("PWD", getcwd(cwd, sizeof(cwd)));
	if (!head)
		return (NULL);
	current = head;
	new = new_env_node("SHLVL", "1");
	if (!new)
		return (NULL);
	current->next = new;
	current = new;
	new = new_env_node("_", "/usr/bin/env");
	if (!new)
		return (NULL);
	current->next = new;
	return (head);
}
t_env	*creat_env(char **env)
{
	t_env	*head;
	t_env	*current;
	t_env	*new;
	char	*eqaule_sign;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	if (!env || !env[0])
	{
		head = empty_env();
		return (head);
	}
	while(env[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		eqaule_sign = ft_strchr(env[i], '=');
		if (eqaule_sign)
		{
			new->key = ft_strndup(env[i], eqaule_sign - env[i]);
			new->value = ft_strdup(eqaule_sign + 1);
		}
		else
		{
			new->key = ft_strdup(env[i]);
			new->value = NULL;
		}
		new->next = NULL;
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
		i++;
	}
	return (head);
}
void	env(char **envp)
{
	t_env	*tmp;

	tmp = creat_env(envp);
	if (!tmp)
		return ;
	while(tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}