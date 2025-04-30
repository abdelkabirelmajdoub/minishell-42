/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:53:21 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/04/30 10:03:56 by ael-majd         ###   ########.fr       */
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
		{
			i++;
			continue;
		}
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			type = tokenize_type(input, &i);
			token_value = malloc (3);
			token_value[0] = input [i];
			if (type == REDIR_APPEND)
				token_value[1] = '>';
			token_value[2] = '\0';
			current = token_creation(token_value, type);
			token_add_back(&head, current);
			i++;
			continue;
		}
		if (input[i] == '\'' || input[i] == '"')
		{
			char quote = input[i++];
			start = i;
			while (input[i] && input[i] != quote)
				i++;
			token_value = ft_strndup(&input[start], i - start);
			current = token_creation(token_value, WORD);
			token_add_back(&head, current);
			if (input[i] == quote)
			i++; // skip the closing quote
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

t_cmd	*pars_token(token	*tok)
{
	t_cmd	*head = NULL;
	t_cmd	*current = NULL;
	t_cmd	*cmd;
	char	**args;
	int		argc;

	while (tok)
	{
		cmd = malloc (sizeof(t_cmd));
		if (!cmd)
			return (NULL);
        cmd->args = NULL;
		cmd->infile = NULL;
		cmd->out_file = NULL;
		cmd->append = NULL;
		cmd->next = NULL;
		args = malloc (sizeof(char *) * 100);
		argc = 0;
		while (tok && tok->type != PIPE)
		{
			if (tok->type == REDIR_IN && tok->next)
			{
				cmd->infile = tok->next->value;
				tok = tok->next->next;
				continue;
			}
			else if (tok->type == REDIR_OUT && tok->next)
			{
				cmd->out_file = tok->next->value;
				tok = tok->next->next;
				continue;
			}
			else if (tok->type == REDIR_APPEND && tok->next)
			{
				cmd->append = tok->next->value;
				tok = tok->next->next;
				continue;
			}
			else if (tok->type == WORD)
				args[argc++] = tok->value;
			tok = tok->next;
		}
		args[argc] = NULL;
		cmd->args = args;
		if (!head)
			head = cmd;
		else
			current->next = cmd;
		current = cmd;
		if (tok && tok->type == PIPE)
			tok = tok->next;
	}
	return (head);
}


void	print_parsed_cmds(t_cmd *cmd_list)
{
	int i;
	int cmd_n = 1;

	while (cmd_list)
	{
		printf("-------- CMD #%d --------\n", cmd_n++);
		if (cmd_list->args)
		{
			i = 0;
			while (cmd_list->args[i])
			{
				printf("arg[%d]: %s\n", i, cmd_list->args[i]);
				i++;
			}
		}
		if (cmd_list->infile)
			printf("infile: %s\n", cmd_list->infile);
		if (cmd_list->out_file)
			printf("outfile: %s\n", cmd_list->out_file);
		if (cmd_list->append)
			printf("append: %s\n", cmd_list->append);
		printf("-------------------------\n");
		printf("the infile:  %s\n outfile: %s append: %s\n", cmd_list->infile, cmd_list->out_file, cmd_list->append);
		cmd_list = cmd_list->next;
	}
}

int	main(int ac, char **av, char **env)
{
	while(1)
	{
		char *input = readline("\033[32mminishell$>\033[0m ");
		token *tokens = tokenize(input);
		t_cmd *cmds = pars_token(tokens);
		exe(cmds, env);
		// print_parsed_cmds(cmds);
	}

	(void)ac;
	(void)av;
	return (0);
}
