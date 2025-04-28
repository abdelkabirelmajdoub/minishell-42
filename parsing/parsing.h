/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:20:26 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/04/28 10:57:51 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
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

char		*ft_strdup(const char *s1);
token_type	tokenize_type(char *input, int *i);
token		*token_creation(char *value, token_type type);
void		token_add_back(token **head, token *new_token);
token		*tokenize(char *input);
#endif