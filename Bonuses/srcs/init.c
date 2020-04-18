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
	settings->S2_path = NULL;
	settings->S3_path = NULL;
	settings->flr_path = NULL;
	settings->clg_path = NULL;
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
	if (!(settings->spr_text = malloc(sizeof(char *) 
		* (settings->spr_count + 1))))
		close_program(data, "Couldn't allocate mem for spr_text", "");
		settings->spr_text[settings->spr_count] = '\0';
	if(!(frame->spr_order = malloc(sizeof(int *) * settings->spr_count)))
		close_program(data, "Failed allocating spr_order", "");
	if(!(frame->spr_dist = malloc(sizeof(double *) * settings->spr_count)))
		close_program(data, "Failed allocating spr_dist", "");
}

	void
init_frame(t_data *data, t_settings *settings, t_frame *frame)
{
		ft_putstr_fd("\nINIT21", 1);
		ft_putstr_fd("\n--", 1);
	init_dir_and_plane(settings, frame);
	frame->pos.x = settings->starting_pos.x + 0.5;
	frame->pos.y = settings->starting_pos.y + 0.5;
	settings->map[settings->starting_pos.y][settings->starting_pos.x] = '0';
		ft_putstr_fd("\nINIT22", 1);
		ft_putstr_fd("\n--", 1);
	if(!(frame->z_buffer = malloc(sizeof(double *) * settings->win_size.x)))
		close_program(data, "Failed allocating z_buffer", "");
		ft_putstr_fd("\nINIT23", 1);
		ft_putstr_fd("\n--", 1);
	create_img(data, settings->NO_path, &frame->NO_img);
		ft_putstr_fd("\nINIT24", 1);
		ft_putstr_fd("\n--", 1);
	create_img(data, settings->SO_path, &frame->SO_img);
		ft_putstr_fd("\nINIT24", 1);
		ft_putstr_fd("\n--", 1);
	create_img(data, settings->WE_path, &frame->WE_img);
		ft_putstr_fd("\nINIT24", 1);
		ft_putstr_fd("\n--", 1);
	create_img(data, settings->EA_path, &frame->EA_img);
		ft_putstr_fd("\nINIT25", 1);
		ft_putstr_fd("\n--", 1);
	create_img(data, settings->S2_path, &frame->S2_img);
		ft_putstr_fd("\nINIT25", 1);
		ft_putstr_fd("\n--", 1);
	create_img(data, settings->S3_path, &frame->S3_img);
		ft_putstr_fd("\nINIT25", 1);
		ft_putstr_fd("\n--", 1);
	create_img(data, settings->flr_path, &data->floor.flr_img);
		ft_putstr_fd("\nINIT26", 1);
		ft_putstr_fd("\n--", 1);
	create_img(data, settings->clg_path, &data->floor.clg_img);
	frame->done = 0;
}
	void
init_minimap(t_data *data, t_settings *settings, t_minimap *map)
{
	if ((map->size = (int)((double)settings->win_size.y / 3.0))
		> ((int)(double)settings->win_size.x / 4.0))
		map->size = (int)((double)settings->win_size.x / 4.0);
	map->case_size = map->size / MINIMAP_SIZE;
	if (!((map->size = MINIMAP_SIZE * map->case_size) % 2))
		map->size++;
	map->margin = map->case_size / 8;
	map->draw_start.x = map->margin;
	map->draw_end.x = map->draw_start.x + map->size;
	map->draw_start.y = map->margin;
	map->draw_end.y = map->draw_start.y + map->size;
	map->radius = (double)map->size / 2;
	map->center.x = map->draw_start.x + map->radius;
	map->center.y = map->draw_start.y + map->radius;
	map->step_in_case = 1.0000000 / map->case_size;
	map->face.ptr = NULL;
	set_life_bar_limits(data, settings, &data->life);
//	create_img(data, "./textures/intellolcut.xpm", &map->face);
	data->map.done = 0;
}

	void
init_data(t_data *data)
{
	t_int	win_size;
	t_img	*img;

	win_size.x = data->settings.win_size.x;
	win_size.y = data->settings.win_size.y;
	data->window = mlx_new_window(data->mlx, win_size.x, win_size.y, "Cub3D");
	img = &data->img;
	img->ptr = mlx_new_image(data->mlx, data->settings.win_size.x,
			data->settings.win_size.y);
	img->colors = (int *)mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_length, &img->endian);
		ft_putstr_fd("\nINIT11", 1);
		ft_putstr_fd("\n--", 1);
//	img->size.x = data->settings.win_size.x;
//	img->size.y = data->settings.win_size.y;
	data->life.value = 100;
	data->respawn = 0;
		ft_putstr_fd("\nINIT12", 1);
		ft_putstr_fd("\n--", 1);
	init_frame(data, &data->settings, &data->frame);
		ft_putstr_fd("\nINIT13", 1);
		ft_putstr_fd("\n--", 1);
	init_minimap(data, &data->settings, &data->map);
	data->game_over_img.ptr = NULL;
}
