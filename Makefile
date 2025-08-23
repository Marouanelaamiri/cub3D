CC      = cc
CFLAGS  = -Wall -Wextra -Werror

USER     = malaamir
GLFW_DIR = /mnt/homes/$(USER)/.brew/opt/glfw
GLFW_INC = -I$(GLFW_DIR)/include
GLFW_LIB = -L$(GLFW_DIR)/lib -lglfw


MLX_DIR   = MLX42
MLX_LIB   = $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS = -L$(MLX_DIR)/build -lmlx42 \
            -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo


MANDATORY_NAME   = cub3D
MANDATORY_DIR    = Mandatory
MLX_MANDATORY_INC = -I$(MANDATORY_DIR)/includes -I$(MANDATORY_DIR)/NEWMLX42/include

MANDATORY_SRC = $(MANDATORY_DIR)/main.c \
	$(MANDATORY_DIR)/parsing/parsing.c \
	$(MANDATORY_DIR)/parsing/parsing_utils.c \
	$(MANDATORY_DIR)/parsing/parsing_utils2.c \
	$(MANDATORY_DIR)/parsing/parsing_utils3.c \
	$(MANDATORY_DIR)/parsing/parsing_utils4.c \
	$(MANDATORY_DIR)/parsing/parsing_utils5.c \
	$(MANDATORY_DIR)/parsing/parsing_colors.c \
	$(MANDATORY_DIR)/parsing/color_utils.c \
	$(MANDATORY_DIR)/parsing/textures.c \
	$(MANDATORY_DIR)/parsing/detol.c \
	$(MANDATORY_DIR)/parsing/parsing_utils6.c \
	$(MANDATORY_DIR)/parsing/init.c \
	$(MANDATORY_DIR)/raycasting/raycasting.c \
	$(MANDATORY_DIR)/helpers/ft_atoi.c \
	$(MANDATORY_DIR)/helpers/ft_bzero.c \
	$(MANDATORY_DIR)/helpers/ft_calloc.c \
	$(MANDATORY_DIR)/helpers/ft_isalnum.c \
	$(MANDATORY_DIR)/helpers/ft_isalpha.c \
	$(MANDATORY_DIR)/helpers/ft_isdigit.c \
	$(MANDATORY_DIR)/helpers/ft_itoa.c \
	$(MANDATORY_DIR)/helpers/ft_memcpy.c \
	$(MANDATORY_DIR)/helpers/ft_memset.c \
	$(MANDATORY_DIR)/helpers/ft_split.c \
	$(MANDATORY_DIR)/helpers/ft_strchr.c \
	$(MANDATORY_DIR)/helpers/ft_strdup.c \
	$(MANDATORY_DIR)/helpers/ft_strjoin.c \
	$(MANDATORY_DIR)/helpers/ft_strlcat.c \
	$(MANDATORY_DIR)/helpers/ft_strlcpy.c \
	$(MANDATORY_DIR)/helpers/ft_strlen.c \
	$(MANDATORY_DIR)/helpers/ft_strncmp.c \
	$(MANDATORY_DIR)/helpers/ft_strnstr.c \
	$(MANDATORY_DIR)/helpers/ft_strrchr.c \
	$(MANDATORY_DIR)/helpers/ft_strtrim.c \
	$(MANDATORY_DIR)/helpers/ft_substr.c \
	$(MANDATORY_DIR)/helpers/get_next_line.c \
	$(MANDATORY_DIR)/helpers/ft_realloc.c \
	$(MANDATORY_DIR)/helpers/ft_strcmp.c \
	$(MANDATORY_DIR)/helpers/ft_getmax.c \
	$(MANDATORY_DIR)/raycasting/moves.c \
	$(MANDATORY_DIR)/raycasting/dda_algo.c \
	$(MANDATORY_DIR)/raycasting/helpers_00.c \
	$(MANDATORY_DIR)/raycasting/helpers_01.c \
	$(MANDATORY_DIR)/raycasting/drawing.c \
	$(MANDATORY_DIR)/parsing/padding.c \
	$(MANDATORY_DIR)/raycasting/textures.c\
	$(MANDATORY_DIR)/raycasting/wall_handel.c\

MANDATORY_OBJ = $(MANDATORY_SRC:.c=.o)


BONUS_NAME   = cub3D_bonus
BONUS_DIR    = Bonus
MLX_BONUS_INC = -I$(BONUS_DIR)/includes_bonus -I$(BONUS_DIR)/NEWMLX42/include

BONUS_SRC = $(BONUS_DIR)/main.c \
    $(BONUS_DIR)/parsing_bonus/parsing.c \
    $(BONUS_DIR)/parsing_bonus/parsing_utils.c \
    $(BONUS_DIR)/parsing_bonus/parsing_utils2.c \
    $(BONUS_DIR)/parsing_bonus/parsing_utils3.c \
    $(BONUS_DIR)/parsing_bonus/parsing_utils4.c \
    $(BONUS_DIR)/parsing_bonus/parsing_utils5.c \
    $(BONUS_DIR)/parsing_bonus/parsing_colors.c \
    $(BONUS_DIR)/parsing_bonus/color_utils.c \
    $(BONUS_DIR)/parsing_bonus/textures.c \
    $(BONUS_DIR)/parsing_bonus/detol.c \
    $(BONUS_DIR)/parsing_bonus/parsing_utils6.c \
    $(BONUS_DIR)/parsing_bonus/init.c \
    $(BONUS_DIR)/raycasting_bonus/raycasting.c \
    $(BONUS_DIR)/helpers_bonus/ft_atoi.c \
    $(BONUS_DIR)/helpers_bonus/ft_bzero.c \
    $(BONUS_DIR)/helpers_bonus/ft_calloc.c \
    $(BONUS_DIR)/helpers_bonus/ft_isalnum.c \
    $(BONUS_DIR)/helpers_bonus/ft_isalpha.c \
    $(BONUS_DIR)/helpers_bonus/ft_isdigit.c \
    $(BONUS_DIR)/helpers_bonus/ft_itoa.c \
    $(BONUS_DIR)/helpers_bonus/ft_memcpy.c \
    $(BONUS_DIR)/helpers_bonus/ft_memset.c \
    $(BONUS_DIR)/helpers_bonus/ft_split.c \
    $(BONUS_DIR)/helpers_bonus/ft_strchr.c \
    $(BONUS_DIR)/helpers_bonus/ft_strdup.c \
    $(BONUS_DIR)/helpers_bonus/ft_strjoin.c \
    $(BONUS_DIR)/helpers_bonus/ft_strlcat.c \
    $(BONUS_DIR)/helpers_bonus/ft_strlcpy.c \
    $(BONUS_DIR)/helpers_bonus/ft_strlen.c \
    $(BONUS_DIR)/helpers_bonus/ft_strncmp.c \
    $(BONUS_DIR)/helpers_bonus/ft_strnstr.c \
    $(BONUS_DIR)/helpers_bonus/ft_strrchr.c \
    $(BONUS_DIR)/helpers_bonus/ft_strtrim.c \
    $(BONUS_DIR)/helpers_bonus/ft_substr.c \
    $(BONUS_DIR)/helpers_bonus/get_next_line.c \
    $(BONUS_DIR)/helpers_bonus/ft_realloc.c \
    $(BONUS_DIR)/helpers_bonus/ft_strcmp.c \
    $(BONUS_DIR)/helpers_bonus/ft_getmax.c \
    $(BONUS_DIR)/raycasting_bonus/moves.c \
    $(BONUS_DIR)/raycasting_bonus/dda_algo.c \
    $(BONUS_DIR)/raycasting_bonus/helpers_00.c \
    $(BONUS_DIR)/raycasting_bonus/helpers_01.c \
    $(BONUS_DIR)/raycasting_bonus/drawing.c \
	$(BONUS_DIR)/raycasting_bonus/doors.c \
    $(BONUS_DIR)/parsing_bonus/padding.c \
    $(BONUS_DIR)/gun_doors/animation.c \
	$(BONUS_DIR)/gun_doors/animation_utils.c \
    $(BONUS_DIR)/gun_doors/door.c \
    $(BONUS_DIR)/raycasting_bonus/mouse_handler.c \
    $(BONUS_DIR)/raycasting_bonus/textures.c \
	$(BONUS_DIR)/raycasting_bonus/minimap.c \
	$(BONUS_DIR)/raycasting_bonus/wall_handel.c

BONUS_OBJ = $(BONUS_SRC:.c=.o)

HF_MANDA = Mandatory/includes/cub3d.h Mandatory/includes/parser.h

HF_BONUS = Bonus/includes_bonus/cub3d_bonus.h Bonus/includes_bonus/parser_bonus.h


all: $(MANDATORY_NAME)

bonus: $(BONUS_NAME)


$(MANDATORY_NAME): $(MANDATORY_OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) $(MANDATORY_OBJ) $(MLX_FLAGS) $(GLFW_LIB) -o $@

Mandatory/%.o: Mandatory/%.c $(HF_MANDA)
	$(CC) $(CFLAGS)  $(MLX_MANDATORY_INC) $(GLFW_INC) -c $< -o $@


$(BONUS_NAME): $(BONUS_OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(MLX_FLAGS) $(GLFW_LIB) -o $@

Bonus/%.o: Bonus/%.c $(HF_BONUS)
	$(CC) $(CFLAGS) $(MLX_BONUS_INC) $(GLFW_INC) -c $< -o $@


first: $(MLX_LIB)

$(MLX_LIB):
	cd $(MLX_DIR) && rm -rf build && cmake -B build && cmake --build build


clean:
	rm -f $(MANDATORY_OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(MANDATORY_NAME) $(BONUS_NAME)
	cd $(MLX_DIR) && rm -rf build

re: fclean all