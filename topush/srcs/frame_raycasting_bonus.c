/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_raycasting_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadier <amenadier@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:30:34 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/12 14:46:50 by amenadier        ###   ########.fr       */
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

	vertical_look = sin(data->angle.y) * (data->win.size.y);
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
		ray = rotate_point(data->angle.x, NULL, NULL);
		ray.x += plane.x * camera_x;
		ray.z += plane.z * camera_x;
	}
	return (ray);
}

double
	perp_wall_dist(t_data *data, t_dbl cam, t_dbl ray)
{
	t_dbl	step;
	t_dbl	wall_cell;
	double	perp_wall_dist;
	double	side;

	step = dda_step(ray);
	wall_cell = ray_to_wall(data, ray, step, 0);
	if (data->skybox[0][0])
	{
		wall_cell = get_side_dist(data, cam, ray);
		wall_cell.x += 1.5;
		wall_cell.z += 1.5;
		wall_cell.x = (int)wall_cell.x;
		wall_cell.z = (int)wall_cell.z;
	}
	side = wall_side(data, ray);
	if (side == EA || side == WE)
		perp_wall_dist = (wall_cell.x - cam.x + (1 - step.x) / 2) / ray.x;
	else
		perp_wall_dist = (wall_cell.z - cam.z + (1 - step.z) / 2) / ray.z;
	return (perp_wall_dist);
}
