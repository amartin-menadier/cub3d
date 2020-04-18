#ifndef _CUB3D_H_
# define _CUB3D_H_
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include "../libft/libft.h"

typedef struct	s_coord{
	double		x;
	double		y;
	double		z;
}				t_coord;

typedef struct	s_int{
	int			x;
	int			y;
	int			z;
}				t_int;

typedef struct  s_img{
	void		*ptr;
	int			*colors;
	int			bpp;
	int			line_length;
	int			endian;
	t_int		size;
}               t_img;

typedef struct 	s_settings{
	int			fd;
	t_int		win_size;
	char		*NO_path;
	char		*SO_path;
	char		*EA_path;
	char		*WE_path;
	char		*flr_path;
	char		*clg_path;
	char		*S2_path;
	char		*S3_path;
	char		**map;
	t_int		map_size;
	char		player_orientation;
	t_int		starting_pos;
	int			spr_count;
	double		*spr_x;
	double		*spr_y;
	char		*spr_text;
	int			done;
}               t_settings;

typedef struct 	s_frame{
	t_coord		pos;
	t_coord		dir;
	t_coord		ray;
	t_coord		plane;
	double		camera_x;
	t_coord		map;
	t_coord		side_dist;
	t_coord		delta_dist;
	double		perp_wall_dist;
	t_int		step;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	t_img		NO_img;
	t_img		SO_img;
	t_img		EA_img;
	t_img		WE_img;
	t_img		S2_img;
	t_img		S3_img;
	t_int		text;
	double		*z_buffer;
	int			*spr_order;
	double		*spr_dist;
	t_coord		spr_inv;
	double		spr_screen_x;
	t_int		spr_size;
	t_int		spr_draw_start;
	t_int		spr_draw_end;
	int			spr_sorted;
	int			done;
}		t_frame;

typedef struct	s_minimap{
	t_coord		case_min;
	t_coord		case_max;
	int			size;
	double		radius;
	t_int		center;
	int			case_size;
	double		step_in_case;
	int			margin;
	t_int		draw_start;
	t_int		draw_end;
	t_img		face;
	int			done;
}				t_minimap;

typedef struct	s_life{
	int			value;
	t_int		size;
	t_int		draw_start;
	t_int		draw_end;
	t_int		ctr;
	int			color;
}				t_life;

typedef struct	s_floor{
	t_img		flr_img;
	t_img		clg_img;
	t_coord		ray;
	t_coord		ray0;
	t_coord		ray1;
	int			pxl_height;
	float		cam_height;
	float		depth;
	t_coord		step;
	t_coord		pos;
	t_int		cell;
	t_int		txt_pxl;
}				t_floor;

typedef struct 	s_data{
	char*		cub_path;
	int			save;
	void		*mlx;
	void		*window;
	t_img		img;
	t_settings	settings;
	t_frame		frame;
	t_minimap	map;
	t_life		life;
	t_floor		floor;
	t_img		game_over_img;
	int			respawn;
}               t_data;

/*
** cub3d.c
*/
	void
check_args_errors(t_data *data, int argc, char **argv);
	int
start_game(t_data *data);
	int
main(int argc, char **argv);

/*
** bmp.c
*/
	unsigned char
*create_bmp_info_header(t_img *img);
	unsigned char
*create_bmp_file_header(t_img *img, int paddingSize);
	void
fill_bmp(t_data *data, unsigned char *image, t_img *img, int bmp_fd);
	char
*get_screenshot_path(t_data *data, char *path);
	void
create_bmp(t_data *data, t_img *img, char *path);

/*
** colors.c
*/
	unsigned char
*int_to_rgb(unsigned char *image, int color);
	void
get_color(t_data *data, char *line, char *color);

/*
** event.c
*/
	void
look_left(t_frame *frame);
	void
look_right(t_frame *frame);
	int
press_key(int key, t_data *data);
	int
red_cross(t_data *data);
	void
hook_event(t_data *data);

/*
** exit.c
*/
	int
close_program(t_data *data, char *error_msg, char *str);
	void
free_all(t_data *data);
	void
free_frame(t_data *data, t_frame *frame);
	void
free_sprites(t_settings *settings, t_frame *frame);
	void
free_settings(t_settings *settings);
	void
free_map(t_settings *settings);

/*
** frame.c
*/
	int
render_next_frame(t_data *data);
	void
perform_DDA(t_data *data, t_frame *frame);
	void
set_ray(t_data *data, t_frame *frame, int x);
	void
set_drawing_limits(t_data *data, t_frame *frame);
	void
draw_column(t_data *data, t_frame *frame, t_img *textimg, int x);

/*
** img.c
*/
	void
put_pixel(t_img *img, t_int pos, int color);
	void
create_img(t_data *data, char *path, t_img *img);

/*
** init.c
*/
	void
init_settings(t_settings *settings);
	void
init_dir_and_plane(t_settings *settings, t_frame *frame);
	void
init_sprites(t_data *data, t_settings *settings, t_frame *frame);
	void
init_frame(t_data *data, t_settings *settings, t_frame *frame);
	void
init_minimap(t_data *data, t_settings *settings, t_minimap *map);
	void
init_data(t_data *data);

/*
** map.c
*/
	int
is_map(t_data *data, t_settings *settings, int i, int j);
	int
check_map_errors(t_data *data, t_settings *settings);
	void
check_square_neighbors(t_data *data, t_settings *settings, int i, int j);
	char
**get_tmp_map(t_data *data, t_settings *settings, char**tmp, char *line);
	void
get_map(t_data *data, char *line, int i, t_settings *settings);

/*
 ** move.c
*/
	void
move_forward(t_frame *frame, char **map);
	void
move_backward(t_frame *frame, char **map);
	void
move_right(t_frame *frame, char **map);
	void
move_left(t_frame *frame, char **map);

/*
** parsing.c
*/
	int
settings_ok(t_data *data, t_settings *settings, char *line);
	int
check_settings(t_data *data, t_settings *settings, char *line);
	void
parse_line(t_data *data, char *line);
	void
get_sprites_data(t_data *data, t_settings *settings, char **map);
	void
parse_cub_file(t_data *data);

/*
** resolution.c
*/
	void
get_resolution(t_data *data, char *line, t_settings *settings);

/*
** sprites.c
*/
	void
draw_sprite_column(t_data *data, t_frame *frame, t_img *img, int stripe);
	void
set_sprite_drawing_limits(t_settings *settings, t_frame *frame, int i);
	void
draw_sprites(t_data *data, t_settings *settings, t_frame *frame);
	void
init_sprite_order(t_settings *settings, t_frame *frame);
	void
sort_sprites(t_settings *settings, t_frame *frame);

/*
** textures.c
*/
	t_img
*get_sprite_texture(t_frame *frame, char text_number);
	t_img
*get_wall_texture(t_frame *frame);
	void
get_texture_path(t_data *data, char *line, char *texture);

/*
** BONUSES
*/

/*
** game.c
*/
	int
game_over_answer(t_data *data, int key);
	void
game_over(t_data *data);

/*
** life_bar.c
*/
	void
sprite_hit(t_data *data);
	void
draw_life_bar(t_data *data, t_settings *settings, t_life *life);
	void
set_life_bar_limits(t_data *data, t_settings *settings, t_life *life);

/*
** mini_map.c
*/
	void
set_minimap_limits(double pos, double *case_min, double *case_max);
	void
get_minimap_face(t_data *data, t_minimap *map);
	void
draw_minimap_column(t_data *data, t_settings *settings, t_minimap *map, t_int pxl);
	void
draw_minimap(t_data *data, t_settings *settings, t_minimap *map);

/*
** floor.c
*/
	void
set_floor(t_data *data, t_settings *settings, t_floor *flr);

/*
** print.c (not evaluated)
*/
void	print_life_bar_data(t_data *data);
void	print_minimap_data(t_data *data);
void	print_settings(t_data *data);
void	print_situation(t_data *data);
void	print_ray(t_data *data);
void	print_sprite_list(t_data *data);
void	print_z_buffer(t_data *data);
void	print_map(t_data *data);
void	print_image(t_data *data);
void	print_current_sprite_data(t_data *data);

/*
** SOME GAME VARIABLES
*/
#define MINIMAP_SIZE 9.000000
//#define ROT_SPEED 0.5235987755983
#define ROT_SPEED 0.4235987755983
#define MOVE_SPEED 0.51
#define PLAYER_SIZE 1.00

/*
** IRRATIONAL NUMBERS
*/
#define PI 3.14159265358979323846

/*
** COLORS
*/
# define GREEN 65280
# define ORANGE 16746496
# define RED 16711680
# define GREY 7895673
# define DARK_GREY 0x2e2e2e
# define BLACK 0
# define WHITE 16777215

/*
** KEY VALUES
*/
# define KEY_D 2
# define KEY_N 45
# define KEY_P 35
# define KEY_Q 0
# define KEY_S 1
# define KEY_Y 16
# define KEY_Z 13
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
#endif
