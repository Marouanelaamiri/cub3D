# Robust Makefile for cub3D + NEWMLX42

NAME := cub3D
CC   := cc

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  BREW_PREFIX := $(shell brew --prefix)
  GLFW_INC    := -I$(BREW_PREFIX)/opt/glfw/include
  GLFW_LIB    := -L$(BREW_PREFIX)/opt/glfw/lib -lglfw
  PLATFORM_LDFLAGS := -framework Cocoa -framework IOKit \
                      -framework CoreVideo -framework OpenGL
else ifeq ($(UNAME_S),Linux)
  GLFW_INC    := $(shell pkg-config --cflags glfw3)
  GLFW_LIB    := $(shell pkg-config --static --libs glfw3)
  PLATFORM_LDFLAGS := -ldl -lm
else
  $(error Unsupported OS: $(UNAME_S))
endif

MLX_DIR := NEWMLX42
MLX_INC := -I$(MLX_DIR)/include
MLX_LIB := $(MLX_DIR)/build/libmlx42.a

CFLAGS := -Wall -Wextra -Werror -Iincludes $(MLX_INC) $(GLFW_INC)
LDFLAGS := $(PLATFORM_LDFLAGS) -pthread
LDLIBS  := $(MLX_LIB) $(GLFW_LIB)

# sources
SRC := main.c

SRC_PARS := \
	parsing/parsing.c \
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
	parsing/textures.c \
	parsing/padding.c

SRC_EXEC := \
	raycasting/dda_algo.c \
	raycasting/drawing.c \
	raycasting/helpers_00.c \
	raycasting/helpers_01.c \
	raycasting/moves.c \
	raycasting/raycasting.c

SRC_HLP := \
	helpers/ft_atoi.c \
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

SRCS := $(SRC) $(SRC_PARS) $(SRC_EXEC) $(SRC_HLP)

# compute objects reliably
OBJS := $(SRCS:.c=.o)

.PHONY: all clean clean_mlx fclean re print-objs

all: $(NAME)

# Build MLX if needed
$(MLX_LIB):
	@echo "🔧 Building MLX42 in $(MLX_DIR)..."
	@cd $(MLX_DIR) && cmake -S . -B build
	@cd $(MLX_DIR) && cmake --build build --config Release

# main link rule — prints OBJS to verify
$(NAME): $(MLX_LIB) $(OBJS)
	@echo "\n\033[1;34mObjects to link:\033[0m $(OBJS)"
	@echo "\033[1;32m✅ Linking $(NAME)...\033[0m"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS) $(LDFLAGS)
	@echo "\033[1;32m🎉 Build successful! Run ./$(NAME)\033[0m"

# compile each .c -> .o; require headers
%.o: %.c includes/cub3d.h includes/parser.h
	@echo "🔹 Compiling: $<"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "🧼 Removing object files..."
	@rm -f $(OBJS)

clean_mlx:
	@echo "🧼 Removing MLX build..."
	@rm -rf $(MLX_DIR)/build

fclean: clean clean_mlx
	@echo "🗑️  Removing executable..."
	@rm -f $(NAME)

re: fclean all

print-objs:
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"
