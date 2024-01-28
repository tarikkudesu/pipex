# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 12:01:11 by tamehri           #+#    #+#              #
#    Updated: 2024/01/28 11:07:37 by tamehri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SRC		=	pipex.c libft.c parc.c split.c error.c process.c

OBJ		=	$(SRC:.c=.o)
INC		=	pipex.h
CC		= 	cc
CFLAGS	=	-Wall -Wextra -Werror
NAME	=	pipex
MAJENTA	=	'\033[1;35m'
GREEN	=	'\033[32m'
RESET	=	'\033[0m'

all: $(NAME) clean

%.o: %.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(GREEN) "... Compiling\t$<\t[OK]" $(RESET)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo $(GREEN) "\n Linking\t<<< $(NAME) >>>" $(RESET)
	@echo $(GREEN) "Done" $(RESET)

clean:
	@rm -f $(OBJ)
	@echo $(MAJENTA) "... Cleaning\n" $(RESET)
	@echo $(MAJENTA) "Done" $(RESET)

fclean: clean
	@rm -f $(NAME)

re: fclean all
	@echo $(GREEN) "\n... Recompiling" $(RESET)
	@echo $(MAJENTA) "Done" $(RESET)
