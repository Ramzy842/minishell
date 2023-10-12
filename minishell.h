/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 03:17:38 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/12 20:22:23 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
#include <stdint.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./src/builtins/builtins.h"
# include "./src/parsing/parsing.h"

// enum redirection_types
// {
// 	INPUT,
// 	OUTPUT,
// 	APPEND,
// 	HEREDOC,
// };

// typedef struct s_input_files
// {
// 	char	*file;
// 	enum	redirection_types type;
// 	int		order;
// } t_input_files;

// typedef struct s_output_files
// {
// 	char	*file;
// 	enum	redirection_types type;
// 	int		order;
// } t_output_files;

// typedef struct s_command
// {
//     char			*command;
//     char			**args;
// 	t_input_files	*input_files;
// 	t_output_files	*output_files;
// 	char			**vars;
//     int				pipe_to;
// } t_command;

// --------------------------------------------------



// typedef struct s_command_pipeline
// {
//     int         number_of_commands;
//     t_command   *commands;
// } t_command_pipeline;

int     ft_strlen(char *str);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_substr(char *s, unsigned int start, int len);
int     ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *str, int c);
char	**ft_split(char *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*join_args(char **args);
void    handle_env(char **envp, char **args);
char    *remove_beg_end(char *str);
char	*ft_strnstr( char *haystack, char *needle, int len);
char    **ft_split_spaces(char *s);
int     ft_strlen_2d(char **tab);
char	**tok_w_no_quotes(char **args);
char	*ft_strtrim(char  *s1, char  *set);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t count, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t length);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin_2d(char *s1, char **s2, int s2_size);
//void	expander(t_command_pipeline *pipeline, char **full_command);


// printing
void printer(t_data *data, t_commands *command);
void	print_tokens_list(t_data *data);
// void	print_commands(t_commands *command);
void print_lexer_list(t_lexer *list);
void print_commands_list(t_commands *list);
// void print_commands_list(t_command **list);
void	clear_command_nodes(t_commands **lst);
void build_commands_list(t_lexer **lexer_list, t_data *data);
// void build_commands_list(t_lexer **tokens, t_data *data);

// ----------------------------------------------------------------------------------
//								NEW CODE											|
// ----------------------------------------------------------------------------------

typedef struct s_global
{
	int	error_num;
	int	stop_heredoc;
	int	command_mode;
	int	heredoc_mode;
}	t_global;

// t_global	g_global;


int	reset_data(t_data *data);

#endif