/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 03:17:38 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/16 06:52:20 by mbouderr         ###   ########.fr       */
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
#include <fcntl.h>
#include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./src/builtins/builtins.h"
# include "./src/parsing/parsing.h"
# include "./src/execution/execution.h"


int     ft_strlen(char *str);
char	**ft_arrdup(char **arr);
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
int ft_atoi(char *str);
// char	**tok_w_no_quotes(char **args);
char	*ft_strtrim(char  *s1, char  *set);
void print_cmd_lst(t_commands* cmd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t count, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t length);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin_2d(char *s1, char **s2, int s2_size);
size_t	ft_strlcpy(char *dst,    char *src, size_t dstsize);
void	ft_memset(void *addr, unsigned char data, int len);
char	*ft_strncpy(char* dest, const char* src, size_t n);
void	free_arr(char **arr);
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
int		(*builtin_arr(char *str))(t_data *data, t_commands * cmd);
// ----------------------------------------------------------------------------------
//								NEW CODE											|
// ----------------------------------------------------------------------------------

 


int	reset_data(t_data *data);

#endif