/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:57:44 by ael-majd          #+#    #+#             */
/*   Updated: 2025/06/10 11:36:31 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_var(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}

int	ft_unset(char *var, t_env **my_env)
{
	t_env	*current;
	t_env	*prev;

	if (!var)
		return (0);
	current = *my_env;
	prev = NULL;
	while (current)
	{
		if (!ft_strncmp(var, current->key, ft_strlen(var)))
		{
			if (prev)
				prev->next = current->next;
			else
				*my_env = current->next;
			remove_var(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
