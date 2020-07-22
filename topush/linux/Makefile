# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/20 16:28:24 by user42            #+#    #+#              #
#    Updated: 2020/07/20 17:16:55 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3D
NAME_BONUS      = Gaminet

SRCS_FILE		= cub3d.c colors.c event.c exit.c frame.c img.c init.c map.c move.c parsing.c raycasting.c resolution.c textures.c bmp.c sprites.c

SRCS_FILE_BONUS	= cub3d_bonus.c \
event_bonus.c event_game_over_bonus.c event_kneel_jump_bonus.c event_move_bonus.c event_sprite_hit_bonus.c\
event_look_bonus.c \
frame_bonus.c frame_dda_bonus.c frame_floor_and_sky_bonus.c frame_raycasting_bonus.c frame_skybox_bonus.c \
frame_sprites_bonus.c frame_walls_bonus.c \
interface_bonus.c interface_avatar_bonus.c interface_lifebar_bonus.c interface_minimap_bonus.c interface_scripts_bonus.c \
settings_bonus.c settings_free_bonus.c settings_images_bonus.c settings_init_bonus.c settings_map_bonus.c \
settings_parsing_bonus.c settings_resolution_bonus.c settings_skybox_bonus.c settings_sprites_bonus.c \
tools_bmp_bonus.c tools_colors_bonus.c tools_maths_bonus.c tools_macros_bonus.c\

SRCS			= $(addprefix $(SRCS_DIR), $(SRCS_FILE))
OBJS			= $(addprefix $(OBJS_DIR), $(SRCS_FILE:.c=.o))
SRCS_DIR		= ./srcs/
OBJS_DIR		= ./objs/
INCLUDES_DIR	= ./includes/
SRCS_BONUS		= $(addprefix $(SRCS_DIR_BONUS), $(SRCS_FILE_BONUS))
OBJS_BONUS		= $(addprefix $(OBJS_DIR_BONUS), $(SRCS_FILE_BONUS:.c=.o))
SRCS_DIR_BONUS	= ./bonus/srcs_bonus/
OBJS_DIR_BONUS	= ./bonus/objs_bonus/
INCLUDES_DIR_BONUS	= ./bonus/includes_bonus/
INCLUDES_BONUS	= $(addprefix -I, $(INCLUDES_DIR_BONUS) $(LIBFT_DIR) $(LIBVECT_DIR) $(MLX_DIR))
HEADER_BONUS	= $(INCLUDES_DIR_BONUS)cub3d_bonus.h
LIBFT_DIR		= ./libft/
MLX_DIR			= ./mlx/
LIBFT			= $(LIBFT_DIR)libft.a
MINILIBX		= $(MLX_DIR)libmlx.a
HEADER			= $(INCLUDES_DIR)cub3d.h
MLXFLAGS		= -lm -lXext -lX11 -lbsd
CFLAGS			= -Wall -Wextra -Werror -O2 -g#3 -fsanitize=address,undefined -Wpadded
CC				= clang
INCLUDES	= $(addprefix -I, $(INCLUDES_DIR) $(LIBFT_DIR) $(LIBVECT_DIR) $(MLX_DIR))
FRAMEWORK	= -framework OpenGL -framework Appkit
# COLORS
_BLACK		= "\033[30m"
_RED		= "\033[31m"
_GREEN		= "\033[32m"
_YELLOW		= "\033[33m"
_BLUE		= "\033[34m"
_VIOLET		= "\033[35m"
_CYAN		= "\033[36m"
_WHITE		= "\033[37m"
_END		= "\033[0m"
_CLEAR		= "\033[2K"
_HIDE_CURS	= "\033[?25l"
_SHOW_CURS	= "\033[?25h"
_UP			= "\033[A"
_CUT		= "\033[k"
.PHONY: all launch clean fclean re norme title bonus 
.SILENT: 


all: launch
launch:
	$(MAKE) $(LIBFT)
	$(MAKE) $(MINILIBX)
	echo $(_CLEAR)$(_YELLOW)"building - "$(_GREEN)$(NAME)$(_END)
	$(MAKE) $(NAME)
	echo $(_GREEN)"\nDone."$(_END)$(_SHOW_CURS)
$(OBJS_DIR):
	mkdir $@
$(LIBFT): FORCE
	$(MAKE) -sC $(LIBFT_DIR)
	echo
$(MINILIBX): FORCE
	$(MAKE) -sC $(MLX_DIR) 2>/dev/null
FORCE:
$(NAME): $(LIBFT) $(MINILIBX) $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) $(MINILIBX) -o $(NAME)
$(OBJS): $(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	printf $<
clean:
	$(MAKE) -sC $(LIBFT_DIR) clean
	$(MAKE) -sC $(MLX_DIR) clean
	$(RM) -r $(OBJS_DIR)
fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)
re:
	$(MAKE) -s fclean
	$(MAKE) -s

bonus:
	echo "BONUS"
	$(MAKE) $(LIBFT)
	$(MAKE) $(MINILIBX)
	echo $(_CLEAR)$(_YELLOW)"building - "$(_GREEN)$(NAME_BONUS)$(_END)
	$(MAKE) $(NAME_BONUS)
	echo $(_GREEN)"\nDone."$(_END)$(_SHOW_CURS)

$(NAME_BONUS): $(LIBFT) $(MINILIBX) $(OBJS_DIR_BONUS) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(MLXFLAGS) $(MINILIBX) -o $(NAME_BONUS)
$(OBJS_DIR_BONUS):
	mkdir $@
$(OBJS_BONUS): $(OBJS_DIR_BONUS)%.o: $(SRCS_DIR_BONUS)%.c $(HEADER_BONUS)
	$(CC) $(CFLAGS) $(INCLUDES_BONUS) -c $< -o $@

bonus_clean:
	$(MAKE) -sC $(LIBFT_DIR) clean
	$(MAKE) -sC $(MLX_DIR) clean
	$(RM) -r $(OBJS_DIR_BONUS)
bonus_fclean: bonus_clean
	$(RM) $(LIBFT)
	$(RM) $(NAME_BONUS)

#check leak avec valgrind
#valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes ./Cub3D maps/resolution_double.cub > valgrind_log 2>&1
#grep -A1 "valgrind" valgrind_log|grep Cub3D