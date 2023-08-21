/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:51:03 by rchahban          #+#    #+#             */
/*   Updated: 2023/08/21 18:37:28 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
#include "../../minishell.h"

char *print_current_dir()
{
    char *cwd;

    cwd = malloc(PATH_MAX * sizeof(char));
    if (!cwd)
        return (NULL);
    if (getcwd(cwd, PATH_MAX) != NULL) {
        return (cwd);
    }
    return (NULL);
}

int apply_hybrid_cd(char *path)
{
    char *home;

    home = getenv("HOME");
    if (home == NULL)
        return (1);
    if ((path[1] == '\0' || path[1] == '/') && !path[2])
    {
        if (chdir(home) != 0)
            return (1);
    } 
    else
    {
        // Extract the path after '~/'
        char *subpath = &path[2]; // Skip '~/' part
            // go to home first
        if (chdir(home) != 0)
            return (1);
            // and then go to subpath
        if (chdir(subpath) != 0)
        {
            printf("Minishell: cd: %s: No such file or directory\n", &path[1]);
            return (1);
        }
    }
    return (0);
}

int handle_cd(char **args) 
{
    if (*args == NULL || !args) 
        visit_home_dir();
    else 
    {
        char *path = args[0];
        if (*path == '~') 
            apply_hybrid_cd(path);
        else if (chdir(path) != 0)
        {
            printf("Minishell: cd: %s: No such file or directory\n", path);
            return 1;
        }
    }
    // Update the prompt to display the current working directory
    print_current_dir();
    return 0;
}