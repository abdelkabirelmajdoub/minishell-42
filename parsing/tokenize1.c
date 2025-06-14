/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:53:21 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/06/14 14:01:53 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_operator(char *input, int *i, t_token **head)
{
	char			*token_value;
	t_token_type	type;
	t_token			*current;

	type = tokenize_type(input, i);
	token_value = malloc(3);
	if (!token_value)
		return ;
	token_value[0] = input[*i];
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

void	handle_c_quoting(char *input, int *i, char *buffer, int *j)
{
	char	quote;
	char	tmp[1024];
	int		k;

	quote = input[*i + 1];
	(*i) += 2;
	k = 0;
	while (input[*i] && input[*i] != quote)
		tmp[k++] = input[(*i)++];
	tmp[k] = '\0';
	if (input[*i] == quote)
		(*i)++;
	ft_memcpy(buffer + *j, tmp, k);
	*j += k;
}

void	handle_exit_status2(char *input, int *i, t_env *env)
{
	char	*exit_str;
	int		len;
	char	*a;

	a = input;
	exit_str = ft_itoa(env->exit_status);
	len = ft_strlen(exit_str);
	ft_memcpy(env->buffer + env->j, exit_str, len);
	env->j += len;
	free(exit_str);
	*i += 2;
}

void	handle_variable_expansion(char *input, int *i, t_env *env)
{
	char	var_name[256];
	char	*var_value;
	int		k;
	int		len;

	k = 0;
	(*i)++;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		var_name[k++] = input[(*i)++];
	var_name[k] = '\0';
	var_value = get_env(var_name, env);
	if (var_value)
	{
		len = ft_strlen(var_value);
		ft_memcpy(env->buffer + env->j, var_value, len);
		env->j += len;
	}
}
