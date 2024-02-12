# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 12:01:11 by tamehri           #+#    #+#              #
#    Updated: 2024/02/12 18:07:59 by tamehri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	mand/pipex.c mand/parss.c mand/h_fun.c mand/split.c mand/error.c mand/utils.c

SRC_B	=	bonus/pipex_bonus.c bonus/parss_bonus.c bonus/utils_bonus.c bonus/error_bonus.c \
			bonus/h_fun_bonus.c bonus/split_bonus.c bonus/gnl_f_bonus.c bonus/gnl_u_bonus.c bonus/multip_cmds.c

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
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo $(GREEN) "\n Linking\t<<< $(NAME) >>>" $(RESET)
	@echo $(GREEN) "Done" $(RESET)

$(BONUS): $(OBJ_B)
	@$(CC) $(CFLAGS) $(OBJ_B) -o $(BONUS)
	@echo $(GREEN) "\n Linking Bonus\t<<< $(BONUS) >>>" $(RESET)
	@echo $(GREEN) "Done" $(RESET)

mand/%.o: mand/%.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(GREEN) "... Compiling\t$<\t[OK]" $(RESET)

bonus/%.o: bonus/%.c $(INC_B)
	@$(CC) $(CFLAGS) -c $< -o $@
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
