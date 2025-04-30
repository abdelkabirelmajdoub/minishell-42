/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:20:26 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/04/30 09:45:48 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "../libft/libft.h"
typedef enum s_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
}	token_type;

typedef struct s_token
{
	char			*value;
	token_type		type;
	struct s_token	*next;
}	token;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*out_file;
	char			*append;
	struct s_cmd	*next;
} t_cmd;

char		*ft_strdup(const char *s1);
token_type	tokenize_type(char *input, int *i);
token		*token_creation(char *value, token_type type);
void		token_add_back(token **head, token *new_token);
token		*tokenize(char *input);
t_cmd		*pars_token(token	*tok);


/// execution
 
char	*get_path(char *cmd, char **env);
void	exe(t_cmd  *cmd_list, char **env);

#endif