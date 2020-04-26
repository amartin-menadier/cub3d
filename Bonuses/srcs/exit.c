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
	mlx_destroy_image(data->mlx, data->scr.ptr);
		data->scr.ptr = NULL;
		ft_putstr_fd("\nEXIT13", 1);
		ft_putstr_fd("\n--", 1);

	mlx_destroy_window(data->mlx, data->window);
	ft_putstr_fd("\n_END_OF_PROGRAM_\n", 1);
	//	system("sudo leaks Cub3D"); //a supprimer
	exit(0);
	return (0);
}

	void
free_image(t_data *data, t_img *img, int mod)
{
	ft_putstr_fd("\nEXIT100  ", 1);
	ft_putstr_fd("\n--", 1);
//	if (img->colors != NULL)
//		free(img->colors);
//	img->colors = NULL;
	ft_putstr_fd("\n--", 1);
	if (mod)
	{
	if (img->path != NULL)
		free(img->path);
	img->path = NULL;
	}
	if (img->ptr != NULL)
		mlx_destroy_image(data->mlx, img->ptr);
	img->ptr = NULL;
		/* a voir si c'est pertinent
		if (data->respawn > 0)
			mlx_destroy_image(data->mlx, data->game_over_img.ptr);
		if (data->respawn > 0)
			data->game_over_img.ptr = NULL;
			*/
	
}

	void
free_piclib(t_data *data, t_piclib *lib)
{
		ft_putstr_fd("\nEXIT20", 1);
	free_image(data, &lib->ea, 1);
	free_image(data, &lib->so, 1);
	free_image(data, &lib->we, 1);
	free_image(data, &lib->no, 1);
	free_image(data, &lib->flr, 1);
	free_image(data, &lib->sky, 1);
	free_image(data, &lib->s2, 1);
	free_image(data, &lib->s3, 1);
	free_image(data, &lib->avatar, 1);
	free_image(data, &lib->skybox, 1);
	free_image(data, &lib->game_over, 1);
	free_image(data, &lib->mask, 1);
}

	void
free_all(t_data *data)
{
		ft_putstr_fd("\nEXIT10", 1);
	free_settings(&data->settings);
	free_piclib(data, &data->piclib);
	if(data->settings.done)
	{
		free_frame(data, &data->frame);
		free_sprites(&data->settings, &data->frame);
	}
}

	void
free_frame(t_data *data, t_frame *frame)
{
	(void)data;
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
