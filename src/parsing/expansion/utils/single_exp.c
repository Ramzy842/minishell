/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 08:35:01 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/23 21:12:58 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

char	*handle_status(char *joined, int status, char *var_name)
{
	joined = ft_strjoin(joined, ft_itoa(status));
	if (&var_name[1])
		joined = ft_strjoin(joined, &var_name[1]);
	return (joined);
}

char	*handle_exp(char *joined, char *var_name, char *var_value, t_env *env)
{
	int		y;
	char	*rest;

	y = 0;
	while (ft_isalnum(var_name[y]))
		y++;
	rest = ft_substr(var_name, y, ft_strlen(var_name));
	var_name = ft_substr(var_name, 0, y);
	var_value = find_env_var(env, var_name);
	if (var_value)
	{
		joined = ft_strjoin(joined, var_value);
		if (rest)
			joined = ft_strjoin(joined, rest);
	}
	else if (rest)
		joined = ft_strjoin(joined, rest);
	return (joined);
}

char	*handle_one_sign(char *str, t_env *env, int status)
{
	char	*dollar_sign;
	char	*var_name;
	char	*var_value;
	char	*joined;

	joined = malloc(1);
	joined[0] = '\0';
	var_value = NULL;
	var_name = NULL;
	joined = join_before_sign(str, joined);
	dollar_sign = ft_strchr(str, '$');
	if (dollar_sign)
	{
		if (ft_strcmp(dollar_sign + 1, ""))
		{
			var_name = dollar_sign + 1;
			if (var_name[0] == '?')
				return (handle_status(joined, status, var_name));
			else
				return (handle_exp(joined, var_name, var_value, env));
		}
		else
			return (ft_strdup("$"));
	}
	return (ft_strdup(str));
}
