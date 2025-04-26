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