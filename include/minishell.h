/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazlaigi <yazlaigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:01:29 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/06 10:27:38 by yazlaigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h> 
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <fcntl.h>

////// For parsing headers
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}		t_env;

typedef enum s_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
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
	char			*limiter;
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
t_cmd			*pars_int(void);
void			handle_syn(char *input, t_token *tok);
void			handle_syn_helper(t_token *cpy_tok);
char			*get_env(char *key, t_env *env);
char			*expand_variable(char *value,t_env *env);
void			*expend_token (t_token *tokens, t_env *env);
////// For execution headers

char	*get_path(char *cmd, char **env);
void	exe(t_cmd  *cmd_list, char **v_tmp, t_env **env);
void	handle_heredoc(t_cmd *cmd);
void	run_heredoc(char *limiter, int	write_end);



int		ft_unset(char *var, t_env **my_env);
int		ft_env(t_env **tmp);
int		ft_cd(char **args);
int		ft_pwd(void);
int		ft_exit(char **args);
int		ft_echo(char **args, t_env **env);
int		ft_export(t_env **env, char **args);
void 	free_args(char **args);
t_env	*new_env_node(char *key, char *value);
t_env	*creat_env(char **env);

/// for execute builtin
int	run_builtin(t_cmd *cmd, t_env **env);
int	is_builtin(char *cmd);


#endif