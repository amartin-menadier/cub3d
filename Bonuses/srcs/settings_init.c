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

	void
init_set(t_set *set)
{
	set->win_size.x = 0;
	set->win_size.y = 0;
	set->pos.x = 0;
	set->pos.y = 0;
	set->angle = -1;
	set->map = NULL;
	set->map_size.x = 1;
	set->map_size.y = 0;
	set->spr_count = 0;
	set->spr = NULL;
	set->z_buffer = NULL;
	set->frame_done = 0;
}

	void
init_all(t_data *data)
{
	data->set.life = 100;
	data->skybox = 1;
	if(ft_memcmp(&data->cub_path[ft_strlen(data->cub_path) - 10], "skybox", 6))
		data->skybox = 0;
	data->mlx = NULL;
	data->window = NULL;
	init_image(&data->scr, 0);
	init_set(&data->set);
	init_piclib(&data->piclib);
}
