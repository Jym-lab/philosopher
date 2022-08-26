# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/26 22:12:58 by yjoo              #+#    #+#              #
#    Updated: 2022/08/27 03:05:26 by yjoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
FSANI = -g3 -fsanitize=address
RM = rm -f
NAME = philo

INCLUDE = -I./include
SRCS_DIR = ./srcs
SRCS_FILES = main.c init.c utils.c action.c
SRCS = $(addprefix $(addsuffix /, $(SRCS_DIR)), $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) -pthread $(INCLUDE) $^ -o $@

re : fclean all

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

.PHONY: all re clean fclean
