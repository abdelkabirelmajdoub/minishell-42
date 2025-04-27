/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:53:52 by ael-majd          #+#    #+#             */
/*   Updated: 2025/04/27 13:55:13 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


int check_name(char *s)
{
    int i;

    if (!ft_isalpha(s[0]) && s[0] != '_')
        return (1);
    i = 1;
    while (s[i])
    {
        if (!ft_isalnum(s[i]) && s[i] != '_')
            return (1);
        i++;
    }
    return (0);
}


char *key_extract(char *s)
{
	int i;
	int j;
	char *key;

	i = 0;
	while(s[i] && s[i] != '=')
		i++;
	key = malloc(i);
	if (!key)
		return (NULL);
	j = 0;
	while (j < i)
	{
		key[j] = s[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

void	add_to_env(char *var, t_env **env)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env;
	while (tmp)
		tmp = tmp->next;
	new = new_env_node(key_extract(var), ft_strchr(var, '='));
	if (!new)
		return ;
	if (tmp)
		tmp->next = new;
	else 
		*env = new;
}

void	ft_export(char **s, t_env **my_env)
{
	if (!ft_strchr(s[1], '='))
		return ;
	// if (check_name(s[1]))
	// {
	// 	printf("export: %s: not a valid identifier\n", s[1]);
	// 	exit(1);
	// }
	add_to_env(s[1] , my_env);
}