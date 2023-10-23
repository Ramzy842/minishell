/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:46:34 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/23 19:47:13 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

extern int	g_signal;

typedef enum s_tokens
{
	WORD = 0,
	INPUT = 1,
	OUTPUT = 2,
	APPEND = 3,
	HEREDOC = 4,
	PIPE = 5,
}	t_tokens;

typedef enum s_input_redirections {
	INPUT_NONE,
	IO_INPUT,
	IO_HEREDOC
}	t_input_redirections;

typedef enum s_output_redirections {
	OUTPUT_NONE,
	IO_OUTPUT,
	IO_APPEND
}	t_output_redirections;

typedef struct s_lexer
{
	int				id;
	char			*str;
	t_tokens		token;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_parser_data
{
	t_lexer			*lexer_list;
	int				number_of_redirections;
	t_lexer			*redirections;
	struct s_data	*data;
}	t_parser_data;

typedef struct s_data
{
	char					*shell_input;
	int						x;
	char					**paths;
	char					**envp;
	char					**envp_arr;
	struct s_commands		*commands;
	t_lexer					*lexer_list;
	char					*pwd;
	char					*old_pwd;
	int						pipes;
	int						*pid;
	int						heredoc;
	int						reset;
}			t_data;

typedef struct s_env {
	char					*key;
	char					*value;
	struct s_env			*next;
}	t_env;

typedef struct s_commands
{
	char					**command_args;
	t_input_redirections	i_redir;
	t_output_redirections	o_redir;
	char					*input_filename;
	char					*output_filename;
	char					*heredoc;
	int						in;
	int						out;
	struct s_commands		*next;
}	t_commands;

int			initialize_data(t_data *data);
int			quotes_are_matching(char *line);
int			tokens_reader(t_data *data);
int			handle_quotes(int x, char *str, char del);
int			handle_token(char *str, int x, t_lexer **lexer_list);
int			handle_words(int x, char *str, t_lexer **lexer_list);
t_tokens	extract_token(char c);

t_lexer		*create_lexer_node(char *str, int token);
void		append_node(t_lexer	**list, t_lexer *new_node);
int			add_node(char *str, t_tokens token, t_lexer **lexer_list);

// PARSER
int			launch_parser(t_data *data);
void		update_pipes_count(t_data *data);
t_commands	*parse_commands(t_data *data);
void		parser_error(int error,
				t_data *data, t_lexer *lexer_list);
void		remove_lexer_node(t_lexer **lst, int key);
int			parser_double_token_error(t_data *data,
				t_lexer *lexer_list, t_tokens token);
void		delete_first_lexer_node(t_lexer **lst);
void		lexer_error(int error, t_data *data);
t_lexer		*free_lexer_node(t_lexer **lst);
void		clear_lexer_nodes(t_lexer **lst);
int			ft_error(int error, t_data *data, t_env *env);
t_lexer		*expand_lexer(t_lexer *lexer_list, t_env *env);
// void		handle_args(t_commands *tmp,
// 				int *x, t_data *data, t_env *env, int status);
void	handle_args(t_commands *tmp, t_data *data, t_env *env, int status);
char		**realloc_arr(char	**old_arr, int increment);
int			get_list_length(void *head);

// REDIRECTIONS
int			redirect_append(t_commands *tmp,
				t_data *data, t_env *env, int status);
void		redirect_heredoc(t_commands *tmp,
				t_data *data, t_env *env, int status);
int			redirect_input(t_commands *tmp,
				t_data *data, t_env *env, int status);
int			redirect_output(t_commands *tmp,
				t_data *data, t_env *env, int status);
int			handle_redirections(t_data *data,
				t_commands *tmp, t_env *env, int status);
char		*ft_get_heredoc(char *heredoc,
				t_env *env, int status);

// REDIRECTIONS UTILS
int			is_metachar(char *str);
int			is_redir_op(char *str);

// ENV
t_env		*get_env(t_env *env, char *key);
char		**convert_env_to_arr(t_env *env);
char		**dup_env(char **envp);
char		*extract_path(char **envp);
void		handle_envp(t_data *data);
t_env		*add_env(t_env *list,
				const char *key, const char *value);
t_env		*parse_environment(char **env);
char		*find_env_key(t_env *env, char *value);

// COMMANDS
t_commands	*gen_cmd_node(void);
void		clear_command_nodes(t_commands **list);

int			ft_save_stdin_stdout(int *save_stdin,
				int *save_stdout);
void		ft_reset_stdin_stdout(int *save_stdin,
				int *save_stdout);

// EXPANSION
char		*find_env_var(t_env *env, char *key);
int			count_dollar_signs(char *str);
void		join_before_sign(char *str, char *joined);
char		*handle_status(char *joined, int status,
				char *var_name);
char		*handle_exp(char *joined, char *var_name,
				char *var_value, t_env *env);
char		*handle_one_sign(char *str, t_env *env, int status);
char		*handle_status_many(char *joined, int status, char *var_name);
char		*handle_exp_many(char *joined,
				char *var_name, char *var_value, t_env *env);
char		*handle_many_signs(char *str, char **spl,
				t_env *env, int status);
#endif