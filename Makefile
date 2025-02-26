# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ninisse <ninisse@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 15:30:30 by avarrett          #+#    #+#              #
#    Updated: 2025/02/17 13:54:20 by ninisse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADERS = ./inc
SRC_DIR = ./src
PARSING_DIR = $(SRC_DIR)/parsing
COMMAND_DIR = $(SRC_DIR)/command
LIBFT_DIR = ./libft
OBJ_DIR = ./obj

CC = gcc 
CFLAGS = -Wall -Werror -Wextra -Iinclude -I$(HEADERS)
LDFLAGS = -lreadline

SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(PARSING_DIR)/*.c) $(wildcard $(COMMAND_DIR)/*.c) 

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

LIBFT_LIB = $(LIBFT_DIR)/libft.a

ROSE = \033[35m
GREEN = \033[1;92m
RESET = \033[0m

all: $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIBFT_LIB) $(LDFLAGS)
	@echo "💕 $(ROSE)minishell is ready for you$(RESET) 💕"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(OBJ_DIR)/parsing $(OBJ_DIR)/command
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/parsing:
	@mkdir -p $(OBJ_DIR)/parsing

$(OBJ_DIR)/command:
	@mkdir -p $(OBJ_DIR)/command

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
