/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:20:26 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/04/30 12:37:11 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef enum s_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
}	t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*out_file;
	char			*append;
	struct s_cmd	*next;
}	t_cmd;

char			*ft_strndup(const char *s, int size);
t_token_type	tokenize_type(char *input, int *i);
t_token			*token_creation(char *value, t_token_type type);
void			token_add_back(t_token **head, t_token *new_token);
t_token			*tokenize(char *input);
t_cmd			*pars_token(t_token	*tok);
void			handle_word(char *input, int *i, t_token **head);
void			handle_quoted(char *input, int *i, t_token **head);
void			handle_operator(char *input, int *i, t_token **head);
int				init_cmd(t_cmd **cmd, char ***args);
#endif