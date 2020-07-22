/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_skybox_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/20 17:40:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_int
	skybox_face_first_pixel(t_img *face, int face_nb)
{
	t_int	start;

	start.y = face->size.y;
	if (face_nb < 4)
		start.x = face->size.x * face_nb;
	else
		start.x = face->size.x;
	if (face_nb == FLR)
		start.y += face->size.y;
	if (face_nb == SKY)
		start.y = 0;
	return (start);
}

void
	create_skybox_face(t_data *data, t_img skybox, t_img *face, int face_nb)
{
	t_int	start;
	t_int	pxl;
	int		color_pxl;

	free_image(data, face);
	face->size.x = skybox.size.x / 4;
	face->size.y = skybox.size.y / 3;
	face->ptr = mlx_new_image(data->mlx, face->size.x, face->size.y);
	face->colors = (int*)mlx_get_data_addr(face->ptr, &face->bpp,
			&face->line_length, &face->endian);
	start = skybox_face_first_pixel(face, face_nb);
	pxl.x = 0;
	while (pxl.x < face->size.x)
	{
		pxl.y = 0;
		while (pxl.y < face->size.y)
		{
			color_pxl = ((pxl.y + start.y) * skybox.size.x + pxl.x + start.x);
			color_pxl = skybox.colors[color_pxl];
			face->colors[pxl.y * face->size.x + pxl.x] = color_pxl;
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
