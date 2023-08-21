/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:08:37 by rchahban          #+#    #+#             */
/*   Updated: 2023/08/21 18:16:58 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int visit_home_dir()
{
    char *home;

    home = getenv("HOME");
    if (home == NULL)
        return 1;
    if (chdir(home) != 0)
    {
        printf("Minishell: cd: %s: No such file or directory\n", home);
        return 1;
    }
    return (0);
}