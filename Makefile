# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/11 18:43:34 by aelkhali          #+#    #+#              #
#    Updated: 2023/03/01 20:15:21 by aelkhali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Program Name
NAME = philo


# Colors :
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED= \033[0;31m``
BLUE = \033[0;34m
STOP = \033[0m

# Commands And Flags : 
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread -g
SRCS = main.c
RM = rm -rf

# loading source files : 
SRCS = main.c utils/args_check.c utils/ft_atoi.c utils/get_time.c utils/init_data.c \
		utils/philosopher.c utils/supervisor.c utils/clean_memory.c

# Makefile required rules :
all : $(NAME)
	@echo "You Can Use $(GREEN)***$(NAME)***$(STOP)"

$(NAME) : $(SRCS)
	@$(CC) $(FLAGS) $(SRCS) -o $(NAME)
	@echo "$(BLUE)Compiling $(NAME) files... $(STOP)"

clean :
	@echo "$(YELLOW)Cleaning Objects... $(STOP)"

fclean : clean
	@$(RM) $(NAME)
	@echo "$(RED)Deleting All... $(STOP)"

re : fclean all