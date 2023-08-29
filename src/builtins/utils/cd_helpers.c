/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:08:37 by rchahban          #+#    #+#             */
/*   Updated: 2023/08/29 17:12:10 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include "../../../minishell.h"

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

int apply_hybrid_cd(char *path)
{
    char *home;

    home = getenv("HOME");
    if (home == NULL)
        return (1);
    if (((path[0] == '~' && !path[1]) || (path[0] == '~' && path[1] == '/' && !path[2])))
    {
        if (chdir(home) != 0)
            return (1);
    } 
    else
    {
        // Extract the path after '~/'
        const char *subpath = &path[2]; // Skip '~/' part
        char *old_path = print_current_dir();
            // go to home first
        if (chdir(home) != 0)
            return (1);
            // and then go to subpath
        
        if (chdir(subpath) != 0)
        {
            printf("Minishell: cd: %s: No such file or directory\n", &path[1]);
            chdir(old_path);
            return (1);
        }
    }
    return (0);
}