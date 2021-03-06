/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/22 16:14:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <time.h>

typedef struct	s_dbl{
	double		x;
	double		y;
	double		z;
}				t_dbl;

typedef struct	s_int{
	int			x;
	int			y;
	int			z;
}				t_int;

/*
** The struct img is used for each img the game uses ;
** ptr is the pointer to this img. It is created by the minilibx;
** bpp, line_length and endian are also mlx variables ;
** bpp means bits per pixels ; usually 32 with mlx functions ;
** colors stores the color for each pixel of an img. Ex : the color of pixel
** with coordinates (5 ; 7) will be colors[7 * img width + 5];
** size.x is the img width;
** size.y is the img height;
** name is used in some functions to determinate which img to pick;
*/

typedef struct	s_img{
	void		*ptr;
	char		*path;
	int			*colors;
	int			bpp;
	int			line_length;
	int			endian;
	t_int		size;
	int			name;
}				t_img;

/*
** piclib is simply a library of all imgs used for the game;
*/

typedef struct	s_piclib{
	t_img		ea;
	t_img		so;
	t_img		we;
	t_img		no;
	t_img		flr;
	t_img		sky;
	t_img		s2;
	t_img		s3;
	t_img		s4;
	t_img		s5;
	t_img		s6;
	t_img		s7;
	t_img		s8;
	t_img		s9;
	t_img		skybox;
	t_img		avatar;
	t_img		victory;
	t_img		game_over;
	t_img		mask;
}				t_piclib;

/*
** DATA STRUCTURE :
** mlx is a pointer to the whole mlx process ;
** window is a pointer to the created window ;
** win is the main img seen on screen ;
** Regarding map_size, (map_)height in tutorial is map_size.z here because the
** player travels depths not heights ; map_size.y is therefore the size of a
** wall, so the size of a cub side so 1. This choice is to match x, y and z of
** the cam variable ;
** z_buffer stores the size in pxl for the wall shown for each column of pixels
** of the current frame ;
** cam gives the position of the player / camera. x and are its position on the
** map. y is the height of the cam /eyes. This changes when certain types of
** events are called ;
** To understand the variable angle (unit : radians), one has to understand the
** trigonometric circle. See :
** https://fr.wikipedia.org/wiki/Cercle_trigonom%C3%A9trique#/
** mediaFichier:Unit_circle_angles_color.svg ;
** angle.x gives the cardinal point the cam is aiming at. Ex : for angle = 0,
** the player is looking east, for angle = PI / 2, the player looks north ;
** angle.y is the vertical view of the player. 0 for a look parallel to the
** floor. + to look up, - to look down ;
** angle.z makes no sense and is unused ;
** current_event stores the event happeningwhich started at the stored variable
** time ;
** save, skybox and frame_done are booleansused to know if the corresponding
** events are activated ,
*/

typedef struct	s_data{
	char		*cub_path;
	void		*mlx;
	void		*window;
	t_piclib	piclib;
	t_img		win;
	char		**map;
	t_int		map_size;
	char		skybox[3][3];
	double		*z_buffer;
	t_dbl		*spr;
	int			spr_count;
	t_dbl		cam;
	t_dbl		angle;
	int			current_event;
	clock_t		time;
	int			life;
	int			save;
	int			frame_done;
}				t_data;

/*
** cub3d.c
*/
void			close_program(t_data *data, char *error_msg, char *str);
int				start_game(t_data *data);

/*
** event.c and family files
*/
void			hook_event(t_data *data);
void			look(t_dbl *angle, int key);
void			move(t_data *data, char **map, t_dbl *pos, int key);
void			jump(t_data *data, clock_t time_diff);
void			kneel(t_data *data, int way);
void			sprite_hit(t_data *data);
void			game_over(t_data *data, t_int win_size, t_img *img);
int				game_over_answer(t_data *data, int key);
char			*new_level_path(char *old_path, char order);
void			load_new_level(t_data *data, char order);
int				victory(t_data *data, t_int win_size, t_img *img);

/*
** frame.c and family files
*/
int				render_next_frame(t_data *data);
double			ray_orientation(t_dbl ray);
t_dbl			get_side_dist(t_data *data, t_dbl cam, t_dbl ray);
int				drawing_limit(t_data *data, double perp_wall_dist, int mod);
t_dbl			set_ray(t_data *data, t_int win_size);
t_dbl			dda_step(t_dbl ray);
t_dbl			ray_to_wall(t_data *data, t_dbl ray, t_dbl step, int mod);
double			wall_side(t_data *data, t_dbl ray);
double			perp_wall_dist(t_data *data, t_dbl cam, t_dbl ray);
void			draw_walls(t_data *data, t_int *win_size);
void			draw_skybox(t_data *data, t_int *win_size);
void			draw_floor_and_sky(t_data *data, t_dbl angle, t_int win_size);
void			draw_sprites(t_data *data, t_piclib *lib);

/*
** interface.c and family files
*/
void			draw_interface(t_data *data, t_piclib *piclib);
void			draw_life_string(t_data *data);
void			draw_minimap(t_data *data, t_int center, double radius);
void			draw_lifebar(t_data *data, int length, int color);
int				lifebar_data(t_data *data, int mod);
void			get_minimap_avatar(t_data *data);
double			minimap_data(t_data *data, int mod);
void			get_minimap_avatar(t_data *data);
int				get_avatar_color
					(t_data *data, t_img *avatar, t_dbl minimap_pos, int color);
int				draw_script(t_data *data, int option);

/*
** settings.c and family files
*/
void			free_all(t_data *data);
void			free_data(t_data *data);
void			free_map(t_data *data, char **map, int ligns_to_free);
void			free_image(t_data *data, t_img *img);
t_dbl			get_first_angle(char c);
void			parse_cub_file(t_data *data);
void			init_all(t_data *data);
void			init_data(t_data *data);
void			set_game(t_data *data);
void			get_sprites_in_map(t_data *data, char **map);
double			sprite_data(t_data *data, t_dbl transform, t_int win, int mod);
void			sort_sprites(t_dbl pos, t_dbl *spr, int spr_count);
int				sprite_player_same_cell(t_data *data, int i);
t_img			*get_sprite_image(char **map, t_dbl spr, t_piclib *lib);
void			create_skybox(t_data *data, t_piclib *piclib, t_img *skybox);
void			check_cell_neighbors(t_data *data, int i, int j);
void			get_resolution(t_data *data, char *line);
int				check_map_errors(t_data *data);
void			get_map(t_data *data, char *line, int i);
void			replace_cub_path(t_data *data, char *new_path);
void			check_resolution(t_data *data);

/*
** tools.c and family files
*/
void			create_bmp(t_data *data, t_img *img, char *path);
void			put_pixel(t_img *img, t_int pos, int color);
void			create_img(t_data *data, char *path, t_img *img);
int				img_color(int *colors, int pxl_x, int pxl_y, t_int size);
t_dbl			rotate_point(double angle, t_dbl *ctr, t_dbl *old);
void			get_image_path
					(t_data *data, t_piclib *lib, char *line, char *texture);
double			dist(t_dbl obj1, t_dbl obj2);
unsigned char	*int_to_rgb(unsigned char *copy, int color);
double			square(double nb);
int				is_look(int	key);
int				is_move(int key);
int				is_wall(char map_element);
int				is_obstacle(char map_element);

# define PI 3.14159265358979323846

/*
** SOME GAME VARIABLES AND MODS
** ROT_SPEED = 0.39 = PI/8/ That is one sixteenth of a circle perimeter ;
*/
# define MINIMAP_CELLS 9.000000
# define ROT_SPEED 0.39269908169872
# define MOVE_SPEED 0.51
# define LOOK_SPEED 50
# define PLAYER_SIZE 1.00
# define JUMP 49
# define KNEEL 9
# define UNKNEEL 90
# define EA 0
# define SO 1
# define WE 2
# define NO 3
# define FLR 4
# define SKY 5
# define EMPTY '0'
# define CLASSIC_WALL '1'
# define DAMAGE_SPR '2'
# define HEAL_SPR '3'
# define PILLAR '4'
# define NORMINET '5'
# define SECRET '6'
# define STAIRS_DOWN '7'
# define STAIRS_UP '8'
# define ELEVATOR '9'
# define S2 12
# define S3 13
# define S4 14
# define S5 15
# define S6 16
# define S7 17
# define S8 18
# define S9 19
# define AVATAR 20
# define SKYBOX 21
# define GAME_OVER 22
# define MASK 23
# define VICTORY 24
# define SIZE_IN_PXL 30
# define CELL_SIZE 31
# define MARGIN 32
# define DRAW_START 330
# define DRAW_START_X 331
# define DRAW_START_Y 332
# define DRAW_END 340
# define DRAW_END_X 341
# define DRAW_END_Y 342
# define STEP_IN_CELL 35
# define RADIUS 36
# define CENTER 370
# define CENTER_X 371
# define CENTER_Y 372
# define LENGTH 40
# define WIDTH 41
# define HEIGHT 42
# define DEPTH 43
# define SIZE 44
# define SCREEN_X 50

/*
** SOME COLORS
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
# define A 97
# define W 119
# define Z 122
# define Q 113
# define S 115
# define D 100
# define V 118
# define SPACE 32
# define N 110
# define P 112
# define Y 121
# define ESC 65307
# define LEFT 65361
# define RIGHT 65363
# define DOWN 65364
# define UP 65362
#endif
