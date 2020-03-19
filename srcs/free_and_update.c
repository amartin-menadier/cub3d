/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:34:33 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 16:27:17 by amartin-         ###   ########.fr       */
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
		while (i < map->Height)
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

void	free_settings(t_settings *settings)
{
	if (settings->NO.colors != NULL)
		free(settings->NO.colors);
	if (settings->SO.colors != NULL)
		free(settings->SO.colors);
	if (settings->WE.colors != NULL)
		free(settings->WE.colors);
	if (settings->EA.colors != NULL)
		free(settings->EA.colors);
	if (settings->S != NULL)
		free(settings->S);
	settings->NO.colors = NULL;
	settings->SO.colors = NULL;
	settings->WE.colors = NULL;
	settings->EA.colors = NULL;
	settings->S = NULL;
}
