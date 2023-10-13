/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:03:57 by rchahban          #+#    #+#             */
/*   Updated: 2023/10/13 02:04:51 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./src/parsing/parsing.h"

void	free_arr(char **arr)
{
	int	x;

	x = 0;
	while (arr[x])
	{
		free(arr[x]);
		x++;
	}
	free(arr);
}

char **dup_env(char **envp)
{
	int		x;
	char	**ptr;

	x = 0;
	ptr = NULL;
	// count number of strs
	while (envp[x])
		x++;
	// allocate memo for strs
	ptr = ft_calloc((x + 1), sizeof(char *));
	if (!ptr)
		return (NULL);
	// dup each str in  the envp to the ptr
	x = 0;
	while (envp[x])
	{
		ptr[x] = ft_strdup(envp[x]);
		if (!ptr[x])
		{
			free_arr(ptr);
			return (NULL);
		}
		x++;
	}
	return (ptr);
}

int	minishell_loop(t_data *data);

void clear_command_nodes(t_commands **list)
{
	t_commands	*tmp;

	if (!*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		if ((*list)->command_args)
			free_arr((*list)->command_args);
		if ((*list)->heredoc)
			free((*list)->heredoc);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

int	reset_data(t_data *data)
{
	if (data->commands)
	 	clear_command_nodes(&data->commands);
	// free(data->shell_input);
	// if (data->pid)
	// 	free(data->pid);
	// free_arr(data->paths);
	initialize_data(data);
	data->reset = 1;
	printf("Performing reset...\n");
	minishell_loop(data);
	return (1);
}

char *show_current_path(char *working_dir)
{
	working_dir = print_current_dir();
	working_dir = ft_strjoin("\x1b[32mMinishell:\x1b[36m",working_dir);
	working_dir = ft_strjoin(working_dir, "$ \x1b[0m");
	return (working_dir);
}

void ft_memset(void* addr, unsigned char data, int len) {
	int i = 0;
	unsigned char* uc_addy = (unsigned char*)addr; 
	while (i < len) {
		uc_addy[i] = data;
		i++;
	}
}

t_commands* gen_cmd_node() {
	t_commands* ret = malloc(sizeof(t_commands));
	ft_memset(ret, 0, sizeof(t_commands));
	return ret;
}

int is_redir_op(char* str) {
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<<")) {
		return 1;
	}
	return 0;
}

int is_metachar(char* str) {
	if (is_redir_op(str) || !ft_strcmp(str, "|"))
		return 1;
	return 0;
}

int calc_argv_sz(t_lexer* data) {
	int i = 0;
	while (data && !is_metachar(data->str)) {
		data = data->next;
		i++;
	}
	return i;
}

void print_cmd_lst(t_commands* cmd) {
	while (cmd) {
		int i = 0;
		printf("argv: ");
		while (cmd->command_args[i])
		{
			printf("%s", cmd->command_args[i]);
			if (cmd->command_args[i + 1])
				printf(", ");
			i++;
		}
		printf("\n");
		printf("input_redir: %i | output_redir: %i\n", cmd->i_redir, cmd->o_redir);
		printf("input_file: %s  | output_file: %s\n", cmd->input_filename, cmd->output_filename);
		printf("\n");
		cmd = cmd->next;
	}
}

int getLinkedListLength(t_commands* head)
{
    int length;
	
	length = 0;
    t_commands* current = head;

    while (current != NULL) {
        length++;
        current = current->next;
    }

    return length;
}

char** realloc_arr(char** old_arr, int increment) {
	int i = 0;
	while (old_arr[i])
		i++;
	char** new_arr = malloc(sizeof(char*) * (i + increment));
	ft_memset(new_arr, 0, sizeof(char*) * (i + increment));
	i = 0;
	while (old_arr[i])
	{
		new_arr[i] = ft_strdup(old_arr[i]);
		i++;
	}
	new_arr[i] = NULL;
	i = 0;
	while (old_arr[i]) {
		free(old_arr[i]);
		i++;
	}
	free(old_arr);
	return new_arr;
}

t_commands* gen_cmd_lst(t_data* data) {
	t_commands* head = gen_cmd_node();
	t_commands* tmp = head;
	int i = 0;
	while (data->lexer_list)
	{
		if (!tmp->command_args) {
			tmp->command_args = malloc(sizeof(char*) * 2);
			ft_memset(tmp->command_args, 0, sizeof(char*) * 2);
		}
		while (data->lexer_list && !is_metachar(data->lexer_list->str))
		{
			tmp->command_args = realloc_arr(tmp->command_args, 2);
			tmp->command_args[i] = ft_strdup(data->lexer_list->str);
			data->lexer_list = data->lexer_list->next;
			i++;
		}
		while (data->lexer_list && is_metachar(data->lexer_list->str)) {
			if (data->lexer_list && !ft_strcmp(data->lexer_list->str, "|")) {
				tmp->next = gen_cmd_node();
				i = 0;
				data->lexer_list = data->lexer_list->next;
				tmp = tmp->next;
				continue;
			}
			else if (data->lexer_list && !ft_strcmp(data->lexer_list->str, "<")) {
				if (tmp->input_filename)
					free(tmp->input_filename);
				tmp->input_filename = ft_strdup(data->lexer_list->next->str);
				tmp->i_redir = IO_INPUT;
				data->lexer_list = data->lexer_list->next;
				if (data->lexer_list)
					data->lexer_list = data->lexer_list->next;
			}
			else if (data->lexer_list && !ft_strcmp(data->lexer_list->str, "<<")) {
				if (tmp->input_filename)
					free(tmp->input_filename);
				tmp->input_filename = ft_strdup(data->lexer_list->next->str);
				tmp->i_redir = IO_HEREDOC;
				data->lexer_list = data->lexer_list->next;
				if (data->lexer_list)
					data->lexer_list = data->lexer_list->next;
			}
			else if (data->lexer_list && !ft_strcmp(data->lexer_list->str, ">>")) {
				if (tmp->output_filename)
					free(tmp->output_filename);
				tmp->output_filename = ft_strdup(data->lexer_list->next->str);
				tmp->o_redir = IO_APPEND;
				data->lexer_list = data->lexer_list->next;
				if (data->lexer_list)
					data->lexer_list = data->lexer_list->next;
			}
			else if (data->lexer_list && !ft_strcmp(data->lexer_list->str, ">")) {
				if (tmp->output_filename)
					free(tmp->output_filename);
				tmp->output_filename = ft_strdup(data->lexer_list->next->str);
				tmp->o_redir = IO_OUTPUT;
				data->lexer_list = data->lexer_list->next;
				if (data->lexer_list) {
					data->lexer_list = data->lexer_list->next;
				}
			}
		}
	}
	return head;
}


// void print_dollar_vars(t_commands *cmd)
// {
// 	int x = 0;
// 	t_commands *current = cmd;
// 	while (current)
// 	{
// 		x = 0;
// 		while (current->command_args[x])
// 		{
// 			if (ft_strtrim(current->command_args[x], "\"")[0] == '$')
// 				printf("%s", current->command_args[x]);
// 			x++;
// 		}
// 		printf("\n");
// 		current = current->next;
// 	}
// }


t_env* add_env(t_env* list, const char* key, const char* value) {
    t_env* new_env = malloc(sizeof(t_env));
    if (new_env == NULL) {
        perror("malloc");
        exit(1);
    }
    new_env->key = strdup(key);
    new_env->value = strdup(value);
    new_env->next = list;
    return new_env;
}

void free_env_list(t_env* list) {
    while (list != NULL) {
        t_env* current = list;
        list = list->next;
        free(current->key);
        free(current->value);
        free(current);
    }
}


char* ft_strncpy(char* dest, const char* src, size_t n) {
    char* original_dest = dest;

    while (n > 0 && *src != '\0') {
        *dest++ = *src++;
        n--;
    }

    // Fill the remaining space with null bytes if necessary
    while (n > 0) {
        *dest++ = '\0';
        n--;
    }

    return original_dest;
}

t_env* parse_environment(char **env) {
    t_env* env_list = NULL;
    
    int i = 0;
    while (env[i] != NULL) {
        // char* env_var = env[i];
        
        // Split the environment variable into key and value
        char* equals = ft_strchr(env[i], '=');
        if (equals != NULL) {
            size_t key_len = equals - env[i];
            char key[key_len + 1];
            ft_strncpy(key, env[i], key_len);
            key[key_len] = '\0';
            char* value = equals + 1;
            
            // Add the key-value pair to the linked list
            env_list = add_env(env_list, key, value);
        }
        i++;
    }
    
    return env_list;
}

int	minishell_loop(t_data *data)
{
	char	*temp;
	data->commands = NULL;
	data->lexer_list = NULL;
	data->shell_input = readline("\x1b[32mminishell-> \x1b[0m");
	// free(working_dir);
	temp = ft_strtrim(data->shell_input, " ");
	free(data->shell_input);
	data->shell_input = temp;
	if (!data->shell_input)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (ft_strlen(&data->shell_input[0]) == '\0')
		return (reset_data(data));
	add_history(data->shell_input);
	if (!quotes_are_matching(data->shell_input))
	{
		printf("error in quotes\n");
		reset_data(data);
		return (EXIT_FAILURE);	
	}
	if (!tokens_reader(data))
		return (ft_error(1, data));
	data->commands = gen_cmd_lst(data);
	t_env* current = parse_environment(data->envp);
    while (current != NULL) {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
	print_cmd_lst(data->commands);
	clear_lexer_nodes(&data->lexer_list);
	printf("\x1b[33mexecuting command...\x1b[0m\n");
	// printf("data->pwd: %s\n", data->pwd);
	// printf("data->old_pwd: %s\n", data->old_pwd);
	reset_data(data);
	return (1);
}


int	extract_pwd(t_data *data)
{
	int	x;

	x = 0;
	while (data->envp[x])
	{
		if (!ft_strncmp(data->envp[x], "PWD=", 4))
			data->pwd = ft_substr(data->envp[x],
					4, ft_strlen(data->envp[x]) - 4);
		if (!ft_strncmp(data->envp[x], "OLDPWD=", 7))
			data->old_pwd = ft_substr(data->envp[x],
					7, ft_strlen(data->envp[x]) - 7);
		x++;
	}
	return (1);
}

char *extract_path(char **envp)
{
	int		x;
	char	*empty_str;

	x = 0;
	empty_str = NULL;
	while (envp[x])
	{
		if (!ft_strncmp(envp[x], "PATH=", 5))
			return (ft_substr(envp[x], 5, ft_strlen(envp[x])));
		x++;
	}
	empty_str = ft_strdup("\0");
	return (empty_str);
}

void handle_envp(t_data *data)
{
	int		x;
	char	*envp_path;
	char	*temp;

	envp_path = NULL;
	temp = NULL;
	envp_path = extract_path(data->envp);
	data->paths = ft_split(envp_path, ':');
	free(envp_path);
	x = 0;
	while (data->paths[x])
	{ 
		if (ft_strncmp(&data->paths[x][ft_strlen(data->paths[x]) - 1],
			"/", 1) != 0)
		{
			temp = ft_strjoin(data->paths[x], "/");
			free(data->paths[x]);
			data->paths[x] = temp;
		}
		x++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	if (argc != 1 || argv[1])
	{
		printf("\x1b[31mMinishell does not accept arguments.\n");
		exit(0);
	}
	initialize_data(&data);
	data.envp = dup_env(envp);
	extract_pwd(&data);
	handle_envp(&data);
	minishell_loop(&data);
	return (0);
}
