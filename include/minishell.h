/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:40:06 by ael-majd          #+#    #+#             */
/*   Updated: 2025/06/22 12:53:43 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <limits.h>
# define SYNTHAX_PIPE "minishell: syntax error near unexpected token `|'\n"
# define SYNTHAX_RED "minishell: syntax error near unexpected token `newline'\n"
/*--------------------------- Structs----------------------*/
extern int	g_exit_code;
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	int				exit_status;
	char			buffer[1024];
	int				j;
	int				has_single;
	int				has_double;
	int				is_str_quoted;
	int				hdoc_expand;
}					t_env;

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
}						t_token;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			**out_file;
	char			*append;
	char			*limiter;
	int				heredoc_fd;
	struct s_cmd	*next;
}					t_cmd;

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

typedef struct s_export_data
{
	char	*key;
	char	*value;
	int		append;
	char	*_arg;
}			t_export_data;

/*-------- lib-helper ------------*/
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strndup(const char *s, int size);
char			**advance_split(char *s);
/*-------- Parsing functions ------------*/
t_token_type	tokenize_type(char *input, int *i);
t_token			*token_creation(char *value, t_token_type type);
t_token			*tokenize(char *input, t_env *env);
t_cmd			*pars_token(t_token	*tok);
t_cmd			*pars_int(void);
char			**args_allocation(void);
int				init_cmd(t_cmd **cmd, char ***args);
int				handle_syn(char *input, t_token *tok, t_env **env);
int				handle_syn_helper(t_token *cpy_tok, t_env **env);
int				handle_quoted(char *input, int *i, t_token **head);
char			*get_env(char *key, t_env *env);
char			*expand_variable(char *value, t_env *env);
void			token_add_back(t_token **head, t_token *new_token);
void			expend_token(t_token *tokens, t_env *env);
void			handle_quotes(t_token *tokens);
void			handle_word(char *input, int *i, t_token **head, t_env *env);
void			handle_operator(char *input, int *i, t_token **head);
void			clean_empty_tokens(t_token **tokens);
int				unclosed_quotes(const char *input);
int				handle_exit_status(t_env *env, int *i);
int				handle_variable(char *value, t_env *env, 
					char *var_name, int *i);
void			copy_exit_status(t_env *env, char *result, int *j, int *i);
int				extract_var_name(char *value, char *var_name, int *i);
void			copy_var_value(char *var_value, char *result, int *j);
char			*allocate_result(char *value, t_env *env);
void			process_expansion(char *value, t_env *env, char *result);
void			remove_token(t_token **tokens, t_token *current, t_token *prev);
void			expand_word_token(t_token *tok, t_env *env);
void			remove_quotes_from_token(t_token *tok);
void			handle_exit_status2(char *input, int *i, t_env *env);
void			handle_variable_expansion(char *input, int *i, t_env *env);
void			handle_dollar_sign(char *input, int *i, t_env *env);
int				is_word_delimiter(char c);
int				extract_quoted_content(char *input, int *i, char *tmp);
void			handle_single_quote_content(char *tmp, int k, t_env *env);
void			handle_double_quote_content(char *tmp, t_env *env);
void			process_quotes(char *input, int *i, t_env *env);
void			process_word_content(char *input, int *i, t_env *env, 
					t_token **head);
void			init_word_vars(t_env *env);
void			create_word_token(t_token **head, t_env *env);
void			pars_helper2(t_token **tok, t_cmd *cmd, int *i);
void			process_input_char(char *input, int *i, 
					t_token **head, t_env *env);
void			handle_c_quoting(char *input, int *i, char *buffer, int *j);
int				expand_variable_helper(char *value, t_env *env, 
					char *var_name, int t_len);
t_token			*get_last_token(t_token **head);
void			limiter_check(char *input, t_env **env);
/*--------- BUILT-in cmds -------------*/
int				ft_unset(char *var, t_env **my_env);
int				ft_cd(char **args, t_env **env);
int				out_exist(t_cmd *cmd);
int				ft_pwd(void);
int				ft_exit(char **args, t_env **env);
int				ft_echo(char **args);
//-----------
int				ft_export(t_env **env, char **args);
int				is_valid_key(char *key);
int				print_export(t_env *env);
//-----------
int				ft_env(t_env **tmp);
void			inc_lvl(t_env **env);

// -------- envirement Utils -----//

char			**env_list_to_array(t_env **env);
t_env			*creat_env(char **env);
t_env			*new_env_node(char *key, char *value);
void			env_add_back(t_env **env, t_env *new_node);
char			*get_env(char *key, t_env *env);
int				env_count(t_env **env);
t_env			**env_to_array(t_env *env);

/*------------- execution cmds -----------------*/

int				run_builtin(t_cmd *cmd, t_env **env);
int				is_builtin(char *cmd);
char			*get_path(char *cmd, char **env);
void			exe(t_cmd *cmd_list, t_env **env);
void			execute_pipe(t_cmd *cmd, t_env **env);
int				is_pipe(t_cmd *cmd_list);
void			handle_heredoc(t_cmd *cmd);
void			run_heredoc(char *limiter, int write_end, t_env **env);
int				prepare_heredocs(t_cmd *cmd_list, t_env **env);
//-----------------files descriptors---------/
void			redirect_in(char *filename);
void			redirect_out(t_cmd *cmd);
void			x_pipe(int pipefd[2]);
void			x_dup2(int fd, int target_fd);
/*------- cleaning -----------*/
void			free_env(t_env *env);
void			free_cmd(t_cmd *cmd);
void			free_args(char **args);
void			free_tokens(t_token *tok);
/*------- signals -----------*/
void			set_signals(void);
void			set_terminal_echoctl(void);
#endif