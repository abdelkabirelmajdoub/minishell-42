/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:20:26 by yazlaigi          #+#    #+#             */
/*   Updated: 2025/04/26 11:20:27 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

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
#endif