NAME        = cub3D
CC          = cc

# MLX42 config
MLX_DIR     = NEWMLX42
MLX_INC     = -I$(MLX_DIR)/include
MLX_LIB     = -L$(MLX_DIR)/build -lmlx42

# GLFW config from homebrew
GLFW_DIR    = /mnt/homes/aromani/.brew/opt/glfw
GLFW_INC    = -I$(GLFW_DIR)/include
GLFW_LIB    = -L$(GLFW_DIR)/lib

CFLAGS      = -Wall -Wextra -Werror -Iincludes $(MLX_INC) $(GLFW_INC)

# macOS-compatible linker flags (no -lGL or -lX11!)
LDFLAGS     = $(MLX_LIB) $(GLFW_LIB) -lglfw -ldl -lm -framework OpenGL -framework Cocoa -pthread

SRC         = main.c

SRC_PARS    = parsing/parsing.c \
              parsing/parsing_utils.c \
              parsing/parsing_utils2.c \
              parsing/parsing_utils3.c \
              parsing/parsing_utils4.c \
              parsing/parsing_utils5.c \
              parsing/detol.c \
              parsing/allocation.c \
              parsing/init.c

SRC_EXEC    = raycasting/rayasting.c

SRC_HLP     = helpers/ft_atoi.c \
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
              helpers/ft_getmax.c

ALL_SRC     = $(SRC) $(SRC_PARS) $(SRC_EXEC) $(SRC_HLP)
OBJ         = $(ALL_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[1;32m✅ Compiling complete source code into executable...\033[0m"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "\033[1;32m🎉 Build successful! You can now run ./cub3d\033[0m"
	@echo "\033[1;31m"
	@echo "  _____ _   _______  ___________  "
	@echo " /  __ \ | | | ___ \|____ |  _  \ "
	@echo " | /  \/ | | | |_/ /    / / | | | "
	@echo " | |   | | | | ___ \    \ \ | | | "
	@echo " | \__/\ |_| | |_/ /.___/ / |/ /  "
	@echo "  \____/\___/\____/ \____/|___/   "
	@echo "\033[0m"

%.o: %.c includes/cub3d.h includes/parser.h
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[1;34m🔹 Compiling: $< -> $@\033[0m"

clean:
	@echo "\033[0;33m🧼 Removing compiled object files to clean up...\033[0m"
	@rm -f $(OBJ)
	@echo "\033[0;32m✔️  Clean complete.\033[0m"

fclean: clean
	@echo "\033[0;31m🗑️ Removing final executable (cub3d)...\033[0m"
	@rm -f $(NAME)
	@echo "\033[0;32m✔️  Full clean complete.\033[0m"

re: fclean all
