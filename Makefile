# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 00:46:41 by rchahban          #+#    #+#              #
#    Updated: 2023/10/08 12:18:45 by rchahban         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Define the compiler
CC = cc

# Define the flags to pass to the compiler
CFLAGS = -Wall -Wextra -Werror

# Define the source files for the so_long executable
SRC = main.c printing.c ./src/parsing/parsing.c ./src/parsing/redirections/redirect_input.c \
	./src/parsing/redirections/redirect_heredoc.c ./src/parsing/redirections/redirect_append.c \
	./src/parsing/redirections/redirect_output.c \
	./src/utils/ft_split_spaces.c ./src/utils/spaces.c \
	./src/utils/ft_strcmp.c ./src/utils/ft_strchr.c \
	./src/utils/ft_putchar_fd.c ./src/parsing/lexer/lexer.c \
	./src/utils/ft_strtrim.c ./src/utils/ft_putendl_fd.c \
	./src/utils/ft_strnstr.c ./src/signals/signals.c \
	./src/utils/ft_split.c ./src/utils/ft_substr.c \
	./src/utils/ft_strdup.c ./src/utils/ft_strlen.c \
	./src/utils/ft_strjoin.c ./src/utils/handle_args.c \
	./src/builtins/builtins.c ./src/builtins/utils/cd_helpers.c \
	./src/execution/execution.c ./src/utils/tok_w_no_quotes.c \
	./src/builtins/utils/echo_helpers.c ./src/utils/ft_strlen_2d.c \
	./src/parsing/expansion/expander.c ./src/parsing/utils/lexer/quotes_utils.c ./src/parsing/utils/lexer/lexer_utils.c \
	./src/parsing/lexer/lexer_list_operations.c ./src/parsing/parser/parser.c ./src/parsing/utils/parser/parser_utils.c \
	./src/parsing/utils/parser/parser_error.c ./src/utils/ft_putstr_fd.c ./src/parsing/utils/lexer/lexer_utils_1.c \
	./src/utils/ft_memmove.c ./src/utils/ft_memcpy.c
# Define the object files for the so_long executable, generated from the source files
OBJ = $(SRC:.c=.o)

# Define the name of the so_long executable to be generated
NAME = minishell

# Define the default target to be built
all: $(NAME)

# Rule to generate the so_long executable from the object files
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline #-g -fsanitize=address

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