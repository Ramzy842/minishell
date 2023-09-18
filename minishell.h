/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 03:17:38 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/18 21:02:50 by rchahban         ###   ########.fr       */
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

typedef struct s_command
{
    char    *command;
    char    **args;
    char    *input_file;
    char    *output_file;
    int     pipe_to;
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
#endif