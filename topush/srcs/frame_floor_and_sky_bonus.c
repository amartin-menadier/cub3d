/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_floor_and_sky_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/20 17:40:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void
	put_floor_and_sky_pixels(t_data *data, t_int pxl, t_dbl cam, t_dbl ray_cam)
{
	t_dbl	cell;
	t_int	img_pxl;
	int		color;
	int		vertical_look;
	t_img	*img;

	vertical_look = sin(data->angle.y) * (data->win.size.y);
	if (pxl.y >= data->cam.y + vertical_look)
	{
		ray_cam.x = cam.x + cam.x - ray_cam.x;
		img = &data->piclib.flr;
	}
	else
	{
		img = &data->piclib.sky;
		ray_cam.z = -(cam.z + cam.z - ray_cam.z);
	}
	cell.x = floor(ray_cam.x);
	cell.z = floor(ray_cam.z);
	img_pxl.x = (int)(img->size.x * (ray_cam.x - cell.x));
	img_pxl.y = (int)(img->size.y * (ray_cam.z - cell.z));
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
	t_dbl	cam;
	t_dbl	step;

	cam.x = 1.5;
	cam.z = 1.5;
	if (!data->skybox[0][0])
		cam = data->cam;
	depth = get_floor_or_sky_depth(data, pxl.y);
	step.x = depth * (ray1.x - ray0.x) / (1.0 * data->win.size.x);
	step.z = depth * (ray1.z - ray0.z) / (1.0 * data->win.size.x);
	ray_cam.x = cam.x + depth * ray0.x;
	ray_cam.z = cam.z + depth * ray0.z;
	pxl.x = 0;
	while (pxl.x < data->win.size.x)
	{
		put_floor_and_sky_pixels(data, pxl, cam, ray_cam);
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
