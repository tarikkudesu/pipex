# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 12:01:11 by tamehri           #+#    #+#              #
#    Updated: 2024/01/28 18:28:18 by tamehri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	pipex.c pars.c libft.c split.c error.c utils.c
SRC_B	=	pipex_bonus.c pars_bonus.c libft.c split.c error.c

OBJ		=	$(SRC:.c=.o)
OBJ_B	=	$(SRC:.c=.o)
INC		=	pipex.h
INC_B	=	pipex_bonus.h
CC		= 	cc
NAME	=	pipex
BONUS	=	pipex_bonus
CFLAGS	=	-Wall -Wextra -Werror
MAJENTA	=	'\033[1;35m'
GREEN	=	'\033[32m'
RESET	=	'\033[0m'

all: $(NAME)

%.o: %.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(GREEN) "... Compiling\t$<\t[OK]" $(RESET)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo $(GREEN) "\n Linking\t<<< $(NAME) >>>" $(RESET)
	@echo $(GREEN) "Done" $(RESET)

$(BONUS): $(OBJ_B)
	@$(CC) $(CFLAGS) $(OBJ_B) -o $(BONUS)
	@echo $(GREEN) "\n Linking Bonus\t<<< $(BONUS) >>>" $(RESET)
	@echo $(GREEN) "Done" $(RESET)

clean:
	@rm -f $(OBJ) $(OBJ_B)
	@echo $(MAJENTA) "... Cleaning\n" $(RESET)
	@echo $(MAJENTA) "Done" $(RESET)

fclean: clean
	@rm -f $(NAME) $(BONUS)

re: fclean all
	@echo $(GREEN) "\n... Recompiling" $(RESET)
	@echo $(MAJENTA) "Done" $(RESET)
