# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 11:29:43 by malaamir          #+#    #+#              #
#    Updated: 2025/07/01 11:38:15 by malaamir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------------------Source Files-----------------------------------#
CUB3D_SRC =

CUB3D_BONUS_SRC =
#-------------------------------Object Files-----------------------------------#
CUB3D_OBJ = $(CUB3D_SRC:.c=.o)

CUB3D_BONUS_OBJ = $(CUB3D_BONUS_SRC:.c=.o)

#-------------------------------Compiler and flags-----------------------------#
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror

MLX_P = MLX42/build

MLX_LIB = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit

#---------------------------Includes and Excutables----------------------------#
INCLUDES =
BONUS_INCLUDES =
MANDATORY_NAME =
BONUS_NAME =

#---------------------------------Rules----------------------------------------#
all: $(MANDATORY_NAME)

bonus : $(BONUS_NAME)

$(MANDATORY_NAME): $(CUB3D_OBJ)
	$(CC) $(FLAGS) $(CUB3D_OBJ) $(MLX_P)/libmlx42.a $(MLX_LIB) $(FRAMEWORKS) -o $(MANDATORY_NAME)


$(BONUS_NAME): $(CUB3D_BONUS_OBJ)
	$(CC) $(FLAGS) $(CUB3D_BONUS_OBJ) $(MLX_P)/libmlx42.a $(MLX_LIB) $(FRAMEWORKS) -o  $(BONUS_NAME)

mand/%.o: mand/%.c $(INCLUDES)
	$(CC) $(FLAGS) -c $< -o $@

bonus/%.o: bonus/%.c $(BONUS_INCLUDES)
	$(CC) $(FLAGS) -c $< -o $@
	
#---------------------------------Cleaning-------------------------------------#
clean:
	$(RM) $(CUB3D_OBJ) $(CUB3D_BONUS_OBJ)

fclean: clean
	$(RM) $(MANDATORY_NAME) $(BONUS_NAME)
#---------------------------------Rebuilding------------------------------------#
re: fclean all
