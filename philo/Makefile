# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andreys <andreys@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 16:48:53 by andreys           #+#    #+#              #
#    Updated: 2022/07/18 16:50:39 by andreys          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

C_FILES =	main.c \
			init.c \
			process_arg.c \
			get_time.c \
			print_message.c \
			philo_actions.c \
			simulation.c \
			finish_simulation.c

O_FILES = $(C_FILES:.c=.o)

H_FILES = philo.h

FLAGS =	-Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(O_FILES)
	gcc $(O_FILES) -o $(NAME)

%.o: %.c $(H_FILES)
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -fr $(O_FILES)

fclean: clean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re