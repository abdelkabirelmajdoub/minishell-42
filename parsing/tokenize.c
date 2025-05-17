/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:53:21 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/05/17 12:29:11 by yazlaigi         ###   ########.fr       */
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
		printf("syntax error near unexpected token \n");
		current->error = 0;
		return (0);
	}
	token_value = ft_strndup(&input[start], (*i) - start);
	current = token_creation(token_value, WORD);
	current->quote_type = quote;
	token_add_back(head, current);
	if (input[*i] == quote)
		(*i)++;
	return (1);
}

void	handle_word(char *input, int *i, t_token **head, t_env *env)
{
	int		j;
	char	quote;
	char	buffer[1024];
	char	tmp[1024];
	t_token	*current;

	j = 0;
	while (input[*i] && !(input[*i] == ' '
			|| input[*i] == '\t' || input[*i] == '\n'
			|| input[*i] == '|' || input[*i] == '<' || input[*i] == '>'))
		{
			if (input[*i] == '\'' || input[*i] == '"')
			{
				int k = 0;
				quote = input[(*i)++];
				while (input[*i] && input[*i] != quote )
					tmp[k++] = input[(*i)++];
				tmp[k] = '\0';
				if (input[*i] == '\0')
					printf("syntax error near unexpected token \n");
				if (input[*i] == quote)
					(*i)++;
				if (quote == '"') // expand in double quotes
				{
					char *expanded = expand_variable(tmp, env);
					int len = ft_strlen(expanded);
					ft_memcpy(buffer + j, expanded, len);
					j += len;
					free(expanded);
				}
				else
				{
					ft_memcpy(buffer + j, tmp, k);
					j += k;
				}
			}
			else
				buffer[j++] = input[(*i)++];		
		}
	buffer[j] = '\0';
	char	*expanded = expand_variable(buffer, env);
	current = token_creation(expanded , WORD);
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
		if ((input[i] == '\'' || input[i] == '"'))
			handle_quoted(input, &i, &head);
		else
			handle_word(input, &i, &head, env);
	}
	return (head);
}

// void	print_parsed_cmds(t_cmd *cmd_list)
// {
// 	int	i;
// 	int	cmd_n;

// 	cmd_n = 1;
// 	while (cmd_list)
// 	{
// 		printf("-------- CMD #%d --------\n", cmd_n++);
// 		if (cmd_list->args)
// 		{
// 			i = 0;
// 			while (cmd_list->args[i])
// 			{
// 				printf("arg[%d]: %s\n", i, cmd_list->args[i]);
// 				i++;
// 			}
// 		}
// 		if (cmd_list->infile)
// 			printf("infile: %s\n", cmd_list->infile);
// 		if (cmd_list->out_file)
// 			printf("outfile: %s\n", cmd_list->out_file);
// 		if (cmd_list->append)
// 			printf("append: %s\n", cmd_list->append);
// 		if (cmd_list->limiter)
// 			printf("limiter: %s\n", cmd_list->limiter);
// 		printf("-------------------------\n"); 
// 		cmd_list = cmd_list->next;
// 	}
// }

// int	main(void)
// {
// 	char *input = readline("$ ");
// 	t_token *tokens = tokenize(input);
// 	t_cmd *cmds = pars_token(tokens);
// 	print_parsed_cmds(cmds);
// 	return (0);
// }