/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:52:59 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/11 04:09:22 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
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

int     handle_cd(char **args);
char    *print_current_dir();
int     visit_home_dir();
int     apply_hybrid_cd(char *path);
// void    echo_without_option_n(char **args);
void    echo_option_n(char **args);
char    *remove_double_quotes(char *str);
// void    handle_echo(char **args);
void    handle_echo(char **args, char *input);
void    echo_without_option_n(char **args, char *input);
char    *extract_echo_args(char *input, int start);
int     count_double_quotes(char *str);
int     is_between_quotes(char *str);
#endif