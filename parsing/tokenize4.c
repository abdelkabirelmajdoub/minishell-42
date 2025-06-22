/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:44:22 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/06/22 12:46:31 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_input_char(char *input, int *i, t_token **head, t_env *env)
{
	if (input[*i] == 32 || (input[*i] >= 9 && input[*i] <= 13))
	{
		(*i)++;
		return ;
	}
	if (input[*i] == '|' || input[*i] == '>' || input[*i] == '<')
	{
		handle_operator(input, i, head);
		return ;
	}
	if (input[*i] == 92)
		(*i)++;
	else
		handle_word(input, i, head, env);
}

t_token	*tokenize(char *input, t_env *env)
{
	int		i;
	t_token	*head;

	i = 0;
	head = NULL;
	while (input[i] != '\0')
		process_input_char(input, &i, &head, env);
	return (head);
}

t_token	*get_last_token(t_token **head)
{
	t_token	*current;

	if (!head || !*head)
		return (NULL);
	current = *head;
	while (current->next)
		current = current->next;
	return (current);
}

void	limiter_check(char *input, t_env **env)
{
	int		i;
	char	**args;

	args = advance_split(input);
	(*env)->hdoc_expand = 0;
	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "<<") && args[i + 1])
		{
			i++;
			if (ft_strchr(args[i], '"') || ft_strchr(args[i], '\''))
				(*env)->hdoc_expand = 1;
			else
				(*env)->hdoc_expand = 0;
		}
		i++;
	}
	free_args(args);
}
