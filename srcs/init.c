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

void	init_image(t_data *data, t_img *img)
{
	img->ptr = mlx_new_image(data->mlx, data->settings.win_width,
			data->settings.win_height);
	img->colors = (int *)mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	//bpp, line length et endian set automatiquement par mlx. Pas tout compris.
}

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->settings.win_width,
			data->settings.win_height, "Cub3D");
}

void	init_settings(t_settings *settings)
{
	settings->win_width = 0;
	settings->win_height = 0;
	//recuperer ici la taile de l'ecran et mettre valeur Rx max et Ry max
	settings->NO_path = NULL;
	settings->SO_path = NULL;
	settings->WE_path = NULL;
	settings->EA_path = NULL;
	settings->Sprite_path = NULL;
	settings->Floor_color = -1;
	settings->Ceiling_color = -1;
	settings->map_width = 1;
	settings->map_height = 0;
	settings->player_orientation = (char)NULL;
	settings->init_posX = -1;
	settings->init_posY = -1;
	settings->map = NULL;
}

void	init_frame(t_data *data, t_frame *frame)
{
		//init le vecteur initiale direction du frame et vecteur camera plane
	if (data->settings.player_orientation == 'N')
	{
		frame->dirX = 0;
		frame->dirY = -1;
		frame->planeX = 0.7;
		frame->planeY = 0;
	}
	if (data->settings.player_orientation == 'E')
	{
		frame->dirX = 1;
		frame->dirY = 0;
		frame->planeX = 0;
		frame->planeY = 0.7;
	}
	if (data->settings.player_orientation == 'S')
	{
		frame->dirX = 0;
		frame->dirY = 1;
		frame->planeX = -0.7;
		frame->planeY = 0;
	}
	if (data->settings.player_orientation == 'W')//
	{
		frame->dirX = -1;
		frame->dirY = 0;
		frame->planeX = 0;
		frame->planeY = -0.7;
	}
	data->frame.posX = data->settings.init_posX + 0.5;
	data->frame.posY = data->settings.init_posY + 0.5;
	data->settings.map[data->settings.init_posY][data->settings.init_posX] = '0';
	frame->time = 0;
	frame->oldTime = 0;
	frame->hit = 0;
	get_texture_img(data, data->settings.NO_path, &data->frame.NO_img);
	get_texture_img(data, data->settings.SO_path, &data->frame.SO_img);
	get_texture_img(data, data->settings.WE_path, &data->frame.WE_img);
	get_texture_img(data, data->settings.WE_path, &data->frame.EA_img);
//	get_texture_img(data, data->settings.Sprite_path, &data->frame.Sprite_img);
}

void	init_data(t_data *data)
{
	init_window(data);
	init_image(data, &data->img);
	init_frame(data, &data->frame);
}
