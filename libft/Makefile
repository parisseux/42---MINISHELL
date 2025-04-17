# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/10 10:09:01 by avarrett          #+#    #+#              #
#    Updated: 2025/04/17 14:46:07 by pchatagn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft.a

CFLAGS= -Wall -Werror -Wextra
CC= gcc 

FILES= ft_atoi.c\
		ft_atol.c \
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strcat.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_str_digit.c\
		ft_power.c\
		ft_free_tab.c\
		get_next_line.c\
		get_next_line_utils.c\
		ft_strnstr_echo.c\

BONUS= ft_lstnew_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c\
		ft_lstiter_bonus.c\
		ft_lstmap_bonus.c\

RESET=	\033[0;39m
ORANGE=	\033[0;33m
GRAY=	\033[0;90m
RED=	\033[0;91m
GREEN=	\033[1;92m
YELLOW=	\033[1;93m
BLUE=	\033[0;94m
MAGENTA= \033[0;95m
CYAN=	\033[0;96m
WHITE=	\033[0;97m

OBJ=	$(FILES:.c=.o) 
OBJBONUS= $(BONUS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "libft		$(GREEN)[OK]$(RESET)"
	
bonus: $(OBJ) $(OBJBONUS)
	@ar rcs $(NAME) $(OBJ) $(OBJBONUS)
	

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f	$(OBJ) $(OBJBONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY	:all re clean fclean