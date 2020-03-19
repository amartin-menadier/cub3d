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


typedef struct  s_img{
	void	*ptr;
	int		*colors;
	int		bits_per_pixel;
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
}               t_settings;

/*
//potentiellement a degager...
typedef struct 	s_map{
	int		Width;
	int		Height;
	int		player_orientation;
	double		pos_x;
	double		pos_y;
	char	**map;
}				t_map;	
*/

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
	double	time;
	double	oldTime;
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
}		t_frame;

typedef struct 	s_data{
	void		*mlx;
	void		*win;
	t_img		img;
	t_settings	settings;
	t_frame		frame;
	int		keycode;
}               t_data;

/*
** cub3d.c
*/

void	check_args_errors(t_data *data, int argc, char **argv);
int		main(int argc, char **argv);

/*
** colors.c
*/

void	fill_color(t_data *data, char *line, char *color);

/*
** event.c
*/

int		presskey(int keycode, t_data *data);
int		red_cross(t_data *data);
void	hook_event(t_data *data);

/*
** exit.c
*/

int		close_program(t_data *data, char *error_msg, char *str);
void	free_settings(t_settings *settings);
void	free_map(t_settings *settings);

/*
** frame.c
*/

void	draw_colum(t_data *data, t_frame *frame, t_img *textimg, int x);
t_img	*pick_texture(t_frame *frame);
void	set_drawing_limits(t_data *data, t_frame *frame);
void	perform_DDA(t_data *data, t_frame *frame);
void	set_ray(t_data *data, t_frame *frame, int x);
int     render_next_frame(t_data *data);

/*
** img.c
*/

int		render_texture(t_data *data, t_img *textimg, int x, int y);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	get_texture_img(t_data *data, char *path, t_img *textimg);

/*
** init.c
*/

void	init_image(t_data *data, t_img *img);
void	init_window(t_data *data);
void	init_settings(t_settings *settings);
void	init_frame(t_data *data, t_frame *frame);
void	init_data(t_data *data);

/*
** map.c
*/

int		is_map(t_data *data, t_settings *settings, int i, int j);
void	check_map_errors(t_data *data, t_settings *settings);
void	check_square_neighbors(t_data *data, t_settings *settings, int i, int j);
char	**fill_tmp_map(t_data *data, t_settings *settings, char**tmp, char *line);
void	fill_map(t_data *data, char *line, int i, t_settings *settings);

/*
** parsing.c
*/

int		settings_all_set(t_data *data, t_settings *settings, char *line);
int		check_settings(t_data *data, t_settings *settings, char *line);
void	parse_line(t_data *data, char *line);
int		parse_cub(t_data *data);

/*
** resolution.c
*/

void	fill_resolution(t_data *data, char *line, t_settings *settings);

/*
** textures.c
*/

void	fill_texture(t_data *data, char *line, char *texture);

/*
** TO BE DELETED
*/

void	print_params(t_data *data);

/*
** KEY VALUES
*/

# define ESC 53
# define LOOK_LEFT 123
# define LOOK_RIGHT 124
# define MOVE_LEFT 0
# define MOVE_RIGHT 2
# define MOVE_FORWARD 13
# define MOVE_BACKWARD 1
#endif
