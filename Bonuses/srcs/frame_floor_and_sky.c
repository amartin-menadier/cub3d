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
put_floor_and_sky_pixels(t_data *data, t_img *img, t_int pxl, t_dbl ray_cam)
{
	t_int	cell;
	t_int	img_pxl;
	int		color;
	int		vertical_look;

	vertical_look = sin(data->angle.y) * (data->win.size.y);
	if (pxl.y < data->cam.y + vertical_look)
	{
		img = &data->piclib.sky;
		ray_cam.x = data->cam.x + data->cam.x - ray_cam.x;
		ray_cam.z = data->cam.z + data->cam.z - ray_cam.z;
	}
	else
		img = &data->piclib.flr;
	cell.x = (int)(ray_cam.x);
	cell.z = (int)(ray_cam.z);
	img_pxl.x = (int)(img->size.x * (ray_cam.x - cell.x)) & (img->size.x - 1);
	img_pxl.y = (int)(img->size.y * (ray_cam.z - cell.z)) & (img->size.y - 1);
	color = img_color(img->colors, img_pxl.x, img_pxl.y, img->size);
	put_pixel(&data->win, pxl, color);
}

	double
get_floor_or_sky_depth(t_data *data, int pxl_y)
{
	double	pxl_height;
	double	depth;
	double	cam_height;
	double	ratio;
	double	vertical_look;

	vertical_look = sin(data->angle.y) * (data->win.size.y * 1.0);
	cam_height = data->cam.y + vertical_look;
	pxl_height = 1.0 * pxl_y - cam_height;
	depth = cam_height / pxl_height;
	ratio = (cam_height - data->win.size.y / 2.0) / (data->win.size.y / 2.0);
	depth /= 1.0 + ratio;
	return (depth);
}

	void
draw_floor_and_sky_lign(t_data *data, t_int pxl, t_dbl ray0, t_dbl ray1)
{
	double	depth;
	t_dbl	ray_cam;
	t_dbl	step;

	depth = get_floor_or_sky_depth(data, pxl.y);
	step.x = depth * (ray1.x - ray0.x) / data->win.size.x;
	step.z = depth * (ray1.z - ray0.z) / data->win.size.x;
	ray_cam.x = data->cam.x + depth * ray0.x;
	ray_cam.z = data->cam.z + depth * ray0.z;
	pxl.x = 0;
	while (pxl.x < data->win.size.x)
	{
		put_floor_and_sky_pixels(data, &data->piclib.flr, pxl, ray_cam);
		ray_cam.x += step.x;
		ray_cam.z += step.z;
		pxl.x++;
	}
}

	void
draw_floor_and_sky(t_data *data, t_dbl angle, t_int win_size)
{
	t_int	pxl;
	t_dbl	ray0;
	t_dbl	ray1;

	ray0.x = cos(angle.x) - cos(angle.x - PI / 2);
	ray0.z = sin(angle.x) - sin(angle.x - PI / 2);
	ray1.x = cos(angle.x) + cos(angle.x - PI / 2);
	ray1.z = sin(angle.x) + sin(angle.x - PI / 2);
	pxl.y = 0;
	while (pxl.y < win_size.y)
	{
		draw_floor_and_sky_lign(data, pxl, ray0, ray1);
		pxl.y++;
	}
}
