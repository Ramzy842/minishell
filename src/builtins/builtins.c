/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:51:03 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/16 10:33:31 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// char *print_current_dir()
// {
//     char *cwd;

//     cwd = malloc(PATH_MAX * sizeof(char));
//     if (!cwd)
//         return (NULL);
//     if (getcwd(cwd, PATH_MAX) != NULL) {
//         return (cwd);
//     }
//     return (NULL);
// }

// int handle_cd(char **args) 
// {
//     if (*args == NULL || !args) 
//         visit_home_dir();
//     else 
//     {
//         char *path = args[0];
//         if (path[0] == '~') 
//             apply_hybrid_cd(path);
//         else if (chdir(path) != 0)
//         {
//             printf("Minishell: cd: %s: No such file or directory\n", path);
//             return 1;
//         }
//     }
//     return 0;
// }

// void    handle_env(char **envp, char **args)
// {
//     int x;

//     x = 0;
//     while (envp[x] && !args[0])
//     {
//         printf("%s\n", envp[x]);
//         x++;
//     }
// }

// void    handle_echo(char **args, char *input)
// {
//      char    *temp;

//     if (args[0] == NULL || !args)
//         printf("\n");
//     else
//     {
//         temp = remove_double_quotes(join_args(args));
//         args = ft_split(temp, ' ');
//         if (ft_strcmp(args[0], "-n") == 0)
//             echo_option_n(args);
//         else
//             echo_without_option_n(args, input);
//     }
// }
