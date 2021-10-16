# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahssaini <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 16:44:52 by ahssaini          #+#    #+#              #
#    Updated: 2021/10/12 16:44:54 by ahssaini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = philo.c philo_utils.c ft_atoi.c ft_init.c 
OBJS = $(SRCS:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror
%.o:%.c *.h
	@$(CC) $(FLAGS) -c $< -o $@
all: *.h
	@$(MAKE) $(NAME)
$(NAME) : $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
clean:
	@rm -rf *.o
fclean:clean
	@rm -rf $(NAME)
re: fclean all