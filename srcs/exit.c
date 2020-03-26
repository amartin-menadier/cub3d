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
	free_settings(&data->settings);
//	ft_putstr_fd("\nSETTINGS FREED", 1);
	free_frame(data, &data->frame);
//	ft_putstr_fd("\nFRAME FREED", 1);
	mlx_destroy_image(data->mlx, data->img.ptr);
	mlx_destroy_window(data->mlx, data->win);
	ft_putstr_fd("\nEND_OF_PROGRAM\n", 1);//a supprimer
//	system("sudo leaks Cub3D"); //a supprimer
	exit(0);
	return (0);
}

void	free_frame(t_data *data, t_frame *frame)
{
//rajouter des if non NULL ?
	mlx_destroy_image(data->mlx, data->frame.NO_img.ptr);
	mlx_destroy_image(data->mlx, data->frame.SO_img.ptr);
	mlx_destroy_image(data->mlx, data->frame.EA_img.ptr);
	mlx_destroy_image(data->mlx, data->frame.WE_img.ptr);
	mlx_destroy_image(data->mlx, data->frame.Sprite_img.ptr);
	free(frame->Zbuffer);
	frame->Zbuffer = NULL; 
	free(frame->spriteorder);
	frame->spriteorder = NULL;
	free(frame->spritedist);
	frame->spritedist = NULL;
}

void	free_sprites(t_settings *settings)
{
	if (settings->spritex != NULL)
		free(settings->spritex);
	if (settings->spritey != NULL)
		free(settings->spritey);
	if (settings->spritetext != NULL)
		free(settings->spritetext);
	settings->spritex = NULL;
	settings->spritey = NULL;
	settings->spritetext = NULL;

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
	free_sprites(settings);
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
