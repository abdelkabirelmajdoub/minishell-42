/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:13:00 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/05/15 11:39:30 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*pars_int(void)
{
	t_cmd	*cmd;

	cmd = malloc (sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->out_file = NULL;
	cmd->append = NULL;
	cmd->limiter = NULL;
	cmd->next = NULL;
	return (cmd);
}

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
	while (s[++i] && i < size)
		str[i] = s[i];
	str[i] = '\0';
	return (str);
}

t_token	*token_creation(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = malloc (sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	token_add_back(t_token **head, t_token *new_token)
{
	t_token	*tmp;

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

t_token_type	tokenize_type(char *input, int *i)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		(*i)++;
		return (REDIR_APPEND);
	}
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		(*i)++;
		return (REDIR_HEREDOC);
	}
	else if (input[*i] == '|')
		return (PIPE);
	else if (input[*i] == '<')
		return (REDIR_IN);
	else if (input[*i] == '>')
		return (REDIR_OUT);
	return (WORD);
}
