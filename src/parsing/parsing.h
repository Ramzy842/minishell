/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:46:34 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/09 16:33:24 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum s_tokens
{
	WORD = 0,
	INPUT = 1,
	OUTPUT = 2,
	APPEND = 3,
	HEREDOC = 4,
	PIPE = 5,
} t_tokens;


typedef enum {
	INPUT_NONE,
	IO_INPUT,
	IO_HEREDOC
} input_redirections;

typedef enum {
	OUTPUT_NONE,
	IO_OUTPUT,
	IO_APPEND
} output_redirections;

typedef struct s_lexer
{
	int				id;
	char			*str;
	t_tokens 		token;
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
	char					**paths;
	char					**envp;
	struct s_commands		*commands;
	t_lexer					*lexer_list;
	char					*pwd;
	char					*old_pwd;
	int						pipes;
	int						*pid;
	int						heredoc;
	int						reset;
	// t_parser_data			*parser_data;
}	t_data;

// typedef struct s_commands
// {
// 	char					**str;
// 	int						(*builtin)(t_data *, struct s_commands *);
// 	int						number_of_redirections;
// 	char					*heredoc_file;
// 	t_lexer					*redirections;
// 	struct s_commands		*next;
// 	struct s_commands		*prev;
// }	t_commands;


typedef struct s_commands
{
	char					**command_args;
	input_redirections i_redir;
	output_redirections o_redir;
	char* input_filename;
	char* output_filename;
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
void 		update_pipes_count(t_data *data);
t_commands *parse_commands(t_data *data);
void		parser_error(int error, t_data *data, t_lexer *lexer_list);
void		remove_lexer_node(t_lexer **lst, int key);
int			parser_double_token_error(t_data *data, t_lexer *lexer_list, t_tokens token);
void		delete_first_lexer_node(t_lexer **lst);
void		lexer_error(int error, t_data *data);
t_lexer		*free_lexer_node(t_lexer **lst);
void		clear_lexer_nodes(t_lexer **lst);
int			ft_error(int error, t_data *data);
// int		is_between_matching_quotes(char *str);
// void    redirect_input(char **tokens, t_command_pipeline *pipeline, int *x);
// void    redirect_output(char **tokens, t_command_pipeline *pipeline, int *x);
// void    redirect_heredoc(char **tokens, t_command_pipeline *pipeline, int *x);
// void    redirect_append(char **tokens, t_command_pipeline *pipeline, int *x);
// void    default_input_parsing(char **tokens, t_command_pipeline *pipeline, int *x);
// void    initialize_commands(t_command_pipeline *pipeline);
// int		tokens_quotes_validation(char **tokens);
#endif