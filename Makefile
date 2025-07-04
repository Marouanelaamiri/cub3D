# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 11:29:43 by malaamir          #+#    #+#              #
#    Updated: 2025/07/04 18:53:19 by malaamir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D

CC            = cc

CFLAGS        = -Wall -Wextra -Werror -Iincludes -IMLX42/include #-g -fsanitize=address

LDFLAGS        = -ldl -lm -pthread

SRC            = main.c

SRC_PARS    = parsing/parsing.c \
			parsing/parsing_utils.c \

SRC_EXEC    =

SRC_HLP        = helpers/ft_atoi.c \
				helpers/ft_bzero.c \
				helpers/ft_calloc.c \
				helpers/ft_isalnum.c \
				helpers/ft_isalpha.c \
				helpers/ft_isdigit.c \
				helpers/ft_itoa.c \
				helpers/ft_memcpy.c \
				helpers/ft_memset.c \
				helpers/ft_split.c \
				helpers/ft_strchr.c \
				helpers/ft_strdup.c \
				helpers/ft_strjoin.c \
				helpers/ft_strlcat.c \
				helpers/ft_strlcpy.c \
				helpers/ft_strlen.c \
				helpers/ft_strncmp.c \
				helpers/ft_strnstr.c \
				helpers/ft_strrchr.c \
				helpers/ft_strtrim.c \
				helpers/ft_substr.c \
				helpers/get_next_line.c \
				helpers/ft_realloc.c \
				helpers/ft_strcmp.c \
				
				

ALL_SRC        = $(SRC) $(SRC_PARS) $(SRC_EXEC) $(SRC_HLP)

OBJ            = $(ALL_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c includes/cub3d.h includes/parser.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all