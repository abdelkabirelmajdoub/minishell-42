/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:53:21 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/04/26 13:39:34 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// addd new function
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
////////////

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	if (!s1)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
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
token	*tokenize(char *input)
{
	int			i;
	token		*head;
	token		*current;
	char		*token_value;
	token_type	type;
	int			start;
	i = 0;
	head = NULL;
	while (input[i] != '\0')
	{
		if (input[i] == 32 || (input[i] >= 9 && input[i] <= 13))
			i++;
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			type = tokenize_type(input, &i);
			token_value = malloc (3);
			token_value[0] = input [i];
			if (type == REDIR_APPEND)
				token_value[1] = input[i + 1];
			token_value[2] = '\0';
			current = token_creation(token_value, type);
			token_add_back(&head, current);
		i++;
		}
		else
		{
			start = i;
			while (input[i] && !(input[i] == ' ' || input[i] == '\t' || input[i] == '\n'
				|| input[i] == '|' || input[i] == '<' || input[i] == '>'))
				i++;
			token_value = ft_strndup(&input[start], i - start);
			current = token_creation(token_value, WORD);
			token_add_back(&head, current);
		}
	}
	return (head);
}

int main()
{
	char *inpute = readline("promte> ");
	token *cmd = tokenize(inpute);
	while(cmd)
	{
		printf("args:[%s]	TYPE:[%u]\n", cmd->value, cmd->type);
		cmd = cmd->next;
	}
}

/*
	The output of this function:

	args:[<]        TYPE:[2]
	args:[infile]   TYPE:[0]
	args:[ls]       TYPE:[0]
	args:[-l]       TYPE:[0]
	args:[|]        TYPE:[1]
	args:[wc]       TYPE:[0]
	args:[-l]       TYPE:[0]
	args:[>]        TYPE:[3]
	args:[out]      TYPE:[0]

*/