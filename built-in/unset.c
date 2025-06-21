/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:57:44 by ael-majd          #+#    #+#             */
/*   Updated: 2025/06/21 15:37:59 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_var(t_env *env)
{
	if (!env)
		return ;
	free(env->value);
	free(env);
}

int	key_check(char *var)
{
	if (!is_valid_key(var))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	return (1);
}

int	ft_unset(char *var, t_env **my_env)
{
	t_env	*current;
	t_env	*prev;

	if (!var)
		return (0);
	if (!key_check(var))
		return (1);
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
