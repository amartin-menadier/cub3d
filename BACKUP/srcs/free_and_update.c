/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:34:33 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/08 19:53:12 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_image(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	init_image(data, &data->img);
}

void	free_map(t_map *map)
{
	int i;

	i = 0;
	if (map->map != NULL)
	{
		while (i < map->y - 1)
		{
			if (map->map[i] != NULL)
			{
				free(map->map[i]);
				map->map[i] = NULL;
			}
			i++;
		}
		free(map->map);
		map->map = NULL;
	}
}

void	free_scene(t_scene *scene)
{
	if (scene->NO != NULL)
		free(scene->NO);
	if (scene->SO != NULL)
		free(scene->SO);
	if (scene->WE != NULL)
		free(scene->WE);
	if (scene->EA != NULL)
		free(scene->EA);
	if (scene->S != NULL)
		free(scene->S);
	scene->NO = NULL;
	scene->SO = NULL;
	scene->WE = NULL;
	scene->EA = NULL;
	scene->S = NULL;
}
