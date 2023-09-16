#Define the compiler
CC = cc

# Define the flags to pass to the compiler
CFLAGS = -Wall -Wextra -Werror

# Define the source files for the so_long executable
SRC = main.c ./src/utils/spaces.c ./src/utils/ft_strcmp.c \
	./src/utils/ft_strnstr.c \
	./src/utils/ft_split.c ./src/utils/ft_substr.c \
	./src/utils/ft_strdup.c ./src/utils/ft_strlen.c \
	./src/utils/ft_strjoin.c ./src/utils/handle_args.c \
	./src/builtins/builtins.c ./src/builtins/utils/cd_helpers.c \
	./src/execution/execution.c ./src/parsing/parsing.c ./src/signals/signals.c\
	./src/builtins/utils/echo_helpers.c

# Define the object files for the so_long executable, generated from the source files
OBJ = $(SRC:.c=.o)

# Define the name of the so_long executable to be generated
NAME = minishell

# Define the default target to be built
all: $(NAME)

# Rule to generate the so_long executable from the object files
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

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