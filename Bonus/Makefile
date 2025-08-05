# ──────────────────────────────────────────────────────────────────────────────
#                          Project Settings
# ──────────────────────────────────────────────────────────────────────────────

NAME     := cub3D
CC       := cc

# ──────────────────────────────────────────────────────────────────────────────
#                      Detect Platform & set GLFW flags
# ──────────────────────────────────────────────────────────────────────────────

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
  # macOS (Homebrew)
  BREW_PREFIX   := $(shell brew --prefix)
  GLFW_INC      := -I$(BREW_PREFIX)/opt/glfw/include
  GLFW_LIB      := -L$(BREW_PREFIX)/opt/glfw/lib -lglfw
  PLATFORM_LDFLAGS := -framework Cocoa -framework IOKit \
                      -framework CoreVideo -framework OpenGL

else ifeq ($(UNAME_S),Linux)
  # Linux (pkg-config)
  GLFW_INC      := $(shell pkg-config --cflags glfw3)
  GLFW_LIB      := $(shell pkg-config --static --libs glfw3)
  PLATFORM_LDFLAGS := -ldl -lm

else
  $(error Unsupported OS: $(UNAME_S))
endif

# ──────────────────────────────────────────────────────────────────────────────
#                               MLX42 Config
# ──────────────────────────────────────────────────────────────────────────────

MLX_DIR := NEWMLX42
MLX_INC := -I$(MLX_DIR)/include
MLX_LIB := -L$(MLX_DIR)/build -lmlx42

# ──────────────────────────────────────────────────────────────────────────────
#                            Compiler & Linker Flags
# ──────────────────────────────────────────────────────────────────────────────

CFLAGS  := -Wall -Wextra -Werror -Iincludes $(MLX_INC) $(GLFW_INC)
LDFLAGS := $(MLX_LIB) $(GLFW_LIB) $(PLATFORM_LDFLAGS) -pthread

# ──────────────────────────────────────────────────────────────────────────────
#                             Source & Object Lists
# ──────────────────────────────────────────────────────────────────────────────

SRC       := main.c
SRC_PARS  := parsing/parsing.c \
             parsing/parsing_utils.c \
             parsing/parsing_utils2.c \
             parsing/parsing_utils3.c \
             parsing/parsing_utils4.c \
             parsing/parsing_utils5.c \
             parsing/parsing_colors.c \
             parsing/detol.c \
             parsing/allocation.c \
             parsing/color_utils.c \
             parsing/init.c \
             parsing/textures.c
SRC_EXEC  := raycasting/rayasting.c
SRC_HLP   := helpers/ft_atoi.c \
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

ALL_SRC := $(SRC) $(SRC_PARS) $(SRC_EXEC) $(SRC_HLP)
OBJ     := $(ALL_SRC:.c=.o)

# ──────────────────────────────────────────────────────────────────────────────
#                               Build Targets
# ──────────────────────────────────────────────────────────────────────────────

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[1;32m✅ Compiling and linking into $(NAME)...\033[0m"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "\033[1;32m🎉 Build successful! Run ./$(NAME)\033[0m"

%.o: %.c includes/cub3d.h includes/parser.h
	@echo "\033[1;34m🔹 Compiling: $<\033[0m"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[0;33m🧼 Removing object files...\033[0m"
	@rm -f $(OBJ)

fclean: clean
	@echo "\033[0;31m🗑️  Removing executable...\033[0m"
	@rm -f $(NAME)

re: fclean all
