/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:30:34 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:19 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	t_dbl
get_first_angle(char c)
{
	t_dbl	angle;

	angle.z = 0;
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
	create_img(data, piclib->no.path, &piclib->skybox);
	create_img(data, "./textures/intellolcut.xpm", &piclib->avatar);
	create_img(data, "./textures/gameover.xpm", &piclib->game_over);
	create_img(data, "./textures/civ_mask.xpm", &piclib->mask);
	if (data->skybox)
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
set_skymap(t_data *data)
{
	int		i;
	int		j;

	data->map_size.x = 1000;
	data->map_size.z = 1000;
	if (!(data->map = malloc(sizeof(char *) * data->map_size.z)))
		close_program(data, "Failed allocating skybox map ligns", "");
	i = 0;
	while (i < data->map_size.z)
	{
		if (!(data->map[i] = malloc(sizeof(char) * (data->map_size.x + 1))))
			close_program(data, "Failed allocating skybox map lign", "");
		data->map[i][data->map_size.x] = '\0';
		j = 0;
		while (j < data->map_size.x)
		{
			if (!i || i == data->map_size.z || !j || j == data->map_size.x - 1)
				data->map[i][j] = 1;
			else
				data->map[i][j] = 0;
			j++;
		}
		i++;
	}
}
	void
set_game(t_data *data)
{
	parse_cub_file(data);
	set_mlx(data, &data->win, data->win.size);
	data->cam.y = data->win.size.y / 2;
	create_piclib(data, &data->piclib);
	if (data->skybox)
	{
		ft_putstr_fd("\nset_game1", 1);
		free_data(data);
		ft_putstr_fd("\nset_game2", 1);
		set_skymap(data);
		ft_putstr_fd("\nset_game3", 1);
		data->cam.x = data->map_size.x / 2;
		data->cam.z = data->map_size.z / 2;
	}
	if (!(data->z_buffer = malloc(sizeof(double *) * data->win.size.x)))
		close_program(data, "Failed allocating z_buffer while", "set_game");
}
