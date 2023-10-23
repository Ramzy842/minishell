/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:54:41 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/23 07:03:24 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*find_env_var(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	count_dollar_signs(char *str)
{
	int	count;
	int	x;

	count = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == '$')
			count++;
		x++;
	}
	return (count);
}

void	join_before_sign(char *str, char *joined);

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
	joined = malloc(1);
	joined[0] = '\0';
	var_value = NULL;
	var_name = NULL;
	join_before_sign(str, joined);
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

void	join_before_sign(char *str, char *joined)
{
	int	x;

	x = 0;
	while (str[x] && str[x] != '$')
	{
		joined = ft_strjoin_char(joined, str[x]);
		x++;
	}
}

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
	join_before_sign(str, joined);
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

char	*expand_variables(char *str, t_env *env, int status)
{
	char	*removed_quotes_str;
	char	**spl;

	removed_quotes_str = remove_quotes(str);
	spl = ft_split(removed_quotes_str, '$');
	if (count_dollar_signs(str) > 1)
		return (handle_many_signs(removed_quotes_str, spl, env, status));
	else
		return (handle_one_sign(removed_quotes_str, env, status));
}
