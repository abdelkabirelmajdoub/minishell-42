/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:53:21 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/06/10 17:56:01 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_operator(char *input, int *i, t_token **head)
{
	char			*token_value;
	t_token_type	type;
	t_token			*current;

	type = tokenize_type(input, i);
	token_value = malloc (3);
	if (!token_value)
		return ;
	token_value[0] = input [*i];
	if (type == REDIR_APPEND)
		token_value[1] = '>';
	else if (type == REDIR_HEREDOC)
		token_value[1] = '<';
	token_value[2] = '\0';
	current = token_creation(token_value, type);
	free(token_value);
	token_add_back(head, current);
	(*i)++;
}

int	handle_quoted(char *input, int *i, t_token **head)
{
	char	quote;
	int		start;
	char	*token_value;
	t_token	*current;
	
	current = NULL;
	quote = input[(*i)++];
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == '\0')
	{
		ft_putstr_fd("syntax error near unexpected token \n", 2);
		return (0);
	}
	token_value = ft_strndup(&input[start], (*i) - start);
	current = token_creation(token_value, WORD);
	free(token_value);
	current->quote_type = quote;
	token_add_back(head, current);
	if (input[*i] == quote)
		(*i)++;
	return (1);
}

void handle_word(char *input, int *i, t_token **head, t_env *env)
{
    int j = 0;
    char quote;
    char buffer[1024];
    char tmp[1024];
    t_token *current;
    int has_single_quotes = 0;
    int has_double_quotes = 0;
    int is_str_quoted = 0;

    while (input[*i] && !(input[*i] == ' '
            || input[*i] == '\t' || input[*i] == '\n'
            || input[*i] == '|' || input[*i] == '<' || input[*i] == '>'))
    {
        if (input[*i] == '$' && (input[*i + 1] == '\'' || input[*i + 1] == '"'))
        {
            quote = input[*i + 1];
            (*i) += 2;
            int k = 0;
            while (input[*i] && input[*i] != quote)
                tmp[k++] = input[(*i)++];
            tmp[k] = '\0';
            if (input[*i] == quote)
                (*i)++;
            ft_memcpy(buffer + j, tmp, k);
            j += k;
            continue;
        }
        if ((input[*i] == '\'' || input[*i] == '"'))
        {
            int k = 0;
            quote = input[(*i)];
            (*i)++;
            while (input[*i] && input[*i] != quote)
                tmp[k++] = input[(*i)++];
            tmp[k] = '\0';
            if (input[*i] == '\0')
            {
                ft_putstr_fd("syntax error near unexpected token\n", 2);
                return;
            }
            if (input[*i] == quote)
                (*i)++;
            if (k == 0) // Detect ""
                is_str_quoted = 1;

            if (quote == '\'')
            {
                has_single_quotes = 1;
                ft_memcpy(buffer + j, tmp, k);
                j += k;
            }
            else if (quote == '"')
            {
                has_double_quotes = 1;
                char *expanded = expand_variable(tmp, env);
                if (expanded)
                {
                    int len = ft_strlen(expanded);
                    ft_memcpy(buffer + j, expanded, len);
                    j += len;
                    free(expanded);
                }
            }
        }
        else if (input[*i] == '$')
        {
            if (input[*i + 1] == '?')
            {
                char *exit_str = ft_itoa(env->exit_status);
                int len = ft_strlen(exit_str);
                ft_memcpy(buffer + j, exit_str, len);
                j += len;
                free(exit_str);
                *i += 2;
            }
            else if (input[*i + 1] && (ft_isalpha(input[*i + 1]) || input[*i + 1] == '_'))
            {
                char var_name[256];
                int k = 0;
                (*i)++;
                while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
                    var_name[k++] = input[(*i)++];
                var_name[k] = '\0';

                char *var_value = get_env(var_name, env);
                if (var_value)
                {
                    int len = ft_strlen(var_value);
                    ft_memcpy(buffer + j, var_value, len);
                    j += len;
                }
            }
            else
                buffer[j++] = input[(*i)++];
        }
        else
            buffer[j++] = input[(*i)++];
    }
    buffer[j] = '\0';
    if (j == 0 && !is_str_quoted)
        return;
    current = token_creation(buffer, WORD);
    if (has_single_quotes)
        current->quote_type = '\'';
    else if (has_double_quotes)
        current->quote_type = '"';
    token_add_back(head, current);
}

t_token	*tokenize(char *input, t_env *env)
{
	int			i;
	t_token		*head;

	i = 0;
	head = NULL;
	while (input[i] != '\0')
	{
		if (input[i] == 32 || (input[i] >= 9 && input[i] <= 13))
		{
			i++;
			continue ;
		}
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			handle_operator(input, &i, &head);
			continue ;
		}
		if (input[i] == 92)
			i++;
		else
			handle_word(input, &i, &head, env);
	}
	return (head);
}

