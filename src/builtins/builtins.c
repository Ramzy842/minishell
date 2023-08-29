/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:51:03 by rchahban          #+#    #+#             */
/*   Updated: 2023/08/29 17:14:03 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

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

int handle_cd(char **args) 
{
    if (*args == NULL || !args) 
        visit_home_dir();
    else 
    {
        char *path = args[0];
        if (path[0] == '~') 
            apply_hybrid_cd(path);
        else if (chdir(path) != 0)
        {
            printf("Minishell: cd: %s: No such file or directory\n", path);
            return 1;
        }
    }
    // Update the prompt to display the current working directory
    //print_current_dir();
    return 0;
}

