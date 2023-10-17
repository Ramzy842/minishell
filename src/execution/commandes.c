/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 07:59:25 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/16 15:41:22 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_in_redir(t_commands *cmd)
{
    int fd[2];
    if (cmd->i_redir == IO_INPUT)
        fd[0] = open(cmd->input_filename, O_RDONLY);
    else if (cmd->i_redir == IO_HEREDOC)
	{
        pipe(fd);
        write(fd[1], cmd->heredoc, ft_strlen(cmd->heredoc));
        if (fd[0])
            close(fd[1]);
    }
    dup2(fd[0], STDIN_FILENO);
    if (fd[0])
        close (fd[0]);
}
void ft_out_redir(t_commands *cmd)
{
    int fd = 0;
    if (cmd->o_redir == IO_OUTPUT)
        fd = open(cmd->output_filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
    else if (cmd->o_redir == IO_APPEND)
        fd = open(cmd->output_filename, O_CREAT | O_APPEND | O_RDWR, 0644);
    dup2(fd, STDOUT_FILENO);
    if (fd)
        close (fd);
}

int ft_redir(t_commands *cmd)
{
    if (cmd->i_redir != INPUT_NONE)
        ft_in_redir(cmd);
    if (cmd->o_redir != OUTPUT_NONE)
        ft_out_redir(cmd);
    return (0);
}
 