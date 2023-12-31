/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 03:17:38 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/24 05:03:54 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <stdint.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./src/builtins/builtins.h"
# include "./src/parsing/parsing.h"
# include "./src/execution/execution.h"
# include "custom_malloc.h"

int		ft_strlen(char *str);
char	*ft_strjoin_char(char *s1, char c);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_substr(char *s, unsigned int start, int len);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *str, int c);
char	**ft_split(char *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*join_args(char **args);
char	*remove_beg_end(char *str);
char	*ft_strnstr( char *haystack, char *needle, int len);
int		ft_strlen_2d(char **tab);
char	*ft_strtrim(char *s1, char *set);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t count, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t length);
void	ft_bzero(void *s, size_t n);
void	ft_memset(void *addr, unsigned char data, int len);
char	*ft_strncpy(char *dest, const char *src, size_t n);
void	free_arr(char **arr);
int		ft_atoi(const char *str);
int		minishell_execute(t_commands *cmd, t_env *env, t_data *data);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_strjoinget(char *s1, char *s2);
char	*ft_itoa(int n);

int		reset_data(t_data *data, t_env *env, int status);
char	*remove_quotes(char *cmd);
int		init_starting_props(char *temp, t_data *data);
void	finalize_environment(int *fd);

#endif