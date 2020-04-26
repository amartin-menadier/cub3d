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
init_image(t_img *img, int name)
{
	img->ptr = NULL;
	img->path = NULL;
	img->colors = NULL;
	img->name = name;
}

	void
init_piclib(t_piclib *piclib)
{
	init_image(&piclib->ea, EA);
	init_image(&piclib->so, SO);
	init_image(&piclib->we, WE);
	init_image(&piclib->no, NO);
	init_image(&piclib->flr, FLR);
	init_image(&piclib->sky, SKY);
	init_image(&piclib->s2, S2);
	init_image(&piclib->s3, S3);
	init_image(&piclib->avatar, AVATAR);
	init_image(&piclib->skybox, SKYBOX);
	init_image(&piclib->game_over, GAME_OVER);
	init_image(&piclib->mask, MASK);
}

	void
init_settings(t_settings *settings)
{
	settings->win_size.x = 0;
	settings->win_size.y = 0;
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
	if (settings->player_orientation == 'E')
		frame->dir.angle = 0;
	if (settings->player_orientation == 'N')
		frame->dir.angle = PI / 2;
	if (settings->player_orientation == 'W')
		frame->dir.angle = PI;
	if (settings->player_orientation == 'S')
		frame->dir.angle = 3 * PI / 2;
	if (frame->dir.angle == 0)
		frame->plane.angle = 3 * PI / 2;
	else
		frame->plane.angle = frame->dir.angle - PI / 2;
	frame->dir.x = cos(frame->dir.angle);
	frame->dir.y = sin(frame->dir.angle);
	frame->plane.x = cos(frame->plane.angle);
	frame->plane.y = sin(frame->plane.angle);
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
create_skybox_face(t_data *data, t_img skybox, t_img *face, int face_nb)
{
	t_int	size;
	t_int	start;
	t_int	pxl;
	int		color_pxl;

	size.x = skybox.size.x / 4;
	size.y = skybox.size.y / 3;
	if (face->ptr != NULL)
		mlx_destroy_image(data->mlx, face->ptr);
	face->ptr = NULL;
	face->ptr = mlx_new_image(data->mlx, size.x, size.y);
	face->colors = (int*)mlx_get_data_addr(face->ptr, &face->bpp,
			&face->line_length, &face->endian);
	face->size = size;
	start.y = size.y;
	if (face_nb < 4)
		start.x = size.x * face_nb;
	else
		start.x = size.x;
	if (face_nb == FLR)
		start.y += size.y;
	if (face_nb == SKY)
		start.y = 0;
	pxl.x = 0;
	while (pxl.x < size.x)
	{
		pxl.y = 0;
		while (pxl.y < size.y)
		{
			color_pxl = ((pxl.y + start.y) * skybox.size.x + pxl.x + start.x);
			color_pxl = skybox.colors[color_pxl];
			face->colors[pxl.y * size.x + pxl.x] = color_pxl;
			pxl.y++;
		}
		pxl.x++;
	}
}

	void
create_skybox(t_data *data, t_piclib *piclib, t_img *skybox)
{

	if (skybox->size.x / 4 != skybox->size.y / 3)
		close_program(data, "skybox img is not a 4*3 img", "");
	create_skybox_face(data, *skybox, &piclib->ea, EA);
	create_skybox_face(data, *skybox, &piclib->so, SO);
	create_skybox_face(data, *skybox, &piclib->we, WE);
	create_skybox_face(data, *skybox, &piclib->no, NO);
	create_skybox_face(data, *skybox, &piclib->flr, FLR);
	create_skybox_face(data, *skybox, &piclib->sky, SKY);
//	free_image(data, skybox);
//	mlx_destroy_image(data->mlx, skybox.ptr);
//	skybox.ptr = NULL;
}

	void
create_images(t_data *data, t_piclib *piclib)
{
	ft_putstr_fd("\nINIT51", 1);
	ft_putstr_fd("\n--", 1);

	create_img(data, piclib->ea.path, &piclib->ea);
	create_img(data, piclib->so.path, &piclib->so);
	create_img(data, piclib->we.path, &piclib->we);
	create_img(data, piclib->no.path, &piclib->no);
	create_img(data, piclib->flr.path, &piclib->flr); 
	create_img(data, piclib->sky.path, &piclib->sky); 
	create_img(data, piclib->s2.path, &piclib->s2); 
	create_img(data, piclib->s3.path, &piclib->s3); 
	create_img(data, piclib->no.path, &piclib->skybox);
	create_img(data, "./textures/intellolcut.xpm", &piclib->avatar);
	create_img(data, "./textures/gameover.xpm", &piclib->game_over);
	create_img(data, "./textures/civ_mask.xpm", &piclib->mask);
	ft_putstr_fd("\nINIT52", 1);
	ft_putstr_fd("\n--", 1);
	if (data->skybox)
		create_skybox(data, piclib, &piclib->skybox);
	ft_putstr_fd("\nINIT53", 1);
	ft_putstr_fd("\n--", 1);
}

	void
init_frame(t_data *data, t_settings *settings, t_frame *frame)
{
	init_dir_and_plane(settings, frame);
	frame->pos.x = settings->starting_pos.x + 0.5;
	frame->pos.y = settings->starting_pos.y + 0.5;
	settings->map[settings->starting_pos.y][settings->starting_pos.x] = '0';
	if(!(frame->z_buffer = malloc(sizeof(double *) * settings->win_size.x)))
		close_program(data, "Failed allocating z_buffer", "");
	ft_putstr_fd("\nINIT125", 1);
	ft_putstr_fd("\n--", 1);
	create_images(data, &data->piclib);
	ft_putstr_fd("\nINIT126", 1);
	ft_putstr_fd("\n--", 1);
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
//	map->face.ptr = NULL;
	set_life_bar_limits(data, settings, &data->life);
	//	create_img(data, "./textures/intellolcut.xpm", &map->face);
	data->map.done = 0;
}

	void
init_data(t_data *data)
{
	t_int	win_size;
	t_img	*scr;

	if(ft_memcmp(&data->cub_path[ft_strlen(data->cub_path) - 10], "skybox", 6))
		data->skybox = 0;
	else
		data->skybox = 1;
//	data->mod = 0;//pour les tests. A supprimer.
	win_size.x = data->settings.win_size.x;
	win_size.y = data->settings.win_size.y;
	data->window = mlx_new_window(data->mlx, win_size.x, win_size.y, "Cub3D");
	scr = &data->scr;
	scr->ptr = mlx_new_image(data->mlx, data->settings.win_size.x,
			data->settings.win_size.y);
	scr->colors = (int *)mlx_get_data_addr(scr->ptr, &scr->bpp,
			&scr->line_length, &scr->endian);
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
	ft_putstr_fd("\nINIT14", 1);
	ft_putstr_fd("\n--", 1);
//	data->game_over_img.ptr = NULL;
}
