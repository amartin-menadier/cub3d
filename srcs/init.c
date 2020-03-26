/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:30:34 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:19 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_image(t_data *data, t_img *img)
{
	img->ptr = mlx_new_image(data->mlx, data->settings.win_width,
			data->settings.win_height);
	img->colors = (int *)mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	//bpp, line length et endian set automatiquement par mlx. Pas tout compris.
}

void	init_window(t_data *data, int *win_width, int *win_height)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, *win_width, *win_height, "Cub3D");
}

void	init_settings(t_settings *settings)
{
	settings->win_width = 0;
	settings->win_height = 0;
	//recuperer ici la taile de l'ecran et mettre valeur Rx max et Ry max
	settings->NO_path = NULL;
	settings->SO_path = NULL;
	settings->WE_path = NULL;
	settings->EA_path = NULL;
	settings->Sprite_path = NULL;
	settings->Floor_color = -1;
	settings->Ceiling_color = -1;
	settings->map = NULL;
	settings->map_width = 1;
	settings->map_height = 0;
	settings->player_orientation = (char)NULL;
	settings->init_posX = -1;
	settings->init_posY = -1;
	settings->numSprites = 0;
	settings->spritex = NULL;
	settings->spritey = NULL;
	settings->spritetext = NULL;

//	settings->sprite = NULL;

}

void	init_dir_and_plane(t_settings *settings, t_frame *frame)
{
		frame->dirX = 0;
		frame->dirY = -1;
		frame->planeX = 0.7;
		frame->planeY = 0;
	if (settings->player_orientation == 'E')
	{
		frame->dirX = 1;
		frame->dirY = 0;
		frame->planeX = 0;
		frame->planeY = 0.7;
	}
	if (settings->player_orientation == 'S')
	{
		frame->dirX = 0;
		frame->dirY = 1;
		frame->planeX = -0.7;
		frame->planeY = 0;
	}
	if (settings->player_orientation == 'W')
	{
		frame->dirX = -1;
		frame->dirY = 0;
		frame->planeX = 0;
		frame->planeY = -0.7;
	}	
}

void	init_sprites(t_data *data, t_settings *settings, t_frame *frame)
{
	if (!(settings->spritex = malloc(sizeof(double *) * (settings->numSprites))))
		close_program(data, "Couldn't allocate mem for sprite structs", "");
	if (!(settings->spritey = malloc(sizeof(double *) * (settings->numSprites))))
		close_program(data, "Couldn't allocate mem for sprite structs", "");
	if (!(settings->spritetext = malloc(sizeof(char *) * (settings->numSprites))))
		close_program(data, "Couldn't allocate mem for sprite structs", "");
	if(!(frame->Zbuffer = malloc(sizeof(double *) * settings->win_width)))
		close_program(data, "Failed allocating Zbuffer", "");
	if(!(frame->spriteorder = malloc(sizeof(int *) * settings->numSprites)))
		close_program(data, "Failed allocating spriteorder", "");
	if(!(frame->spritedist = malloc(sizeof(double *) * settings->numSprites)))
		close_program(data, "Failed allocating spritedist", "");

	
}

void	init_frame(t_data *data, t_settings *settings, t_frame *frame)
{
	init_dir_and_plane(settings, frame);
	frame->posX = settings->init_posX + 0.5;
	frame->posY = settings->init_posY + 0.5;
	settings->map[settings->init_posY][settings->init_posX] = '0';
	frame->hit = 0;
	frame->sprites_sorted = 0;
//	init_sprite(data, settings, frame);
	get_texture_img(data, settings->NO_path, &frame->NO_img);
	get_texture_img(data, settings->SO_path, &frame->SO_img);
	get_texture_img(data, settings->WE_path, &frame->WE_img);
	get_texture_img(data, settings->EA_path, &frame->EA_img);
	get_texture_img(data, settings->Sprite_path, &frame->Sprite_img);
	(void)data;
}

void	init_data(t_data *data)
{
	init_window(data, &data->settings.win_width, &data->settings.win_height);
//	ft_putstr_fd("\n INIT WINDOW DONE", 1);
	init_image(data, &data->img);
//	ft_putstr_fd("\n INIT IMAGE DONE", 1);
	init_frame(data, &data->settings, &data->frame);
//	ft_putstr_fd("\n INIT FRAME DONE", 1);
}
