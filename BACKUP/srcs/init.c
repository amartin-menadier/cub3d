/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:30:34 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/09 14:17:38 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_image(t_data *data, t_img *img)
{
	img->img = mlx_new_image(data->mlx, data->scene.win_Rx,
			data->scene.win_Ry);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	//bpp, line length et endian set automatiquement par mlx. Pas tout compris.
}

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->scene.win_Rx,
			data->scene.win_Ry, "Cub3D");
}

void	init_scene(t_scene *scene)
{
//	ft_putstr_fd("\nI GET INTO INIT_SCENE\n", 1);
	scene->win_Rx = -1;
	scene->win_Ry = -1;
	//recuperer ici la taile de l'ecran et mettre valeur Rx max et Ry max
	scene->NO = NULL;
	scene->SO = NULL;
	scene->WE = NULL;
	scene->EA = NULL;
	scene->S = NULL;
	scene->F = -1;
	scene->C = -1;
}

void	init_map(t_map *map)
{
	map->x = 1;
	map->y = 0;
	map->player_orientation = 0;
	map->pos_x = -1;
	map->pos_y = -1;
	map->map = NULL;
}

void	init_data(t_data *data)
{
	init_window(data);
	init_image(data, &data->img);
}
