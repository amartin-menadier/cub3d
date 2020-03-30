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


typedef struct	s_vector{
	int		x;
	int		y;
	int		z;
}				t_vector;

typedef struct  s_img{
	void	*ptr;
	int		*colors;
	int		bpp;
	int		line_length;
	int		endian;
	int		th;
	int		tw;
}               t_img;

typedef struct 	s_settings{
	int		fd;
	int		win_width;
	int		win_height;
	char	*NO_path;
	char	*SO_path;
	char	*EA_path;
	char	*WE_path;
	char	*Sprite_path;
	int		Floor_color;
	int		Ceiling_color;
	char	**map;
	int		map_width;
	int		map_height;
	char	player_orientation;
	int		init_posX;
	int		init_posY;
	int		numSprites;
	double	*spritex;
	double	*spritey;
	char	*spritetext;
}               t_settings;

typedef struct 	s_frame{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	rayX;
	double	rayY;
	double	planeX;
	double	planeY;
	double	cameraX;
	double	mapX;
	double	mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int	stepX;
	int	stepY;
	int	hit;
	int	side;
	int	lineHeight;
	int	drawStart;
	int	drawEnd;
	double	wallX;
	int		texX;
	int		texY;
	t_img	NO_img;
	t_img	SO_img;
	t_img	EA_img;
	t_img	WE_img;
	t_img	Sprite_img;
	double	*Zbuffer;
	int		*spriteorder;
	double	*spritedist;
	double	spriteX;
	double	spriteY;
	double	invDet;
	double	transfX;
	double	transfY;
	int		spriteScreenX;
	int		spriteHeight;
	int		spriteWidth;
	int		drawStartY;
	int		drawEndY;
	int		drawStartX;
	int		drawEndX;
//@:int		texSX;
//	int		texSY;
	int		sprites_sorted;
}		t_frame;

typedef struct 	s_data{
	void		*mlx;
	void		*window;
	t_img		img;
	t_settings	settings;
	t_frame		frame;
	int		save;
}               t_data;

/*
 ** cub3d.c
 */
void
check_args_errors(t_data *data, int argc, char **argv);
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
free_frame(t_data *data, t_frame *frame);
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
put_pixel(t_img *img, t_vector *vector, int color);
	void
create_texture_img(t_data *data, char *path, t_img *textimg);

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
	int
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
draw_sprites(t_data *data, t_settings *settings, t_frame *frame, t_img *textimg);
	void
init_sprite_order(t_settings *settings, t_frame *frame);
	void
sort_sprites(t_settings *settings, t_frame *frame);
/*
 ** textures.c
 */
	t_img
*get_texture_img(t_frame *frame);
	void
get_texture(t_data *data, char *line, char *texture);

/*
 ** print.c TO BE DELETED
 */
void	print_settings(t_data *data);
void	print_situation(t_data *data);
void	print_ray(t_data *data);
void	print_sprites(t_data *data);
void	print_Zbuffer(t_data *data);
void	print_map(t_data *data);
void	print_image(t_data *data);

/*
 ** KEY VALUES
 */
# define KEY_Q 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Z 13
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_P 35 
#endif
