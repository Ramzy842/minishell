/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:02:27 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/20 23:25:25 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env	*parse_environment(char **env)
{
	t_env	*env_list;
	char	*equals;
	int		x;
	char	*value;
	char	*key;

	env_list = NULL;
	x = 0;
	while (env[x])
	{
		equals = ft_strchr(env[x], '=');
		if (equals != NULL)
		{
			key = malloc(sizeof(char) * ((equals - env[x]) + 1));
			key[(equals - env[x])] = '\0';
			ft_strncpy(key, env[x], (equals - env[x]));
			value = equals + 1;
			env_list = add_env(env_list, key, value);
		}
		x++;
	}
	return (env_list);
}
