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
get_first_dir_and_plane(t_set *set)
{
	double	plane_angle;

	if (set->angle == 0)
		plane_angle = 3 * PI / 2;
	else
		plane_angle = set->angle - PI / 2;
	set->dir.x = cos(set->angle);
	set->dir.y = sin(set->angle);
//	set->plan.x = cos(plane_angle);
//	set->plan.y = sin(plane_angle);
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
	free_image(data, face);
	face->ptr = mlx_new_image(data->mlx, size.x, size.y);
	face->colors = (int*)mlx_get_data_addr(face->ptr, &face->bpp,
			&face->line_length, &face->endian);
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
}

	void
create_piclib(t_data *data, t_piclib *piclib)
{
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
	if (data->skybox)
		create_skybox(data, piclib, &piclib->skybox);
}

	void
set_mlx(t_data *data, t_img *scr, t_int win_size)
{
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, win_size.x, win_size.y, "Cub3D");
	scr->ptr = mlx_new_image(data->mlx, win_size.x, win_size.y);
	scr->colors = (int *)mlx_get_data_addr(scr->ptr, &scr->bpp,
			&scr->line_length, &scr->endian);
}

	void
set_game(t_data *data, t_set *set)
{
	parse_cub_file(data);
	set_mlx(data, &data->scr, data->set.win_size);
	create_piclib(data, &data->piclib);
	if (!(set->z_buffer = malloc(sizeof(double *) * set->win_size.x)))
		close_program(data, "Failed allocating z_buffer while", "set_game");
	get_first_dir_and_plane(set);
}
