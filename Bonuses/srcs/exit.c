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
		ft_putstr_fd("\nEXIT01", 1);
	free(data->cub_path);
		data->cub_path = NULL;
		ft_putstr_fd("\nEXIT02", 1);
	free_all(data);
	/*
	free_settings(&data->settings);

	if(data->settings.done)
	{
		free_frame(data, &data->frame);
		free_sprites(&data->settings, &data->frame);
		mlx_destroy_image(data->mlx, data->mini_map.player_img.ptr);
		if (data->life.value <= 0)
			mlx_destroy_image(data->mlx, data->game_over_img.ptr);
		mlx_destroy_image(data->mlx, data->img.ptr);
		mlx_destroy_window(data->mlx, data->window);
	}
	*/
	mlx_destroy_image(data->mlx, data->img.ptr);
		data->img.ptr = NULL;
		ft_putstr_fd("\nEXIT13", 1);
		ft_putstr_fd("\n--", 1);

	mlx_destroy_window(data->mlx, data->window);
	ft_putstr_fd("\n_END_OF_PROGRAM_\n", 1);
	//	system("sudo leaks Cub3D"); //a supprimer
	exit(0);
	return (0);
}

	void
free_all(t_data *data)
{
		ft_putstr_fd("\nEXIT10", 1);
	free_settings(&data->settings);
	if(data->settings.done)
	{
		ft_putstr_fd("\nEXIT11", 1);
		free_frame(data, &data->frame);
		ft_putstr_fd("\nEXIT12", 1);
		free_sprites(&data->settings, &data->frame);
		ft_putstr_fd("\nEXIT13", 1);
		mlx_destroy_image(data->mlx, data->map.face.ptr);
		data->map.face.ptr = NULL;
		ft_putstr_fd("\nEXIT14", 1);
		if (data->respawn > 0)
			mlx_destroy_image(data->mlx, data->game_over_img.ptr);
		ft_putstr_fd("\nEXIT14", 1);
		if (data->respawn > 0)
			data->game_over_img.ptr = NULL;
	}
}

	void
free_frame(t_data *data, t_frame *frame)
{
		ft_putstr_fd("\nEXIT20", 1);
	mlx_destroy_image(data->mlx, data->frame.NO_img.ptr);
		data->frame.NO_img.ptr = NULL;
	mlx_destroy_image(data->mlx, data->frame.SO_img.ptr);
		data->frame.SO_img.ptr = NULL;
	mlx_destroy_image(data->mlx, data->frame.EA_img.ptr);
		data->frame.EA_img.ptr = NULL;
	mlx_destroy_image(data->mlx, data->frame.WE_img.ptr);
		data->frame.WE_img.ptr = NULL;
	mlx_destroy_image(data->mlx, data->frame.S2_img.ptr);
		data->frame.S2_img.ptr = NULL;
	mlx_destroy_image(data->mlx, data->frame.S3_img.ptr);
		data->frame.S3_img.ptr = NULL;
	if (frame->z_buffer != NULL)
		free(frame->z_buffer);
	frame->z_buffer = NULL; 
}

	void
free_sprites(t_settings *settings, t_frame *frame)
{
		ft_putstr_fd("\nEXIT30", 1);
	if (settings->spr_x != NULL)
		free(settings->spr_x);
	if (settings->spr_y != NULL)
		free(settings->spr_y);
	if (settings->spr_text != NULL)
		free(settings->spr_text);
	if (frame->spr_order != NULL)
		free(frame->spr_order);
	if (frame->spr_dist != NULL)
		free(frame->spr_dist);
	settings->spr_x = NULL;
	settings->spr_y = NULL;
	settings->spr_text = NULL;
	frame->spr_order = NULL;
	frame->spr_dist = NULL;
}

	void
free_settings(t_settings *settings)
{
		ft_putstr_fd("\nEXIT40", 1);
	if (settings->NO_path != NULL)
		free(settings->NO_path);
	if (settings->SO_path != NULL)
		free(settings->SO_path);
	if (settings->WE_path != NULL)
		free(settings->WE_path);
	if (settings->EA_path != NULL)
		free(settings->EA_path);
	if (settings->S2_path != NULL)
		free(settings->S2_path);
	if (settings->S3_path != NULL)
		free(settings->S3_path);
	settings->NO_path = NULL;
	settings->SO_path = NULL;
	settings->WE_path = NULL;
	settings->EA_path = NULL;
	settings->S2_path = NULL;
	settings->S3_path = NULL;
	free_map(settings);
}

	void
free_map(t_settings *settings)
{
	int i;

		ft_putstr_fd("\nEXIT50", 1);
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
