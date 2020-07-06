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

#include "cub3d_bonus.h"

	void
init_image(t_img *img, int name)
{
	img->ptr = NULL;
	img->path = NULL;
	img->colors = NULL;
	img->name = name;
}

	void
init_piclib(t_piclib *piclib)
{
	init_image(&piclib->ea, EA);
	init_image(&piclib->so, SO);
	init_image(&piclib->we, WE);
	init_image(&piclib->no, NO);
	init_image(&piclib->flr, FLR);
	init_image(&piclib->sky, SKY);
	init_image(&piclib->s2, S2);
	init_image(&piclib->s3, S3);
	init_image(&piclib->skybox, SKYBOX);
	init_image(&piclib->avatar, AVATAR);
	init_image(&piclib->game_over, GAME_OVER);
	init_image(&piclib->mask, MASK);
}

/*
** in init_data, angle.z is init, even though it is not supposedly used
*/

	void
init_data(t_data *data)
{
	data->win.size.x = 0;
	data->win.size.y = 0;
	data->cam.x = 0;
	data->cam.y = - 1;
	data->cam.z = 0;
	data->angle.x = -1;
	data->angle.y = 0;
	data->angle.z = 0;
	data->map = NULL;
	data->map_size.x = 1;
	data->map_size.y = 1;
	data->map_size.z = 0;
	data->spr_count = 0;
	data->spr = NULL;
	data->z_buffer = NULL;
	data->time = clock();// a free ?
	data->current_event = 0;
	data->frame_done = 0;
}

	void
init_skybox(t_data *data)
{
	int		skybox;
	int		x;
	int		z;

	if (ft_memcmp(&data->cub_path[ft_strlen(data->cub_path) - 10], "skybox", 6))
		skybox = 0;
	else
		skybox = 1;
	x = 0;
	while (x < 3)
	{
		z = 0;
		while (z < 3)
		{
			data->skybox[z][x] = skybox * '1';
			z++;
		}
		x++;
	}
	if (skybox)
		data->skybox[1][1] = '0';
}

	void
init_all(t_data *data)
{
	data->life = 100;
	init_skybox(data);
	data->mlx = NULL;
	data->window = NULL;
	init_image(&data->win, 0);
	init_data(data);
	init_piclib(&data->piclib);
}
