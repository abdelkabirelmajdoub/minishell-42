/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:43:02 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/06/22 11:58:16 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_quotes(char *input, int *i, t_env *env)
{
	char	quote;
	char	tmp[1024];
	int		k;

	quote = input[*i];
	k = extract_quoted_content(input, i, tmp);
	if (k == -1)
		return ;
	if (k == 0)
		env->is_str_quoted = 1;
	if (quote == '\'')
		handle_single_quote_content(tmp, k, env);
	else if (quote == '"')
		handle_double_quote_content(tmp, env);
}

void	process_word_content(char *input, int *i, t_env *env, t_token **head)
{
	t_token	*last_tok;

	last_tok = get_last_token(head);
	if (input[*i] == '$' && (input[*i + 1] == '\'' || input[*i + 1] == '"'))
		handle_c_quoting(input, i, env->buffer, &env->j);
	else if (input[*i] == '\'' || input[*i] == '"')
		process_quotes(input, i, env);
	else if (input[*i] == '$' && last_tok 
		&& last_tok->type != REDIR_HEREDOC)
		handle_dollar_sign(input, i, env);
	else
		env->buffer[env->j++] = input[(*i)++];
}

void	init_word_vars(t_env *env)
{
	env->j = 0;
	env->has_single = 0;
	env->has_double = 0;
	env->is_str_quoted = 0;
}

void	create_word_token(t_token **head, t_env *env)
{
	t_token	*current;

	env->buffer[env->j] = '\0';
	if (env->j == 0 && !env->is_str_quoted)
		return ;
	current = token_creation(env->buffer, WORD);
	if (env->has_single)
		current->quote_type = '\'';
	else if (env->has_double)
		current->quote_type = '"';
	token_add_back(head, current);
}

void	handle_word(char *input, int *i, t_token **head, t_env *env)
{
	init_word_vars(env);
	while (input[*i] && !is_word_delimiter(input[*i]))
		process_word_content(input, i, env, head);
	create_word_token(head, env);
}
