#ifndef _CUB3D_H_
# define _CUB3D_H_
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <mlx.h>
# include "../libft/libft.h"

typedef struct  s_img {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}               t_img;

typedef struct 	s_scene {
	int	fd;
	int	win_Rx;
	int	win_Ry;
	char	*NO;
	char	*SO;//south
	char	*WE;
	char	*EA;
	char	*S;//sprite
	int		F;//Floor
	int		C;//Ceiling
}               t_scene;

typedef struct 	s_map{
	int		x;
	int		y;
	int		player_orientation;
	int		pos_x;
	int		pos_y;
	char	**map;
}				t_map;	

typedef struct 	s_data {
	void	*mlx;
	void	*win;
	t_img	img;
	t_scene	scene;
	t_map	map;
	int	keycode;
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
int		scene_is_set(t_scene *scene);
int		is_map(t_data *data, t_map *map, int i, int j);
void		check_map_neighbors(t_data *data, t_map *map, int i, int j);
void	check_map_errors(t_data *data, t_map *map);
void	check_scene_errors(t_data *data, char *line);
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
void	free_scene(t_scene *scene);

/*
** init.c
*/

void	init_image(t_data *data, t_img *img);
void	init_window(t_data *data);
void	init_scene(t_scene *scene);
void	init_map(t_map *map);
void	init_data(t_data *data);

/*
** parsing.c
*/

void	parse_map(t_data *data, t_map *map);
void	parse_scene(t_data *data, char *line);
int		parse_cub(t_data *data);

/*
** scene.c
*/

char	**fill_tmp_map(t_data *data, t_map *map, char**tmp, char *line);
void	fill_map(t_data *data, char *line, int i, t_map *map);
void	fill_resolution(t_data *data, char *line, t_scene *scene);
void	fill_texture(t_data *data, char *line, char *texture);
void	fill_color(t_data *data, char *line, char *color);
void	fill_settings(t_data *data, char *line, int i);

/*
** TO BE DELETED
*/

void	print_params(t_data *data);

# define ESC 53
#endif
