NAME = Cub3D

CC = clang

CFLAGS = -O3 -Wall -Wextra -Werror

LIBFT = libft

MLX = mlx

LXFLAGS = -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

SRC = cub3d.c colors.c event.c exit.c frame.c img.c init.c map.c move.c parsing.c resolution.c textures.c print.c bmp.c sprites.c

FIL = $(addprefix srcs/, $(SRC)) $(addprefix libft/, $(LIB_SRC))

OBJ = $(FIL:.c=.o)

BIN = $(SRC:.c=.o) $(LIB_SRC:.c=.o)

B_HEADER = cub3d_bonus.h

B_SRC = cub3d_bonus.c \
event_bonus.c event_game_over_bonus.c event_kneel_jump_bonus.c event_move_bonus.c event_sprite_hit_bonus.c\
event_look_bonus.c \
frame_bonus.c frame_DDA_bonus.c frame_floor_and_sky_bonus.c frame_raycasting_bonus.c frame_skybox_bonus.c \
frame_sprites_bonus.c frame_walls_bonus.c \
interface_bonus.c interface_avatar_bonus.c interface_lifebar_bonus.c interface_minimap_bonus.c interface_scripts_bonus.c \
settings_bonus.c settings_free_bonus.c settings_images_bonus.c settings_init_bonus.c settings_map_bonus.c \
settings_parsing_bonus.c settings_resolution_bonus.c settings_skybox_bonus.c settings_sprites_bonus.c \
tools_bmp_bonus.c tools_colors_bonus.c tools_maths_bonus.c \


LIB_SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c \
ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c ft_putchar_fd.c \
ft_putendl_fd.c ft_putnbr_fd.c \
ft_putstr_fd.c ft_strchr.c ft_split.c \
ft_calloc.c ft_strdup.c ft_strjoin.c \
ft_strcat.c ft_strlcat.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
ft_strcpy.c ft_strncpy.c ft_strlcpy.c ft_strnstr.c ft_strrchr.c \
ft_strtrim.c ft_tolower.c ft_toupper.c ft_substr.c \
get_next_line.c ft_strjoin_GNL.c ft_rgb_from_str.c \
ft_strcharcpy.c \

B_FIL = $(addprefix srcs/, $(B_SRC)) $(addprefix libft/, $(LIB_SRC))

B_OBJ = $(B_FIL:.c=.o)

B_BIN = $(B_SRC:.c=.o) $(LIB_SRC:.c=.o)

.PHONY: all clean fclean re bonus test sqr bmp err inv norm

all: $(NAME)

$(NAME): $(OBJ)

	@echo "\n\033[0;33mCompiling..."
	$(CC) -o $(NAME) -L $(LIBFT) -L $(MLX) $(LXFLAGS) $(OBJ)
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning..."
	rm -rf $(OBJ) $(B_OBJ)
	rm -f bitmap.bmp
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

bonus: fclean $(B_OBJ)
	@echo "\n\033[0;32mCompiling bonus..."
	$(CC) -o $(NAME) -L $(LIBFT) -L $(MLX) $(LXFLAGS) $(B_OBJ)
	@echo "\033[0m"
