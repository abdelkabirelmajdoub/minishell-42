/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:40:06 by ael-majd          #+#    #+#             */
/*   Updated: 2025/05/13 15:41:58 by ael-majd         ###   ########.fr       */
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

/*--------------------------- Structs----------------------*/

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	int				exit_status;
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
	char				quote_type;
	struct s_token		*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			**out_file;
	char			*append;
	char			*limiter;
	int				heredoc_fd;
	struct s_cmd	*next;
}	t_cmd;


typedef struct s_exe_pipe
{
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;
	char	**envp;
	int		status;
	pid_t	last_pid;
	t_cmd	*last_cmd;
}			t_exe_pipe;


/*---------------------------------- lib-helper --------------------------------------*/
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strndup(const char *s, int size);

/*---------------------------------- Parsing functions --------------------------------------*/

t_token_type	tokenize_type(char *input, int *i);
t_token			*token_creation(char *value, t_token_type type);
void			token_add_back(t_token **head, t_token *new_token);
t_token			*tokenize(char *input);
t_cmd			*pars_token(t_token	*tok);
void			handle_word(char *input, int *i, t_token **head);
void			handle_operator(char *input, int *i, t_token **head);
int				init_cmd(t_cmd **cmd, char ***args);
t_cmd			*pars_int(void);
int				handle_syn(char *input, t_token *tok);
int				handle_syn_helper(t_token *cpy_tok);
char			*get_env(char *key, t_env *env);
char			*expand_variable(char *value,t_env *env);
void			expend_token(t_token *tokens, t_env *env);
void			handle_quotes(t_token *tokens);
int				handle_quoted(char *input, int *i, t_token **head);
void			clean_empty_tokens(t_token **tokens);
/*---------------------------------- BUILT-in cmds --------------------------------------*/

int		ft_unset(char *var, t_env **my_env);
int		ft_cd(char **args, t_env **env);
int		ft_pwd(void);
int		ft_exit(char **args);
int		ft_echo(char **args, t_env **env);
int		ft_export(t_env **env, char **args);
int		ft_env(t_env **tmp);
void	inc_lvl(t_env **env);

// -------- envirement Utils -----//

char	**env_list_to_array(t_env **env);
t_env	*creat_env(char **env);
t_env	*new_env_node(char *key, char *value);
void	env_add_back(t_env **env, t_env *new_node);
char	*get_env(char *key, t_env *env);

/*---------------------------------- execution cmds --------------------------------------*/

int		run_builtin(t_cmd *cmd, t_env **env);
int		is_builtin(char *cmd);
char	*get_path(char *cmd, char **env);
void	exe(t_cmd  *cmd_list, t_env **env);
void	execute_pipe(t_cmd *cmd, t_env **env);
int		is_pipe(t_cmd *cmd_list);
void	handle_heredoc(t_cmd *cmd);
void	run_heredoc(char *limiter, int	write_end);
void	prepare_heredocs(t_cmd *cmd_list);


//-----------------files descriptors---------//

void	redirect_in(char *filename);
void	redirect_out(t_cmd *cmd);
void	x_pipe(int pipefd[2]);
void	x_dup2(int fd, int target_fd);
/*---------------------------------- cleaning --------------------------------------*/

void	free_env(t_env *env);
void	free_cmd(t_cmd *cmd);
void 	free_args(char **args);
void	free_tokens(t_token *tok);

#endif