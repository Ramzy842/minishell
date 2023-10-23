/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:54:41 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/23 08:35:22 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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
