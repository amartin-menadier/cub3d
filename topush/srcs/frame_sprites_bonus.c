/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_sprites_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/20 17:40:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int
	get_sprite_y(t_data *data, t_img *img, int pxl_y, int height_on_win)
{
	int		spr_pxl_y;
	int		spr_height;
	int		step;
	double	vertical_look;

	vertical_look = sin(data->angle.y) * (data->win.size.y);
	spr_height = img->size.y;
	step = pxl_y - data->cam.y - vertical_look + height_on_win / 2;
	spr_pxl_y = ((step * spr_height) / height_on_win);
	return (spr_pxl_y);
}

int
	get_sprite_x(t_img *img, int pxl_x, int width_on_win, double center_x)
{
	int		spr_pxl_x;
	int		spr_width;

	spr_width = img->size.x;
	spr_pxl_x = (int)(256 * fabs(pxl_x - (-width_on_win / 2
					+ center_x)) * spr_width / width_on_win) / 256;
	return (spr_pxl_x);
}

t_dbl
	transform_sprite(double angle, t_dbl dist, double spr_y)
{
	t_dbl	transform;
	t_dbl	dir;
	t_dbl	plane;
	double	inv_det;

	dir = rotate_point(angle, NULL, NULL);
	plane = rotate_point(angle - PI / 2, NULL, NULL);
	inv_det = 1.0 / (plane.x * dir.z - dir.x * plane.z);
	transform.x = inv_det * (dir.z * dist.x - dir.x * dist.z);
	transform.y = spr_y;
	transform.z = inv_det * (plane.x * dist.z - plane.z * dist.x);
	return (transform);
}

/*
** transform.z stands for depth
*/

void
	draw_one_sprite(t_data *data, t_img *img, t_dbl transform, t_int draw_end)
{
	t_int			pxl;
	t_int			spr_pxl;
	unsigned int	color;
	t_int			size_on_win;
	double			center_x;

	size_on_win.x = (int)sprite_data(data, transform, data->win.size, WIDTH);
	size_on_win.y = (int)sprite_data(data, transform, data->win.size, HEIGHT);
	pxl.x = (int)sprite_data(data, transform, data->win.size, DRAW_START_X);
	center_x = sprite_data(data, transform, data->win.size, CENTER_X);
	while (pxl.x < draw_end.x)
	{
		pxl.y = (int)sprite_data(data, transform, data->win.size, DRAW_START_Y);
		spr_pxl.x = get_sprite_x(img, pxl.x, size_on_win.x, center_x);
		while (pxl.y < draw_end.y && transform.z < data->z_buffer[pxl.x])
		{
			spr_pxl.y = get_sprite_y(data, img, pxl.y, size_on_win.y);
			color = img_color(img->colors, spr_pxl.x, spr_pxl.y, img->size);
			if (color != BLACK)
				put_pixel(&data->win, pxl, color);
			pxl.y++;
		}
		pxl.x++;
	}
}

void
	draw_sprites(t_data *data, t_piclib *lib)
{
	int		i;
	t_img	*img;
	t_dbl	dist;
	t_dbl	trans;
	t_int	draw_end;

	sort_sprites(data->cam, data->spr, data->spr_count);
	i = 0;
	while (i < data->spr_count)
	{
		if (!(sprite_player_same_cell(data, i)))
		{
			img = get_sprite_image(data->map, data->spr[i], lib);
			dist.x = data->spr[i].x - data->cam.x;
			dist.z = data->spr[i].z - data->cam.z;
			trans = transform_sprite(data->angle.x, dist, data->spr[i].y);
			draw_end.x = sprite_data(data, trans, data->win.size, DRAW_END_X);
			draw_end.y = sprite_data(data, trans, data->win.size, DRAW_END_Y);
			if (trans.z > 0)
				draw_one_sprite(data, img, trans, draw_end);
		}
		i++;
	}
}
