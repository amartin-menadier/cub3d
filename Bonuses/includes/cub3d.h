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

typedef struct	s_dbl{
	double		x;
	double		y;
	double		z;
	double		angle;
}				t_dbl;

typedef struct	s_int{
	int			x;
	int			y;
	int			z;
}				t_int;

typedef struct  s_img{
	void		*ptr;
	char		*path;
	int			*colors;
	int			bpp;
	int			line_length;
	int			endian;
	t_int		size;
	int			name;
}               t_img;

typedef struct 	s_settings{
	int			fd;
	t_int		win_size;
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

typedef	struct	s_piclib
{
	t_img		ea;
	t_img		so;
	t_img		we;
	t_img		no;
	t_img		flr;
	t_img		sky;
	t_img		s2;
	t_img		s3;
	t_img		skybox;
	t_img		avatar;
	t_img		game_over;
	t_img		mask;
}				t_piclib;

typedef struct 	s_frame{
	t_dbl		pos;
	t_dbl		dir;
	t_dbl		plane;
	t_int		text; //dans sprite
	double		*z_buffer;
	int			*spr_order;
	double		*spr_dist;
	t_dbl		spr_inv;
	double		spr_screen_x;
	t_int		spr_size;
	t_int		spr_draw_start;
	t_int		spr_draw_end;
	int			spr_sorted;
	int			done;
}		t_frame;

typedef struct	s_minimap{
	t_dbl		case_min;
	t_dbl		case_max;
	int			size;
	double		radius;
	t_int		center;
	int			case_size;
	double		step_in_case;
	int			margin;
	t_int		draw_start;
	t_int		draw_end;
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
	t_dbl		ray;
	t_dbl		ray0;
	t_dbl		ray1;
	int			pxl_height;
	float		cam_height;
	float		depth;
	t_dbl		step;
	t_dbl		pos;
	t_int		cell;
	t_int		txt_pxl;
}				t_floor;

typedef struct 	s_data{
	char*		cub_path;
	int			save;
	void		*mlx;
	void		*window;
	t_img		scr;
	t_settings	settings;
	t_frame		frame;
	t_minimap	map;
	t_life		life;
	t_floor		floor;
	t_piclib	piclib;
	int			skybox;
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
free_image(t_data *data, t_img *img, int mod);
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
	double
perform_DDA(t_data *data, t_dbl pos, t_dbl ray, int mod);
	t_dbl
set_ray(t_data *data, t_frame *frame, t_int scr);
	int
set_drawing_limit(t_int win_size, double perp_wall_dist, int mod);
	void
draw_wall_column(t_data *data, t_int scr, t_dbl ray, double perp_wall_dist);

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
init_image(t_img *img, int name);
	void
init_piclib(t_piclib *piclib);
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
settings_ok(t_data *data, t_settings *settings, t_piclib *lib, char *line);
	int
check_settings(t_data *data, t_settings *settings, t_piclib *lib, char *line);
	void
parse_line(t_data *data, t_settings *settings, t_piclib *lib, char *line);
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
*get_sprite_image(t_piclib *lib, char text_number);
//	t_img
//*get_wall_image(t_data *data, t_frame *frame);
	void
get_image_path(t_data *data, t_piclib *lib, char *line, char *texture);

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
get_minimap_avatar(t_data *data, t_img *avatar);
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
** ROT_SPEED = 0.39 = PI/8 soit un 1 seizieme de tour de cercle
*/
#define MINIMAP_SIZE 9.000000
//#define ROT_SPEED 0.78539816339745
#define ROT_SPEED 0.39269908169872
//#define ROT_SPEED 0.3
#define MOVE_SPEED 0.51
#define PLAYER_SIZE 1.00
#define EA 0
#define SO 1
#define WE 2
#define NO 3
#define FLR 4
#define SKY 5
#define S2 20
#define S3 30
#define AVATAR 420
#define SKYBOX 100
#define GAME_OVER 666
#define MASK 200
#define WALL 49

/*
** IRRATIONAL NUMBERS
*/
#define PI 3.14159265358979323846

/*
** COLORS
*/
# define BLACK 0x000000
# define WHITE 0xffffff
# define RED 0xff0000
# define GREEN 0x00ff00
# define BLUE 0x0000ff
# define ORANGE 0xff8800
# define GREY 0x9e9e9e
# define DARK_GREY 0x2e2e2e

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
