# ─────────────────────────────────────────────
# Compiler and Flags
# ─────────────────────────────────────────────
CC     = cc
CFLAGS = -Wall -Wextra -Werror -IMandatory/includes

# ─────────────────────────────────────────────
# GLFW & MLX
# ─────────────────────────────────────────────
GLFW_DIR  = /mnt/homes/malaamir/.brew/opt/glfw
GLFW_INC  = -I$(GLFW_DIR)/include
GLFW_LIB  = -L$(GLFW_DIR)/lib -lglfw

MLX_FLAGS = -L$(MLX_DIR)/build -lmlx42 -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

# ─────────────────────────────────────────────
# Mandatory Build
# ─────────────────────────────────────────────
MANDATORY_NAME = cub3D
MANDATORY_DIR  = Mandatory
MANDATORY_INCL = -I$(MANDATORY_DIR)/includes -I$(MANDATORY_DIR)/NEWMLX42/include
MLX_DIR        = $(MANDATORY_DIR)/NEWMLX42

MANDATORY_SRC = \
	$(MANDATORY_DIR)/main.c \
	$(MANDATORY_DIR)/parsing/parsing.c \
	$(MANDATORY_DIR)/parsing/parsing_utils.c \
	$(MANDATORY_DIR)/parsing/parsing_utils2.c \
	$(MANDATORY_DIR)/parsing/parsing_utils3.c \
	$(MANDATORY_DIR)/parsing/parsing_utils4.c \
	$(MANDATORY_DIR)/parsing/parsing_utils5.c \
	$(MANDATORY_DIR)/parsing/parsing_colors.c\
	$(MANDATORY_DIR)/parsing/color_utils.c \
	$(MANDATORY_DIR)/parsing/textures.c \
	$(MANDATORY_DIR)/parsing/detol.c \
	$(MANDATORY_DIR)/parsing/allocation.c \
	$(MANDATORY_DIR)/parsing/init.c \
	$(MANDATORY_DIR)/raycasting/rayasting.c \
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
	$(MANDATORY_DIR)/helpers/ft_getmax.c

MANDATORY_OBJ = $(MANDATORY_SRC:.c=.o)

# ─────────────────────────────────────────────
# Bonus Build
# ─────────────────────────────────────────────
BONUS_NAME = cub3D_bonus
BONUS_DIR  = Bonus
BONUS_INCL = -I$(BONUS_DIR)/includes -I$(BONUS_DIR)/NEWMLX42/include
MLX_BONUS_DIR = $(BONUS_DIR)/NEWMLX42

BONUS_SRC = \
	$(BONUS_DIR)/main.c \
	# (Add bonus files here manually like above)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

# ─────────────────────────────────────────────
# Targets
# ─────────────────────────────────────────────
all: $(MANDATORY_NAME)

bonus: MLX_DIR = $(MLX_BONUS_DIR)
bonus: CFLAGS += $(BONUS_INCL)
bonus: $(BONUS_NAME)

$(MANDATORY_NAME): $(MANDATORY_OBJ)
	$(CC) $(CFLAGS) $(MANDATORY_OBJ) $(GLFW_LIB) $(MLX_FLAGS) -o $@
	@echo "\033[1;31mREADY TO PLAY !!\033[0m"

$(BONUS_NAME): $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(GLFW_LIB) $(MLX_FLAGS) -o $@
	@echo "\033[1;31mREADY TO PLAY !!\033[0m"

%.o: %.c
	$(CC) $(CFLAGS) -I$(dir $<)/includes -I$(dir $<)/NEWMLX42/include $(GLFW_INC) -c $< -o $@

clean:
	rm -f $(MANDATORY_OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(MANDATORY_NAME) $(BONUS_NAME)

re: fclean all
