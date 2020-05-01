/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 12:15:52 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	void
put_floor_and_sky_pixels(t_data *data, t_img img, t_int scr, t_dbl ray_pos)
{
	t_int	cell;
	t_int	img_pxl;
	int		color;

	cell.x = (int)(ray_pos.x);
	cell.y = (int)(ray_pos.y);
	img_pxl.x = (int)(img.size.x * (ray_pos.x - cell.x)) & (img.size.x - 1);
	img_pxl.y = (int)(img.size.y * (ray_pos.y - cell.y)) & (img.size.y - 1);
	color = get_img_color(img, img_pxl.x, img_pxl.y, img.size);
	put_pixel(&data->scr, scr, color);
	img = data->piclib.sky;
	color = get_img_color(img, img_pxl.x, img_pxl.y, img.size);
	scr.y = data->set.win_size.y - scr.y - 1;
	put_pixel(&data->scr, scr, color);
	scr.y = data->set.win_size.y - scr.y - 1;
}

	double
get_floor_or_sky_depth(int win_size_y, int scr_y)
{
	float	cam_height;
	float	pxl_height;
	double	depth;

	cam_height = 0.5 * win_size_y;
	pxl_height = scr_y - win_size_y / 2;
	depth = cam_height / pxl_height;
	return (depth);
}

	void
draw_floor_and_sky_lign(t_data *data, t_int scr, t_dbl ray0, t_dbl ray1)
{
	double	depth;
	t_dbl	ray_pos;
	t_dbl	step;

	depth = get_floor_or_sky_depth(data->set.win_size.y, scr.y);
	step.x = depth * (ray1.x - ray0.x) / data->set.win_size.x;
	step.y = depth * (ray1.y - ray0.y) / data->set.win_size.x;
	ray_pos.x = data->set.pos.x + depth * ray0.x;
	ray_pos.y = data->set.pos.y + depth * ray0.y;
	scr.x = 0;
	while (scr.x < data->set.win_size.x)
	{
		put_floor_and_sky_pixels(data, data->piclib.flr, scr, ray_pos);
		ray_pos.x += step.x;
		ray_pos.y += step.y;
		scr.x++;
	}
}

	void
draw_floor_and_sky(t_data *data, double angle, t_int win_size)
{
	t_int	scr;
	t_dbl	ray0;
	t_dbl	ray1;

	ray0.x = cos(angle) - cos(angle - PI / 2);
	ray0.y = sin(angle) - sin(angle - PI / 2);
	ray1.x = cos(angle) + cos(angle - PI / 2);
	ray1.y = sin(angle) + sin(angle - PI / 2);
	scr.y = 0;
	while (scr.y < win_size.y)
	{
		draw_floor_and_sky_lign(data, scr, ray0, ray1);
		scr.y++;
	}

}
