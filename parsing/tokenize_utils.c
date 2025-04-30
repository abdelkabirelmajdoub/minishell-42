/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:13:00 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/04/30 09:15:40 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

token	*token_creation(char *value, token_type type)
{
	token	*new_token;
	
	new_token = malloc (sizeof(token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);// my change ae-majd
}

void	token_add_back(token **head, token *new_token)
{
	token	*tmp;
	if (!*head)
		*head = new_token;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

token_type	tokenize_type(char *input, int *i)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		(*i)++;
		return (REDIR_APPEND);
	}
	else if (input[*i] == '|')
		return (PIPE);
	else if (input[*i] == '<')
		return (REDIR_IN);
	else if (input[*i] == '>')
		return (REDIR_OUT);
	return (WORD);// my change ae-majd
}