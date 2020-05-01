/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:07 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	void
sort_sprites(t_dbl pos, t_dbl *spr, int spr_count)
{
	int		i;
	int		j;
	int		k;
	t_dbl	tmp_spr;

	i = 0;
	while (i < spr_count - 1)
	{
		k = 0;
		j = i;
		while (++j < spr_count)
		{
		if ((dist(pos, spr[i]) < dist(pos, spr[j]) && i < j)
				|| (dist(pos, spr[i]) > dist(pos, spr[j]) && i > j))
			{
				k++;
				tmp_spr = spr[i];
				spr[i] = spr[j];
				spr[j] = tmp_spr;
			}
		}
		i = (k == 0) ? i + 1 : i;
	}
}

	t_dbl
transform_sprite(double angle, t_dbl dist)
{
	t_dbl	transform;
	t_dbl	dir;
	t_dbl	plane;
	double	inv_det;

	dir = rotate_point(angle, NULL, NULL);
	plane = rotate_point(angle - PI / 2, NULL, NULL);
	inv_det = 1.0 / (plane.x * dir.y - dir.x * plane.y);
	transform.x = inv_det * (dir.y * dist.x - dir.x * dist.y);
	transform.y = inv_det * (plane.x * dist.y - plane.y * dist.x);
	return (transform);
}

	double
sprite_data(t_set *set, t_dbl transform, int mod)
{
	double	center_x;
	t_int	size_on_scr;
	t_int	win;
	int		ret;

	win = set->win_size;
	ret = 0;
	center_x = ((set->win_size.x / 2) * (1 + transform.x / transform.y));
	size_on_scr.y = abs((int)(win.y / (transform.y)));
	size_on_scr.x = abs((int)(win.x / (2 * transform.y)));
	if (mod == CENTER_X)
		return (center_x);
	if (mod == WIDTH)
		return (size_on_scr.x);
	if (mod == HEIGHT)
		return (size_on_scr.y);
	if (mod == DRAW_START_X)
		return ((ret = center_x - size_on_scr.x / 2) < 0 ? 0 : ret);
	if (mod == DRAW_END_X)
		return ((ret = size_on_scr.x / 2 + center_x) >= win.x ? win.x : ret);
	if (mod == DRAW_START_Y)
		return ((ret = win.y / 2 - size_on_scr.y / 2) < 0 ? 0 : ret);
	if (mod == DRAW_END_Y)
		return ((ret = win.y / 2 + size_on_scr.y / 2) >= win.y ? win.y : ret);
	return (-9999);
}

/*
 * transform.y stands for depth
 */
	void
draw_one_sprite(t_data *data, t_img img, t_dbl transform, t_int draw_end)
{
	t_int	scr;
	t_int	spr_pxl;
	int		color;
	t_int	size_on_scr;
	double	center_x;

	size_on_scr.x = (int)sprite_data(&data->set, transform, WIDTH);
	size_on_scr.y = (int)sprite_data(&data->set, transform, HEIGHT);
	scr.x = (int)sprite_data(&data->set, transform, DRAW_START_X);
	center_x = sprite_data(&data->set, transform, CENTER_X);
	while (scr.x < draw_end.x)
	{
		scr.y = (int)sprite_data(&data->set, transform, DRAW_START_Y);
		spr_pxl.x = get_sprite_x(img, scr.x, size_on_scr.x, center_x);
		while (scr.y < draw_end.y && transform.y < data->set.z_buffer[scr.x])
		{
			spr_pxl.y = get_sprite_y(data, img, scr.y, size_on_scr.y);
			color = get_img_color(img, spr_pxl.x, spr_pxl.y, img.size);
			if (color != BLACK)
				put_pixel(&data->scr, scr, color);
			scr.y++;
		}
		scr.x++;
	}
}

	void
draw_sprites(t_data *data, t_piclib lib, t_set *set)
{
	int		i;
	t_img	img;
	t_dbl	dist;
	t_dbl	transform;
	t_int	draw_end;

	sort_sprites(set->pos, set->spr, set->spr_count);
	i = 0;
	while (i < set->spr_count)
	{
		if (!(sprite_player_same_cell(set, i)))
		{
			img = get_sprite_image(set->map, set->spr[i], lib);
			dist.x = set->spr[i].x - set->pos.x;
			dist.y = set->spr[i].y - set->pos.y;
			transform = transform_sprite(set->angle, dist);
			draw_end.x = (int)sprite_data(&data->set, transform, DRAW_END_X);
			draw_end.y = (int)sprite_data(&data->set, transform, DRAW_END_Y);
			if (transform.y > 0)
				draw_one_sprite(data, img, transform, draw_end);
		}
		i++;
	}

}
