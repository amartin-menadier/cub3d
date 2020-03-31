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

	int
close_program(t_data *data, char *error_msg, char *str)
{
	if (ft_memcmp(str, "\\o/\n", 4))
		ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(error_msg, 1);
	ft_putstr_fd(str, 1);
	free_settings(&data->settings);
	if(data->settings.done)
	{
		free_frame(data, &data->frame);
		mlx_destroy_image(data->mlx, data->img.ptr);
		mlx_destroy_window(data->mlx, data->window);
	}
	ft_putstr_fd("\n_END_OF_PROGRAM_\n", 1);
//	system("sudo leaks Cub3D"); //a supprimer
	exit(0);
	return (0);
}

	void
free_frame(t_data *data, t_frame *frame)
{
	mlx_destroy_image(data->mlx, data->frame.NO_img.ptr);
	mlx_destroy_image(data->mlx, data->frame.SO_img.ptr);
	mlx_destroy_image(data->mlx, data->frame.EA_img.ptr);
	mlx_destroy_image(data->mlx, data->frame.WE_img.ptr);
	mlx_destroy_image(data->mlx, data->frame.S_img.ptr);
	free(frame->z_buffer);
	frame->z_buffer = NULL; 
	free(frame->spr_order);
	frame->spr_order = NULL;
	free(frame->spr_dist);
	frame->spr_dist = NULL;
}

	void
free_sprites(t_settings *settings)
{
	if (settings->spr_x != NULL)
		free(settings->spr_x);
	if (settings->spr_y != NULL)
		free(settings->spr_y);
	if (settings->spr_text != NULL)
		free(settings->spr_text);
	settings->spr_x = NULL;
	settings->spr_y = NULL;
	settings->spr_text = NULL;
}

	void
free_settings(t_settings *settings)
{
	if (settings->NO_path != NULL)
		free(settings->NO_path);
	if (settings->SO_path != NULL)
		free(settings->SO_path);
	if (settings->WE_path != NULL)
		free(settings->WE_path);
	if (settings->EA_path != NULL)
		free(settings->EA_path);
	if (settings->S_path != NULL)
		free(settings->S_path);
	settings->NO_path = NULL;
	settings->SO_path = NULL;
	settings->WE_path = NULL;
	settings->EA_path = NULL;
	settings->S_path = NULL;
	free_sprites(settings);
	free_map(settings);
}

	void
free_map(t_settings *settings)
{
	int i;

	i = 0;
	if (settings->map != NULL)
	{
		while (i < settings->map_size.y)
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
