# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 00:46:41 by rchahban          #+#    #+#              #
#    Updated: 2023/10/23 22:35:22 by rchahban         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Define the compiler
CC = cc

# Define the flags to pass to the compiler
CFLAGS = -Werror -Wall -Wextra

FLAGS = -lreadline  -g -fsanitize=address

# Define the source files for the minishell executable
SRC = main.c ./src/parsing/parsing.c ./src/parsing/redirections/redirect_input.c ./src/parsing/minishell_loop.c \
	./src/utils/ft_strjoinget.c ./src/parsing/redirections/redirect_heredoc.c ./src/parsing/redirections/redirect_append.c \
	./src/parsing/redirections/redirect_output.c ./src/utils/spaces.c \
	./src/utils/ft_strcmp.c ./src/utils/ft_atoi.c ./src/utils/ft_strchr.c ./src/parsing/lexer/lexer.c \
	./src/utils/ft_strtrim.c ./src/utils/ft_putendl_fd.c ./src/utils/ft_putchar_fd.c \
	./src/utils/ft_strnstr.c ./src/utils/ft_split.c ./src/utils/ft_substr.c \
	./src/utils/ft_strdup.c ./src/utils/ft_strlen.c ./src/utils/ft_strjoin.c ./src/utils/handle_args.c \
	./src/builtins/utils/cd_helpers.c ./src/parsing/expansion/expander.c \
	./src/execution/execution.c ./src/utils/tok_w_no_quotes.c ./src/builtins/utils/echo_helpers.c ./src/utils/ft_strlen_2d.c \
	./src/parsing/utils/lexer/quotes_utils.c ./src/parsing/utils/lexer/lexer_utils.c \
	./src/parsing/lexer/lexer_list_operations.c ./src/parsing/parser/parser.c ./src/parsing/utils/parser/parser_utils.c \
	./src/utils/ft_putstr_fd.c ./src/parsing/utils/lexer/lexer_utils_1.c \
	./src/utils/ft_memmove.c ./src/utils/ft_memcpy.c ./src/utils/ft_calloc.c ./src/utils/ft_bzero.c \
	./src/utils/ft_strncmp.c ./src/parsing/env/convert_env_to_arr.c ./src/parsing/env/dup_envp.c \
	./src/parsing/env/extract_path.c ./src/parsing/env/get_env.c ./src/parsing/env/parse_env.c ./src/parsing/parser/utils/gen_cmd_node.c \
	./src/parsing/parser/utils/get_list_length.c ./src/parsing/parser/utils/handle_args.c ./src/parsing/parser/utils/realloc_arr.c \
	./src/utils/ft_strncpy.c ./src/parsing/env/operations.c ./src/parsing/utils/commands/freeing.c src/utils/ft_memset.c \
	./src/execution/commandes.c ./src/parsing/redirections/utils/is_metachar.c ./src/parsing/redirections/utils/is_redir_op.c \
	./src/builtins/utils/tools.c  src/parsing/env/freeing.c ./src/parsing/redirections/handle_redirections.c  ./src/execution/add_functions.c\
	./src/builtins/builtins.c ./src/builtins/utils/exit_helpers.c ./src/builtins/utils/export_helper.c ./src/builtins/utils/pwd_helper.c ./src/builtins/utils/unset_helper.c \
	./src/utils/ft_strlcpy.c ./src/builtins/utils/env_helper.c ./src/execution/help_function.c \
	./src/execution/ft_signal.c ./src/builtins/utils/tools_export.c ./src/builtins/utils/tools2.c ./src/utils/ft_itoa.c \
	./src/parsing/expansion/utils/many_exp.c ./src/parsing/expansion/utils/single_exp.c ./src/parsing/expansion/utils/utils_1.c
# Define the object files for the minishell executable, generated from the source files
OBJ = $(SRC:.c=.o)

# Define the name of the minishell executable to be generated
NAME = minishell

# Define the default target to be built
all: $(NAME)

# Rule to generate the minishell executable from the object files
$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lreadline 

# Rule to generate the object files from the source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(patsubst %.c,%.o,$<) 

# Clean target to remove generated files
clean:
	rm -f $(OBJ)

# Fclean target to remove executable files and perform clean
fclean: clean
	rm -f $(NAME)

# Re target to rebuild the project from scratch
re: fclean all

.PHONY: all clean fclean re