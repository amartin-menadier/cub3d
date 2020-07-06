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

	void
init_settings(t_settings *settings)
{
	settings->win_size.x = 0;
	settings->win_size.y = 0;
	settings->NO_path = NULL;
	settings->SO_path = NULL;
	settings->WE_path = NULL;
	settings->EA_path = NULL;
	settings->S_path = NULL;
	settings->floor_color = -1;
	settings->ceiling_color = -1;
	settings->map = NULL;
	settings->map_size.x = 1;
	settings->map_size.y = 0;
	settings->player_orientation = (char)NULL;
	settings->starting_pos.x = -1;
	settings->starting_pos.y = -1;
	settings->spr_count = 0;
	settings->spr_x = NULL;
	settings->spr_y = NULL;
	settings->spr_text = NULL;
	settings->done = 0;
}

	void
init_dir_and_plane(t_settings *settings, t_frame *frame)
{
		frame->dir.x = 0;
		frame->dir.y = -1;
		frame->plane.x = 0.7;
		frame->plane.y = 0;
	if (settings->player_orientation == 'E')
	{
		frame->dir.x = 1;
		frame->dir.y = 0;
		frame->plane.x = 0;
		frame->plane.y = 0.7;
	}
	if (settings->player_orientation == 'S')
	{
		frame->dir.x = 0;
		frame->dir.y = 1;
		frame->plane.x = -0.7;
		frame->plane.y = 0;
	}
	if (settings->player_orientation == 'W')
	{
		frame->dir.x = -1;
		frame->dir.y = 0;
		frame->plane.x = 0;
		frame->plane.y = -0.7;
	}	
}

	void
init_sprites(t_data *data, t_settings *settings, t_frame *frame)
{
	if (!(settings->spr_x = malloc(sizeof(double *) * (settings->spr_count))))
		close_program(data, "Couldn't allocate mem for spr_x", "");
	if (!(settings->spr_y = malloc(sizeof(double *) * (settings->spr_count))))
		close_program(data, "Couldn't allocate mem for spr_y", "");
	if (!(settings->spr_text = malloc(sizeof(char *) * (settings->spr_count))))
		close_program(data, "Couldn't allocate mem for spr_text", "");
	if(!(frame->z_buffer = malloc(sizeof(double *) * settings->win_size.x)))
		close_program(data, "Failed allocating z_buffer", "");
	if(!(frame->spr_order = malloc(sizeof(int *) * settings->spr_count)))
		close_program(data, "Failed allocating spr_order", "");
	if(!(frame->spr_dist = malloc(sizeof(double *) * settings->spr_count)))
		close_program(data, "Failed allocating spr_dist", "");
}

	void
init_frame(t_data *data, t_settings *settings, t_frame *frame)
{
	init_dir_and_plane(settings, frame);
	frame->pos.x = settings->starting_pos.x + 0.5;
	frame->pos.y = settings->starting_pos.y + 0.5;
	settings->map[settings->starting_pos.y][settings->starting_pos.x] = '0';
	frame->spr_sorted = 0;
	create_texture_img(data, settings->NO_path, &frame->NO_img);
	create_texture_img(data, settings->SO_path, &frame->SO_img);
	create_texture_img(data, settings->WE_path, &frame->WE_img);
	create_texture_img(data, settings->EA_path, &frame->EA_img);
	create_texture_img(data, settings->S_path, &frame->S_img);
}

	void
init_data(t_data *data)
{
	t_int	win_size;
	t_img	*img;

	win_size.x = data->settings.win_size.x;
	win_size.y = data->settings.win_size.y;
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, win_size.x, win_size.y, "Cub3D");
	img = &data->img;
	img->ptr = mlx_new_image(data->mlx, data->settings.win_size.x,
			data->settings.win_size.y);
	img->colors = (int *)mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_length, &img->endian);
	img->size.x = data->settings.win_size.x;
	img->size.y = data->settings.win_size.y;
	init_frame(data, &data->settings, &data->frame);
}
