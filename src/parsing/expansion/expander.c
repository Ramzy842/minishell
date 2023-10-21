/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:54:41 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/20 23:18:05 by rchahban         ###   ########.fr       */
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

char	*handle_many_signs(char **spl, t_env *env)
{
	char	*var_name;
	char	*var_value;
	int		x;
	char	*joined;

	x = 0;
	joined = malloc(1);
	joined[0] = '\0';
	while (spl[x])
	{
		var_name = spl[x];
		var_value = find_env_var(env, var_name);
		if (var_value)
			joined = ft_strjoin(joined, var_value);
		else
			joined = ft_strjoin(joined, "");
		x++;
	}
	free_arr(spl);
	return (joined);
}

char	*handle_one_sign(char *str, t_env *env)
{
	char	*dollar_sign;
	char	*var_name;
	char	*var_value;

	dollar_sign = ft_strchr(str, '$');
	if (dollar_sign)
	{
		if (ft_strcmp(dollar_sign + 1, ""))
		{
			var_name = dollar_sign + 1;
			var_value = find_env_var(env, var_name);
			if (var_value)
				return (ft_strdup(var_value));
			else
				return (ft_strdup(""));
		}
		else
			return (ft_strdup("$"));
	}
	return (ft_strdup(str));
}

char	*expand_variables(char *str, t_env *env)
{
	char	*removed_quotes_str;
	char	**spl;

	removed_quotes_str = remove_quotes(str);
	spl = ft_split(removed_quotes_str, '$');
	if (count_dollar_signs(str) > 1)
		return (handle_many_signs(spl, env));
	else
		return (handle_one_sign(removed_quotes_str, env));
}

// char	*expand_variables(char *str, t_env *env)
// {
// 	char	*dollar_sign;
// 	char	*removed_quotes_str;
// 	int		x;
// 	char	**spl;
// 	char	*joined;
// 	char	*var_name;
// 	char	*var_value;

// 	dollar_sign = NULL;
// 	removed_quotes_str = NULL;
// 	if (count_dollar_signs(str) > 1)
// 	{
// 		x = 0;
// 		removed_quotes_str = remove_quotes(str);
// 		spl = ft_split(removed_quotes_str, '$');
// 		joined = malloc(1);
// 		joined[0] = '\0';
// 		while (spl[x])
// 		{
// 			var_name = spl[x];
// 			var_value = find_env_var(env, var_name);
// 			if (var_value)
// 				joined = ft_strjoin(joined, var_value);
// 			else
// 				joined = ft_strjoin(joined, "");
// 			x++;
// 		}
// 		free_arr(spl);
// 		return (joined);
// 	}
// 	else
// 	{
// 		removed_quotes_str = remove_quotes(str);
// 		dollar_sign = ft_strchr(removed_quotes_str, '$');
// 		free(removed_quotes_str);
// 		if (dollar_sign && ft_strcmp(dollar_sign + 1, ""))
// 		{
// 			var_name = dollar_sign + 1;
// 			var_value = find_env_var(env, var_name);
// 			if (var_value)
// 				str = ft_strdup(var_value);
// 			else
// 				str = ft_strdup("");
// 		}
// 		else if (dollar_sign && !ft_strcmp(dollar_sign + 1, ""))
// 			str = ft_strdup("$");
// 		else
// 			str = ft_strdup(str);
// 	}
// 	return (str);
// }
