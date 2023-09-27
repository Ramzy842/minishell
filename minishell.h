/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 03:17:38 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/27 21:02:31 by rchahban         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./src/builtins/builtins.h"

typedef struct s_input_files
{
	char	*file;
	int		order;
} t_input_files;

typedef struct s_output_files
{
	char	*file;
	int		order;
} t_output_files;

typedef struct s_command
{
    char			*command;
    char			**args;
	t_input_files	*input_files;
	t_output_files	*output_files;
	char			**vars;
    int				pipe_to;
} t_command;


typedef struct s_command_pipeline
{
    int         number_of_commands;
    t_command   *commands;
} t_command_pipeline;

int     ft_strlen(char *str);
char	*ft_substr(char *s, unsigned int start, int len);
int     ft_strcmp(const char *s1, const char *s2);
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
void	expander(t_command_pipeline *pipeline, char **full_command);


// printing
void    print_commands_count(t_command_pipeline *pipeline);
void    print_commands(t_command_pipeline *pipeline);
void    print_args(t_command_pipeline *pipeline);
void    print_input_files(t_command_pipeline *pipeline);
void    print_output_files(t_command_pipeline *pipeline);
void    print_tokens(char **tokens);
void	printer(t_command_pipeline *pipeline, char **tokens);
void	print_full_command(char **full_command);
#endif