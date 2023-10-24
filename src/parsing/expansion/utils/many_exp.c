/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   many_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouderr <mbouderr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 08:34:32 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/24 04:26:46 by mbouderr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

char	*handle_status_many(char *joined, int status, char *var_name)
{
	joined = ft_strjoin(joined, ft_itoa(status));
	if (&var_name[1])
		joined = ft_strjoin(joined, &var_name[1]);
	return (joined);
}

char	*handle_exp_many(char *joined,
	char *var_name, char *var_value, t_env *env)
{
	char	*rest;
	int		y;

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
	return (joined);
}

char	*handle_many_signs(char *str, char **spl, t_env *env, int status)
{
	char	*var_name;
	char	*var_value;
	int		x;
	char	*joined;

	x = 0;
	joined = custom_malloc(1, NULL, ALLOC, NULL);
	joined[0] = '\0';
	var_value = NULL;
	var_name = NULL;
	joined = join_before_sign(str, joined);
	while (spl[x])
	{
		var_name = spl[x];
		if (var_name[0] == '?')
			joined = handle_status_many(joined, status, var_name);
		else
			joined = handle_exp_many(joined, var_name, var_value, env);
		x++;
	}
	free_arr(spl);
	return (joined);
}
