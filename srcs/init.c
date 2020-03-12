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
	img->img = mlx_new_image(data->mlx, data->settings.Resx,
			data->settings.Resy);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	//bpp, line length et endian set automatiquement par mlx. Pas tout compris.
}

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->settings.Resx,
			data->settings.Resy, "Cub3D");
}

void	init_settings(t_settings *settings)
{
//	ft_putstr_fd("\nI GET INTO INIT_SCENE\n", 1);
	settings->Resx = -1;
	settings->Resy = -1;
	//recuperer ici la taile de l'ecran et mettre valeur Rx max et Ry max
	settings->NO = NULL;
	settings->SO = NULL;
	settings->WE = NULL;
	settings->EA = NULL;
	settings->S = NULL;
	settings->F = -1;
	settings->C = -1;
}

void	init_map(t_map *map)
{
	map->Width = 1;
	map->Height = 0;
	map->player_orientation = 0;
	map->pos_x = -1;
	map->pos_y = -1;
	map->map = NULL;
}

void	init_ray(t_data *data, t_ray *ray)
{
		//init le vecteur initiale direction du ray et vecteur camera plane
	if (data->map.player_orientation == 'N')
	{
		ray->dirX = 0;
		ray->dirY = -1;
		ray->planeX = 0.6;
		ray->planeY = 0;
	}
	if (data->map.player_orientation == 'E')
	{
		ray->dirX = 1;
		ray->dirY = 0;
		ray->planeX = 0;
		ray->planeY = 0.6;
	}
	if (data->map.player_orientation == 'S')
	{
		ray->dirX = 0;
		ray->dirY = 1;
		ray->planeX = -0.6;
		ray->planeY = 0;
	}
	if (data->map.player_orientation == 'W')//
	{
		ray->dirX = -1;
		ray->dirY = 0;
		ray->planeX = 0;
		ray->planeY = -0.6;
	}
	data->map.pos_x += 0.5;
	data->map.pos_y += 0.5;
	data->map.map[(int)data->map.pos_y][(int)data->map.pos_x] = '0';
	//		ray->mapX = (int)data->map.pos_x;
	//		ray->mapY = (int)data->map.pos_y;
	//	ray->planeX = 0;
	//	ray->planeY = 0.66;
	//		ray->cameraX = 0;
	//pour update ce sera cameraX = 2 * x / settingsResY - 1 
	ray->time = 0;
	ray->oldTime = 0;
	ray->hit = 0;
	//couleurs arbitraires a changer en textures.
	ray->NO = 16562691;
	ray->SO = 16711680;
	ray->WE = 19240321;
	ray->EA = 255;
	ray->S = 65280;
	//		ray->deltaDistX = fabs(1 / ray->raydirX);
}

void	init_data(t_data *data)
{
	init_window(data);
	init_image(data, &data->img);
	init_ray(data, &data->ray);
}
