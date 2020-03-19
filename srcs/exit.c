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

int		close_program(t_data *data, char *error_msg, char *str)
{
	if (ft_memcmp(str, "\\o/\n", 4))
		ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(error_msg, 1);
	ft_putstr_fd(str, 1);
	print_params(data);
	free_settings(&data->settings);
	//penser a free les img des structures
	mlx_destroy_image(data->mlx, data->img.ptr);
	mlx_destroy_window(data->mlx, data->win);
	ft_putstr_fd("\nEND_OF_PROGRAM\n", 1);//a supprimer
//	system("sudo leaks Cub3D"); //a supprimer
	exit(0);
	return (0);
}

void	free_settings(t_settings *settings)
{
	if (settings->NO_path != NULL)
		free(settings->NO_path);
	if (settings->SO_path != NULL)
		free(settings->SO_path);
	if (settings->WE_path != NULL)
		free(settings->WE_path);
	if (settings->EA_path != NULL)
		free(settings->EA_path);
	if (settings->Sprite_path != NULL)
		free(settings->Sprite_path);
	settings->NO_path = NULL;
	settings->SO_path = NULL;
	settings->WE_path = NULL;
	settings->EA_path = NULL;
	settings->Sprite_path = NULL;
	free_map(settings);
}

void	free_map(t_settings *settings)
{
	int i;

	i = 0;
	if (settings->map != NULL)
	{
		while (i < settings->map_height)
		{
			if (settings->map[i] != NULL)
			{
				free(settings->map[i]);
				settings->map[i] = NULL;
			}
			i++;
		}
		free(settings->map);
		settings->map = NULL;
	}
}
