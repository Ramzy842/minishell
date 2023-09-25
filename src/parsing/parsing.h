/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:46:34 by rchahban          #+#    #+#             */
/*   Updated: 2023/09/24 16:03:46 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../../minishell.h"

int		is_between_matching_quotes(char *str);
void    redirect_input(char **tokens, t_command_pipeline *pipeline, int *x);
void    redirect_output(char **tokens, t_command_pipeline *pipeline, int *x);
void    default_input_parsing(char **tokens, t_command_pipeline *pipeline, int *x);
void    initialize_commands(t_command_pipeline *pipeline);
int		tokens_quotes_validation(char **tokens);
#endif