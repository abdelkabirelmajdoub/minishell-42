/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cnv_env_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:03:46 by ael-majd          #+#    #+#             */
/*   Updated: 2025/06/10 11:35:33 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_count(t_env **env)
{
	int		count;
	t_env	*tmp;

	tmp = *env;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(joined, s1, len1);
	ft_memcpy(joined + len1, s2, len2);
	joined[len1 + len2] = '\0';
	free(s1);
	return (joined);
}

int	count_non_null(t_env **env)
{
	t_env	*tmp;
	int		count;

	count = 0;
	tmp = *env;
	while (tmp)
	{
		if (tmp->value != NULL)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**env_list_to_array(t_env **env)
{
	t_env	*cur;
	int		count;
	char	**arr;
	char	*tmp;

	count = count_non_null(env);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	cur = *env;
	count = 0;
	while (cur)
	{
		if (cur->value != NULL)
		{
			tmp = ft_strjoin(cur->key, "=");
			arr[count++] = ft_strjoin(tmp, cur->value);
			free(tmp);
		}
		cur = cur->next;
	}
	arr[count] = NULL;
	return (arr);
}
