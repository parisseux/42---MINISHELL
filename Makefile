NAME = minishell

HEADERS = ./inc
SRC_DIR = ./src
PARSING_DIR = $(SRC_DIR)/parsing
COMMAND_DIR = $(SRC_DIR)/command
EXEC_DIR = $(SRC_DIR)/execution
SIG_DIR = $(SRC_DIR)/signals
LIBFT_DIR = ./libft
OBJ_DIR = ./obj

CC = gcc 
CFLAGS = -Wall -Werror -Wextra -Iinclude -I$(HEADERS) -g3
LDFLAGS = -lreadline

SRC_FILES = ./src/command/pwd.c \
			./src/command/unset.c \
			./src/command/exit.c \
			./src/command/exit_u.c \
			./src/command/cd.c \
			./src/command/echo.c \
			./src/command/env.c \
			./src/command/export.c \
			./src/command/export_u.c \
			./src/execution/execution2.c \
			./src/execution/pipe_utils.c \
			./src/execution/redirection_utils.c \
			./src/execution/pipe.c \
			./src/execution/pipe_utils2.c \
			./src/execution/builtin_utils.c \
			./src/execution/execution.c \
			./src/execution/exec_utils.c \
			./src/execution/non_builtin_utils.c \
			./src/execution/redirection.c \
			./src/parsing/expand_var_utils.c \
			./src/parsing/expand_var_utils2.c \
			./src/parsing/syntax_error.c \
			./src/parsing/bin_path.c \
			./src/parsing/detect_var.c \
			./src/parsing/new_token.c\
			./src/parsing/new_token_utils.c \
			./src/parsing/parsing.c \
			./src/parsing/expand_var.c \
			./src/parsing/parsing_utils.c \
			./src/parsing/expand_home.c \
			./src/parsing/valid_shell_var.c \
			./src/parsing/detect_var_utils.c \
			./src/parsing/expand_home_u.c \
			./src/parsing/shell_var.c \
			./src/signals/signal.c \
			./src/signals/signals2.c \
			./src/utils.c \
			./src/main.c \
			./src/utils2.c \

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

LIBFT_LIB = $(LIBFT_DIR)/libft.a

ROSE = \033[35m
GREEN = \033[1;92m
RESET = \033[0m

all: $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIBFT_LIB) $(LDFLAGS)
	@echo "💕 $(ROSE)minishell is ready for you$(RESET) 💕"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(OBJ_DIR)/parsing $(OBJ_DIR)/command $(OBJ_DIR)/execution $(OBJ_DIR)/signals
	@$(CC) $(CFLAGS) -o $@ -c $<


$(OBJ_DIR)/signals:
	@mkdir -p $(OBJ_DIR)/signals

$(OBJ_DIR)/parsing:
	@mkdir -p $(OBJ_DIR)/parsing

$(OBJ_DIR)/command:
	@mkdir -p $(OBJ_DIR)/command

$(OBJ_DIR)/execution:
	@mkdir -p $(OBJ_DIR)/execution

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "cleaning	$(GREEN)[OK]$(RESET)"
	
re: fclean all
    
.PHONY: all clean fclean re 
