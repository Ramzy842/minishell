/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 07:59:25 by mbouderr          #+#    #+#             */
/*   Updated: 2023/10/21 20:54:32 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_in_redir(t_commands *cmd)
{
	int	fd[2];

	if (cmd->i_redir == IO_INPUT)
	{
		fd[0] = open(cmd->input_filename, O_RDONLY);
		if (fd[0] == -1)
		{
			printf("erro msg file not found\n");
			return (EXIT_FAILURE);
		}
	}
	else if (cmd->i_redir == IO_HEREDOC)
	{
		pipe(fd);
		write(fd[1], cmd->heredoc, ft_strlen(cmd->heredoc));
		if (fd[0])
			close(fd[1]);
	}
	dup2(fd[0], STDIN_FILENO);
	if (fd[0])
		close(fd[0]);
	return (0);
}

void	ft_out_redir(t_commands *cmd)
{
	int	fd;

	fd = 0;
	if (cmd->o_redir == IO_OUTPUT)
	{
		fd = open(cmd->output_filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else if (cmd->o_redir == IO_APPEND)
		fd = open(cmd->output_filename, O_CREAT | O_APPEND | O_RDWR, 0644);
	dup2(fd, STDOUT_FILENO);
	if (fd)
		close(fd);
}

int	ft_redir(t_commands *cmd)
{
	if (cmd->i_redir != INPUT_NONE)
	{
		ft_in_redir(cmd);
	}
	if (cmd->o_redir != OUTPUT_NONE)
		ft_out_redir(cmd);
	return (0);
}

char	*get_cmd_abs_path(t_env *env, char *cmd)
{
	t_env	*path;
	char	**path_spl;
	char	*tmp1;
	char	*tmp2;
	int		i;

	path = get_env(env, "PATH");
	if (!path)
		return (NULL);
	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
	{
		tmp2 = cmd;
		if (!access(tmp2, F_OK))
			return (tmp2);
	}
	path_spl = ft_split(path->value, ':');
	if (!path_spl)
		return (NULL);
	i = 0;
	while (path_spl[i])
	{
		tmp1 = ft_strjoin(path_spl[i], "/");
		tmp2 = ft_strjoin(tmp1, cmd);
		free(tmp1);
		if (!access(tmp2, F_OK))
			return (tmp2);
		i++;
	}
	return (NULL);
}
