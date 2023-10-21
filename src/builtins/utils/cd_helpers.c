/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:08:37 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/21 13:53:09 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include "../builtins.h"

char	*find_path_ret(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], str, ft_strlen(str)))
			return (ft_substr(data->envp[i], ft_strlen(str),
					ft_strlen(data->envp[i]) - ft_strlen(str)));
		i++;
	}
	return (NULL);
}

void	change_path(t_data *data)
{
	char	*tmp;

	tmp = ft_strdup(data->pwd);
	free(data->old_pwd);
	data->old_pwd = tmp;
	free(data->pwd);
	data->pwd = getcwd(NULL, sizeof(NULL));
}

int	specific_path(t_data *data, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_path_ret(str, data);
	ret = chdir(tmp);
	free(tmp);
	if (ret != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (ret);
}

void	add_path_to_env(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", data->pwd);
			free(data->envp[i]);
			data->envp[i] = tmp;
		}
		else if (!ft_strncmp(data->envp[i], "OLDPWD=", 7) && data->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", data->old_pwd);
			free(data->envp[i]);
			data->envp[i] = tmp;
		}
		i++;
	}
}

int	change_to_home_directory(void)
{
	const char	*home_dir;

	home_dir = getenv("HOME");
	if (home_dir == NULL)
	{
		ft_errors("HOME directory not set in the environment.",
			strerror(errno));
		return (1);
	}
	if (chdir(home_dir) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	change_directory_to_path(const char *path)
{
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	buit_cd(t_commands *cmd)
{
	if (cmd->command_args[1] == NULL)
	{
		return (change_to_home_directory());
	}
	else
		return (change_directory_to_path(cmd->command_args[1]));
 
}