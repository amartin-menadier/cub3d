/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 12:15:52 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	free_image(data, &lib->avatar);
	free_image(data, &lib->skybox);
	free_image(data, &lib->game_over);
	free_image(data, &lib->mask);
}

	void
free_map(char **map, int ligns_to_free)
{
	int i;

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
}

	void
free_set(t_set *set)
{
	free_map(set->map, set->map_size.y);
	if (set->spr != NULL)
		free(set->spr);
	set->spr = NULL;
	if (set->z_buffer != NULL)
		free(set->z_buffer);
	set->z_buffer = NULL; 
}

	void
free_all(t_data *data)
{
	free(data->cub_path);
	data->cub_path = NULL;
	data->save = 0;
	free_set(&data->set);
	free_piclib(data, &data->piclib);
	mlx_destroy_image(data->mlx, data->scr.ptr);
	data->scr.ptr = NULL;
	mlx_destroy_window(data->mlx, data->window);
}
