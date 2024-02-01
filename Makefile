# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 12:01:11 by tamehri           #+#    #+#              #
#    Updated: 2024/02/01 14:12:27 by tamehri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	mand/pipex.c mand/pars.c mand/libft.c mand/split.c mand/error.c mand/utils.c
SRC_B	=	bonus/pipex_bonus.c bonus/pars_bonus.c bonus/utils_bonus.c bonus/error_bonus.c \
			bonus/libft_bonus.c bonus/split_bonus.c bonus/gnl.c bonus/gnl_utils.c bonus/here_doc.c

OBJ		=	$(SRC:.c=.o)
OBJ_B	=	$(SRC_B:.c=.o)
INC		=	mand/pipex.h
INC_B	=	bonus/pipex_bonus.h
CC		= 	cc
NAME	=	pipex
BONUS	=	pipex_bonus
CFLAGS	=	-Wall -Wextra -Werror
MAJENTA	=	'\033[35m'
GREEN	=	'\033[32m'
RESET	=	'\033[0m'

all: $(NAME)

bonus: $(BONUS)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
	@echo $(GREEN) "\n Linking\t<<< $(NAME) >>>" $(RESET)
	@echo $(GREEN) "Done" $(RESET)

$(BONUS): $(OBJ_B)
	@$(CC) $(OBJ_B) -o $(BONUS)
	@echo $(GREEN) "\n Linking Bonus\t<<< $(BONUS) >>>" $(RESET)
	@echo $(GREEN) "Done" $(RESET)

%.o: %.c $(INC) $(INC_B)
	@$(CC) -c $< -o $@
	@echo $(GREEN) "... Compiling\t$<\t[OK]" $(RESET)

clean:
	@rm -f $(OBJ) $(OBJ_B)
	@echo $(MAJENTA) "... Cleaning\n" $(RESET)
	@echo $(MAJENTA) "Done" $(RESET)

fclean: clean
	@rm -f $(NAME) $(BONUS)

re: fclean all
	@echo $(GREEN) "\n ... Recompiling" $(RESET)
	@echo $(GREEN) "Done" $(RESET)

re_bonus: fclean bonus
	@echo $(GREEN) "\n ... Recompiling" $(RESET)
	@echo $(GREEN) "Done" $(RESET)
