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
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}               t_img;

typedef struct 	s_settings{
	int	fd;
	int	Resx;
	int	Resy;
	char	*NO;
	char	*SO;//south
	char	*WE;
	char	*EA;
	char	*S;//sprite
	int	F;//Floor
	int	C;//Ceiling
}               t_settings;

typedef struct 	s_map{
	int		Width;
	int		Height;
	int		player_orientation;
	double		pos_x;
	double		pos_y;
	char	**map;
}				t_map;	

typedef struct 	s_ray{
	double	dirX;
	double	dirY;
	double	rayX;
	double	rayY;
	double	planeX;
	double	planeY;
	double	cameraX;
	double	time;
	double	oldTime;
	double	mapX;//current square ray is in
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
	int	NO;
	int	SO;
	int	WE;
	int	EA;
	int	S;
}		t_ray;

typedef struct 	s_data{
	void		*mlx;
	void		*win;
	t_img		img;
	t_settings	settings;
	t_map		map;
	t_ray		ray;
	int		keycode;
}               t_data;

/*
** cub3d.c
*/

int		close_window(t_data *data, int mod);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int     render_next_frame(t_data *data);

/*
** errors.c
*/

int		error_exit(t_data *data, char *Error_msg, char *str);
int		settings_is_set(t_settings *settings);
int		is_map(t_data *data, t_map *map, int i, int j);
void		check_map_neighbors(t_data *data, t_map *map, int i, int j);
void	check_map_errors(t_data *data, t_map *map);
void	check_settings_errors(t_data *data, char *line);
void	check_args_errors(t_data *data, int argc, char **argv);

/*
** event.c
*/

int		presskey(int keycode, t_data *data);
int		red_cross(t_data *data);
void	hook_event(t_data *data);

/*
** free_and_update.c
*/

void	update_image(t_data *data);
void	free_map(t_map *map);
void	free_settings(t_settings *settings);

/*
** init.c
*/

void	init_image(t_data *data, t_img *img);
void	init_window(t_data *data);
void	init_settings(t_settings *settings);
void	init_map(t_map *map);
void	init_ray(t_data *data, t_ray *ray);
void	init_data(t_data *data);

/*
** parsing.c
*/

void	parse_map(t_data *data, t_map *map);
void	parse_settings(t_data *data, char *line);
int		parse_cub(t_data *data);

/*
** settings.c
*/

char	**fill_tmp_map(t_data *data, t_map *map, char**tmp, char *line);
void	fill_map(t_data *data, char *line, int i, t_map *map);
void	fill_resolution(t_data *data, char *line, t_settings *settings);
void	fill_texture(t_data *data, char *line, char *texture);
void	fill_color(t_data *data, char *line, char *color);
void	fill_settings(t_data *data, char *line, int i);

/*
** TO BE DELETED
*/

void	print_params(t_data *data);

# define ESC 53
# define LOOK_LEFT 123
# define LOOK_RIGHT 124
# define MOVE_LEFT 0
# define MOVE_RIGHT 2
# define MOVE_FORWARD 13
# define MOVE_BACKWARD 1
#endif
