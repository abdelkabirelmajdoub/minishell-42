/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:32:11 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/05/13 12:42:52 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
int	expand_variable_helper(char *value,t_env *env, char *var_name, int total_len)
{
	int		i;
	char	*var_value;
	
	i = 0;
	total_len = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] == '?')
		{
			char *exit_str = ft_itoa(env->exit_status);
			total_len += ft_strlen(exit_str);
			free(exit_str);
			i += 2;
		}
		else if (value[i] == '$' && value[i + 1]
			&& (ft_isalpha(value[i + 1]) || value[i + 1] == '_'))
		{
			int k = 0;
			i++;
			while (value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
				var_name[k++] = value[i++];
			var_name[k] = '\0';
			var_value = get_env(var_name, env);
			if (var_value)
				total_len += ft_strlen(var_value);
		}
		else
		{
			total_len++;
			i++;
		}
	}
	return (total_len);
}

char	*expand_variable(char *value, t_env *env)
{
	char	*result;
	char	*exit_str;
	int		total_len = 0;
	int		i = 0, j = 0;
	char	*var_value;
	char	var_name[256];

	total_len = expand_variable_helper(value, env, var_name, total_len);
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] == '?')
		{
			exit_str = ft_itoa(env->exit_status);
			ft_memcpy(result + j, exit_str, ft_strlen(exit_str));
			j += ft_strlen(exit_str);
			free(exit_str);
			i += 2;
		}
		if (value[i] == '$' && value[i + 1]
			&& (ft_isalpha(value[i + 1]) || value[i + 1] == '_'))
		{
			int k = 0;
			i++;
			while (value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
				var_name[k++] = value[i++];
			var_name[k] = '\0';
			var_value = get_env(var_name, env);
			if (var_value)
			{
				int len = ft_strlen(var_value);
				ft_memcpy(result + j, var_value, len);
				j += len;
			}
			
		}
		else
			result[j++] = value[i++];
	}
	result[j] = '\0';
	return (result);
}

void	clean_empty_tokens(t_token **tokens)
{
	t_token *current = *tokens;
	t_token *prev = NULL;
	t_token *next;
	
	while (current)
	{
		next = current->next;
		if (current->type == WORD && current->value && current->value[0] == '\0')
		{
			if (prev)
				prev->next = next;
			else
				*tokens = next;
				
			free(current->value);
			free(current);
			current = next;
			continue;
		}
		
		prev = current;
		current = next;
	}
}

void	expend_token(t_token *tokens, t_env *env)
{
	t_token	*cpy_tok;
	char	*expanded;

	cpy_tok = tokens;
	while (cpy_tok)
	{
		if (cpy_tok->type == WORD && cpy_tok->quote_type != '\''
			&& ft_strchr (cpy_tok->value, '$'))
		{
			expanded = expand_variable(cpy_tok->value, env);
			if (expanded)
			{
				free(cpy_tok->value);
				cpy_tok->value = expanded;
			}
		}
		cpy_tok = cpy_tok->next;
	}
}

void	handle_quotes(t_token *tokens)
{
	t_token	*tok;
	char	*new_value;

	tok = tokens;
	while (tok)
	{
		if (tok->type == WORD)
		{
			if (ft_strlen(tok->value) >= 2 && (tok->value[0] == '\'' || tok->value[0] == '"') 
				&& tok->value[ft_strlen(tok->value) - 1] == tok->value[0])
			{
				new_value = ft_substr(tok->value, 1, ft_strlen(tok->value) - 2);
				free(tok->value);
				tok->value = new_value;
			}
		}
		tok = tok->next;

	}
}
