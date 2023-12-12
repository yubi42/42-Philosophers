# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jborner <jborner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 16:51:26 by yubi42            #+#    #+#              #
#    Updated: 2023/12/12 13:08:42 by jborner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g #-lpthread #-fsanitize=thread
NAME	= philo

SRC_PATH = src/
OBJ_PATH = obj/

SRC	= main.c clean_up.c monitoring.c philo_actions.c philo_actions_forks.c set_structs.c utils.c validator.c \

SRCS	= $(addprefix $(SRC_PATH), $(SRC))

OBJ	= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INCS	= -Iinclude

all: $(NAME) 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(NAME): $(OBJ_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re