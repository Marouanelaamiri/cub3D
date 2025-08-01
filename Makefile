# ──────────────────────────────────────────────────────────────────────────────
#                          Project Settings
# ──────────────────────────────────────────────────────────────────────────────

NAME        := cub3D
CC          := cc

# ──────────────────────────────────────────────────────────────────────────────
#                      Detect Homebrew Prefix & macOS
# ──────────────────────────────────────────────────────────────────────────────

UNAME_S     := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  # where brew is installed on this Mac
  BREW_PREFIX := $(shell brew --prefix)
  # GLFW from Homebrew
  GLFW_DIR    := $(BREW_PREFIX)/opt/glfw
  GLFW_INC    := -I$(GLFW_DIR)/include
  GLFW_LIB    := -L$(GLFW_DIR)/lib -lglfw
  # frameworks needed by MLX42 & OpenGL on macOS
  OSX_FRAMEWORKS := -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL
else
  $(error This Makefile is macOS‑only)
endif

# ──────────────────────────────────────────────────────────────────────────────
#                               MLX42 Config
# ──────────────────────────────────────────────────────────────────────────────

MLX_DIR     := NEWMLX42
MLX_INC     := -I$(MLX_DIR)/include
MLX_LIB     := -L$(MLX_DIR)/build -lmlx42

# ──────────────────────────────────────────────────────────────────────────────
#                            Compiler & Linker Flags
# ──────────────────────────────────────────────────────────────────────────────

CFLAGS      := -Wall -Wextra -Werror -Iincludes $(MLX_INC) $(GLFW_INC) -fsanitize=address
LDFLAGS     := $(MLX_LIB) $(GLFW_LIB) $(OSX_FRAMEWORKS) -pthread

# ──────────────────────────────────────────────────────────────────────────────
#                             Source & Object Lists
# ──────────────────────────────────────────────────────────────────────────────

SRC         := main.c
SRC_PARS    := parsing/parsing.c \
               parsing/parsing_utils.c \
               parsing/parsing_utils2.c \
               parsing/parsing_utils3.c \
               parsing/parsing_utils4.c \
               parsing/parsing_utils5.c \
               parsing/detol.c \
               parsing/allocation.c \
               parsing/init.c \
               parsing/textures.c
SRC_EXEC    := raycasting/rayasting.c
SRC_HLP     := helpers/ft_atoi.c \
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

ALL_SRC     := $(SRC) $(SRC_PARS) $(SRC_EXEC) $(SRC_HLP)
OBJ         := $(ALL_SRC:.c=.o)

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
