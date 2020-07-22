/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_free_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:30:34 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/20 17:37:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void
	free_image(t_data *data, t_img *img)
{
	if (img->path != NULL)
		free(img->path);
	img->path = NULL;
	if (img->ptr != NULL)
		mlx_destroy_image(data->mlx, img->ptr);
	img->ptr = NULL;
}

void
	free_piclib(t_data *data, t_piclib *lib)
{
	free_image(data, &lib->ea);
	free_image(data, &lib->so);
	free_image(data, &lib->we);
	free_image(data, &lib->no);
	free_image(data, &lib->flr);
	free_image(data, &lib->sky);
	free_image(data, &lib->s2);
	free_image(data, &lib->s3);
	free_image(data, &lib->s4);
	free_image(data, &lib->s5);
	free_image(data, &lib->s6);
	free_image(data, &lib->s7);
	free_image(data, &lib->s8);
	free_image(data, &lib->s9);
	free_image(data, &lib->avatar);
	free_image(data, &lib->skybox);
	free_image(data, &lib->game_over);
	free_image(data, &lib->victory);
	free_image(data, &lib->mask);
}

void
	free_map(t_data *data, char **map, int ligns_to_free)
{
	int	i;

	i = 0;
	if (map != NULL)
	{
		while (i < ligns_to_free)
		{
			if (map[i] != NULL)
			{
				free(map[i]);
				map[i] = NULL;
			}
			i++;
		}
		free(map);
		map = NULL;
	}
	if (data)
	{
		data->map_size.x = 0;
		data->map_size.z = 0;
	}
}

void
	free_data(t_data *data)
{
	free_map(data, data->map, data->map_size.z);
	if (data->spr != NULL)
		free(data->spr);
	data->spr = NULL;
	if (data->z_buffer != NULL)
		free(data->z_buffer);
	data->z_buffer = NULL;
}

void
	free_all(t_data *data)
{
	free(data->cub_path);
	data->cub_path = NULL;
	data->save = 0;
	free_data(data);
	free_piclib(data, &data->piclib);
	mlx_destroy_image(data->mlx, data->win.ptr);
	data->win.ptr = NULL;
	mlx_destroy_window(data->mlx, data->window);
}
