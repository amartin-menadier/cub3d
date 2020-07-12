/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadier <amenadier@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:30:34 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/12 14:45:22 by amenadier        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void
	replace_cub_path(t_data *data, char *new_path)
{
	free(data->cub_path);
	data->cub_path = ft_strdup(new_path);
}

	t_dbl
get_first_angle(char c)
{
	t_dbl	angle;

	angle.y = 0;
	if (c == 'E')
		angle.x = 0;
	if (c == 'N')
		angle.x = PI / 2;
	if (c == 'W')
		angle.x = PI;
	if (c == 'S')
		angle.x = 3 * PI / 2;
	return (angle);
}

void
	create_piclib(t_data *data, t_piclib *piclib)
{
	create_img(data, piclib->ea.path, &piclib->ea);
	create_img(data, piclib->so.path, &piclib->so);
	create_img(data, piclib->we.path, &piclib->we);
	create_img(data, piclib->no.path, &piclib->no);
	create_img(data, piclib->flr.path, &piclib->flr);
	create_img(data, piclib->sky.path, &piclib->sky);
	create_img(data, piclib->s2.path, &piclib->s2);
	create_img(data, piclib->s3.path, &piclib->s3);
	create_img(data, piclib->s4.path, &piclib->s4);
	create_img(data, piclib->s5.path, &piclib->s5);
	create_img(data, piclib->s6.path, &piclib->s6);
	create_img(data, piclib->s7.path, &piclib->s7);
	create_img(data, piclib->s8.path, &piclib->s8);
	create_img(data, piclib->s9.path, &piclib->s9);
	create_img(data, piclib->no.path, &piclib->skybox);
	create_img(data, "./textures/intellolcut.xpm", &piclib->avatar);
	create_img(data, "./textures/gameover.xpm", &piclib->game_over);
	create_img(data, "./textures/victory.xpm", &piclib->victory);
	create_img(data, "./textures/civ_mask.xpm", &piclib->mask);
	if (data->skybox[0][0])
		create_skybox(data, piclib, &piclib->skybox);
}

void
	set_mlx(t_data *data, t_img *win, t_int win_size)
{
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, win_size.x, win_size.y, "Cub3D");
	win->ptr = mlx_new_image(data->mlx, win_size.x, win_size.y);
	win->colors = (int *)mlx_get_data_addr(win->ptr, &win->bpp,
			&win->line_length, &win->endian);
	win->size.x = win_size.x;
	win->size.y = win_size.y;
}

void
	set_game(t_data *data)
{
	parse_cub_file(data);
	set_mlx(data, &data->win, data->win.size);
	data->cam.y = data->win.size.y / 2;
	create_piclib(data, &data->piclib);
	if (!(data->z_buffer = malloc(sizeof(double *) * data->win.size.x)))
		close_program(data, "Failed allocating z_buffer while", "set_game");
}
