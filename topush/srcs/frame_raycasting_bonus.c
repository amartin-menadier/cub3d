/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:07 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** in set_drawing_limit, odd mods (so mod % 2 is true) are for skyboxes
*/

	int
drawing_limit(t_data *data, double wall_dist, int mod)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		vertical_look;

//	if (data->skybox[0][0])
//		mod++;
	vertical_look = sin(data->angle.y) * (data->win.size.y);
//	if (mod % 2)
//		wall_dist = fmax(data->win.size.x, data->win.size.y) / data->win.size.y;
	line_height = fabs(data->win.size.y / wall_dist);
	draw_start = vertical_look + data->cam.y - line_height / 2;
	draw_end = vertical_look + data->cam.y + line_height / 2;
	if ((mod == 0 || mod == 1) && draw_start < 0)
		return (0);
	else if (mod == 0 || mod == 1)
		return (draw_start);
	else if ((mod == 2 || mod == 3) && draw_end > data->win.size.y)
		return (data->win.size.y);
	else if (mod == 2 || mod == 3)
		return (draw_end);
	else if (mod == 4 || mod == 5)
		return (line_height);
	else
		return (-100000000);
}

	t_dbl
set_ray(t_data *data, t_int win_size)
{
	double	camera_x;
	t_dbl	ray;
	t_dbl	plane;

	camera_x = 2.0 * win_size.x / data->win.size.x - 1;
	if (data->skybox[0][0] < 0)
	{
		ray = rotate_point(data->angle.x - (PI / 3) * camera_x, NULL, NULL);
	}
	else
	{
		plane = rotate_point(data->angle.x - PI / 2, NULL, NULL);
		ray = rotate_point(data->angle.x , NULL, NULL);
		ray.x += plane.x * camera_x;
		ray.z += plane.z * camera_x;
	}
	return(ray);
}
