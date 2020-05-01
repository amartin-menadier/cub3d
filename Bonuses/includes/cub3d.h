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
}				t_dbl;

typedef struct	s_int{
	int			x;
	int			y;
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

typedef struct 	s_set{
	t_int		win_size;
	char		**map;
	t_int		map_size;
	int			spr_count;
	t_dbl		*spr;
	t_dbl		pos;
	double		angle;
	double		*z_buffer;
	int			life;
	int			frame_done;
}               t_set;

typedef struct	s_piclib{
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

typedef struct 	s_data{
	char*		cub_path;
	int			save;
	int			skybox;
	void		*mlx;
	void		*window;
	t_img		scr;
	t_set		set;
	t_piclib	piclib;
}               t_data;

	t_dbl
transform_sprite(double angle, t_dbl dist);
	double
sprite_data(t_set *set, t_dbl transform, int mod);
/*
** cub3d.c
*/
	void
close_program(t_data *data, char *error_msg, char *str);
	int
start_game(t_data *data);
	int
main(int argc, char **argv);

/*
** bmp.c
*/
	void
create_bmp(t_data *data, t_img *img, char *path);


/*
** color_tools.c
*/
	int
get_img_color(t_img img, int pxl_x, int pxl_y, t_int size);
	unsigned char
*int_to_rgb(unsigned char *copy, int color);

/*
** event.c
*/
	void
hook_event(t_data *data);

/*
** free.c
*/
	void
free_image(t_data *data, t_img *img);
	void
free_all(t_data *data);
	void
free_map(char **map, int ligns_to_free);
	void
free_set(t_set *set);

/*
** frame.c
*/
	int
render_next_frame(t_data *data);
	double
perform_DDA(t_data *data, t_dbl pos, t_dbl ray, int mod);
	int
set_drawing_limit(t_int win_size, double perp_wall_dist, int mod);

/*
** img.c
*/
	t_img
get_sprite_image(char **map, t_dbl spr, t_piclib lib);
	void
get_image_path(t_data *data, t_piclib *lib, char *line, char *texture);
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
init_set(t_set *set);
	void
set_game(t_data *data, t_set *set);
	void
init_all(t_data *data);

/*
** interface.c
*/
	void
draw_interface(t_data *data, t_piclib*piclib, t_set *set);

/*
** map.c
*/

	int
check_map_errors(t_data *data, t_set *set);
	void
check_cell_neighbors(t_data *data, t_set *set, int i, int j);
	void
get_map(t_data *data, char *line, int i, t_set *set);

/*
 ** move.c
*/
	void
move(t_set *set, char **map, int key);

/*
** parsing.c
*/
	void
get_sprites_data(t_data *data, t_set *set, char **map);
	void
parse_cub_file(t_data *data);

/*
** resolution.c
*/
	void
get_resolution(t_data *data, char *line, t_set *set);

/*
 * set_game.c
 */
	void
get_dir_and_plane(t_set *set);


/*
** skybox.c
*/
	void
create_skybox(t_data *data, t_piclib *piclib, t_img *skybox);

/*
** sprites.c and sprite_utils.c
*/
	void
draw_sprites(t_data *data, t_piclib lib, t_set *set);
	int
sprite_player_same_cell(t_set *set, int i);
	int
get_sprite_x(t_img img, int scr_x, int width_on_screen, double center_x);
	int
get_sprite_y(t_data *data, t_img img, int scr_y, int height_on_scr);
/*
** textures.c
*/

/*
 * math_utils.c
*/
	double
dist(t_dbl pos, t_dbl obj);
	t_dbl
rotate_point(double angle, t_dbl *ctr, t_dbl *old);

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
	int
lifebar_data(t_data *data, int mod);

/*
** minimap.c
*/
	void
get_minimap_avatar(t_data *data);
	double
minimap_data(t_data *data, int mod);
	void
draw_minimap(t_data *data, t_int center, double radius);
	void
get_minimap_avatar(t_data *data);
	int
get_avatar_color(t_data *data, t_img avatar, t_dbl minimap_pos, int color);

/*
** floor.c
*/
	void
draw_floor_and_sky(t_data *data,
double angle, t_int win_size);

/*
** print.c (not evaluated)
*/
void	print_life_bar_data(t_data *data);
void	print_minimap_data(t_data *data);
void	print_set(t_data *data);
void	print_situation(t_data *data);
void	print_ray(t_data *data);
void	print_sprite_list(t_data *data);
void	print_z_buffer(t_data *data);
void	print_map(t_data *data);
void	print_image(t_data *data);
void	print_current_sprite_data(t_data *data);

/*
** SOME GAME VARIABLES AND MODS
** ROT_SPEED = 0.39 = PI/8 soit un 1 seizieme de tour de cercle
*/
#define MINIMAP_CELLS 9.000000
#define ROT_SPEED 0.39269908169872
#define MOVE_SPEED 0.51
#define PLAYER_SIZE 1.00
#define WALL 49
#define EA 0
#define SO 1
#define WE 2
#define NO 3
#define FLR 4
#define SKY 5
#define S2 12
#define S3 13
#define AVATAR 20
#define SKYBOX 21
#define GAME_OVER 22
#define MASK 23
#define SIZE_IN_PXL 30
#define CELL_SIZE 31
#define MARGIN 32
#define DRAW_START 330
#define DRAW_START_X 331
#define DRAW_START_Y 332
#define DRAW_END 340
#define DRAW_END_X 341
#define DRAW_END_Y 342
#define STEP_IN_CELL 35
#define RADIUS 36
#define CENTER 370
#define CENTER_X 371
#define CENTER_Y 372
#define LENGTH 40
#define WIDTH 41
#define HEIGHT 42
#define DEPTH 43
#define SIZE 44
#define SCREEN_X 50

/*
** PI
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
# define Z 13
# define Q 0
# define S 1
# define D 2
# define MOVE(x) (x == Z || x == Q || x == S || x == D)
# define N 45
# define P 35
# define Y 16
# define ESC 53
# define LEFT 123
# define RIGHT 124
# define UP -99999
# define DOWN -9999
# define LOOK(x) (x == LEFT || x == RIGHT || x == UP || x == DOWN)
#endif
