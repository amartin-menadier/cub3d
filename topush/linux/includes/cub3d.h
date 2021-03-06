/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/23 19:07:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include "../mlx/mlx.h"
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

typedef struct	s_img{
	void		*ptr;
	int			*colors;
	int			bpp;
	int			line_length;
	int			endian;
	t_int		size;
}				t_img;

typedef struct	s_settings{
	int			fd;
	t_int		win_size;
	char		*no_path;
	char		*so_path;
	char		*ea_path;
	char		*we_path;
	char		*s_path;
	int			floor_color;
	int			ceiling_color;
	char		**map;
	t_int		map_size;
	int			map_done;
	char		player_orientation;
	t_int		starting_pos;
	int			spr_count;
	double		*spr_x;
	double		*spr_y;
	char		*spr_text;
	int			done;
}				t_settings;

typedef struct	s_frame{
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
	t_img		no_img;
	t_img		so_img;
	t_img		ea_img;
	t_img		we_img;
	t_img		s_img;
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
}				t_frame;

typedef struct	s_data{
	void		*mlx;
	void		*win;
	t_img		img;
	t_settings	settings;
	t_frame		frame;
	int			save;
}				t_data;

/*
** cub3d.c
*/
void			check_args_errors(t_data *data, int argc, char **argv);
int				main(int argc, char **argv);

/*
** bmp.c
*/
unsigned char	*create_bmp_info_header(t_img *img);
unsigned char	*create_bmp_file_header(t_img *img, int padding_size);
void			fill_bmp(t_data *data,
					unsigned char *image, t_img *img, int bmp_fd);
char			*get_screenshot_path(t_data *data, char *path);
void			create_bmp(t_data *data, t_img *img, char *path);

/*
** colors.c
*/
unsigned char	*int_to_rgb(unsigned char *image, int color);
void			get_color(t_data *data, char *line, char *color);

/*
** event.c
*/
void			look_left(t_frame *frame);
void			look_right(t_frame *frame);
int				press_key(int key, t_data *data);
int				red_cross(t_data *data);
void			hook_event(t_data *data);

/*
** exit.c
*/
int				close_program(t_data *data, char *error_msg, char *str);
void			free_frame(t_data *data, t_frame *frame);
void			free_settings(t_settings *settings);
void			free_map(t_settings *settings);

/*
** frame.c
*/
int				render_next_frame(t_data *data);
void			perform_dda(t_data *data, t_frame *frame);
void			set_ray(t_data *data, t_frame *frame, int x);
void			set_drawing_limits(t_data *data, t_frame *frame);
void			draw_column(t_data *data,
					t_frame *frame, t_img *textimg, int x);

/*
** img.c
*/
t_int			check_texture_pxl(t_int text, t_int img_size);
void			put_pixel(t_img *img, t_int pos, int color);
void			create_texture_img(t_data *data, char *path, t_img *textimg);

/*
** init.c
*/
void			init_settings(t_settings *settings);
void			init_dir_and_plane(t_settings *settings, t_frame *frame);
void			init_sprites(t_data *data,
					t_settings *settings, t_frame *frame);
void			init_frame(t_data *data, t_settings *settings, t_frame *frame);
void			init_data(t_data *data);

/*
** map.c
*/
int				is_map(t_data *data, t_settings *settings, int i, int j);
int				check_map_errors(t_data *data, t_settings *settings);
void			check_square_neighbors(t_data *data,
					t_settings *settings, int i, int j);
char			**get_tmp_map(t_data *data,
					t_settings *settings, char**tmp, char *line);
void			get_map(t_data *data, char *line, int i, t_settings *settings);

/*
 ** move.c
*/
void			move_forward(t_frame *frame, char **map);
void			move_backward(t_frame *frame, char **map);
void			move_right(t_frame *frame, char **map);
void			move_left(t_frame *frame, char **map);

/*
** parsing.c
*/
int				settings_ok(t_data *data, t_settings *settings, char *line);
int				check_settings(t_data *data, t_settings *settings, char *line);
void			parse_line(t_data *data, char *line);
void			get_sprites_data(t_data *data,
					t_settings *settings, char **map);
void			parse_cub_file(t_data *data);

/*
** resolution.c
*/
void			check_resolution(t_data *data, t_settings *settings);
void			get_resolution(t_data *data, char *line, t_settings *settings);

/*
** sprites.c
*/
void			draw_sprites(t_data *data,
					t_settings *settings, t_frame *frame, t_img *textimg);
void			init_sprite_order(t_settings *settings, t_frame *frame);
void			sort_sprites(t_settings *settings, t_frame *frame);

/*
** textures.c
*/
t_img			*get_texture_img(t_frame *frame);
void			get_texture(t_data *data, char *line, char *texture);

/*
** KEY VALUES
*/
# define KEY_A 97
# define KEY_W 119
# define KEY_Q 113
# define KEY_S 115
# define KEY_D 100
# define KEY_Z 122
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_P 112
#endif
