/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_dda_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/20 17:37:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

/*
** DDA = Digital Differential Analyser
*/

t_dbl
	get_delta_dist(t_data *data, t_dbl ray)
{
	t_dbl	delta_dist;

	if (ray.x == 0)
		delta_dist.z = 0;
	else if (ray.z == 0)
		delta_dist.z = 1;
	else
		delta_dist.z = sqrt(1 + square(ray.x) / square(ray.z));
	if (ray.z == 0)
		delta_dist.x = 0;
	else if (ray.x == 0)
		delta_dist.x = 1;
	else
		delta_dist.x = sqrt(1 + square(ray.z) / square(ray.x));
	if (ray.x < 0 && data->skybox[0][0])
		delta_dist.x = -delta_dist.x;
	if (ray.z < 0 && data->skybox[0][0])
		delta_dist.z = -delta_dist.z;
	return (delta_dist);
}

t_dbl
	get_side_dist(t_data *data, t_dbl cam, t_dbl ray)
{
	t_dbl	cell;
	t_dbl	side_dist;
	t_dbl	delta_dist;

	cell.x = (int)cam.x;
	cell.z = (int)cam.z;
	delta_dist = get_delta_dist(data, ray);
	if (ray.x < 0)
		side_dist.x = (cam.x - cell.x) * delta_dist.x;
	else
		side_dist.x = (cell.x + 1.0 - cam.x) * delta_dist.x;
	if (ray.z < 0)
		side_dist.z = (cam.z - cell.z) * delta_dist.z;
	else
		side_dist.z = (cell.z + 1.0 - cam.z) * delta_dist.z;
	return (side_dist);
}

t_dbl
	dda_step(t_dbl ray)
{
	t_dbl	step;

	if (ray.x < 0)
		step.x = -1;
	else
		step.x = 1;
	if (ray.z < 0)
		step.z = -1;
	else
		step.z = 1;
	return (step);
}

t_dbl
	ray_to_wall(t_data *data, t_dbl ray, t_dbl step, int mod)
{
	t_dbl	cell;
	t_dbl	delta_dist;
	t_dbl	side_dist;
	t_dbl	side;

	delta_dist = get_delta_dist(data, ray);
	side_dist = get_side_dist(data, data->cam, ray);
	cell.x = (int)data->cam.x;
	cell.z = (int)data->cam.z;
	while (!is_wall(data->map[(int)cell.z][(int)cell.x]))
	{
		if (side_dist.x < side_dist.z)
		{
			side_dist.x += delta_dist.x;
			cell.x += step.x;
			side.x = (ray.x > 0 ? EA : WE);
		}
		else
		{
			side_dist.z += delta_dist.z;
			cell.z += step.z;
			side.x = (ray.z > 0 ? NO : SO);
		}
	}
	return (mod == 0 ? cell : side);
}

double
	wall_side(t_data *data, t_dbl ray)
{
	t_dbl	side;
	t_dbl	step;

	step = dda_step(ray);
	side = ray_to_wall(data, ray, step, 1);
	if (!data->skybox[0][0])
		return (side.x);
	else
		return (ray_orientation(ray));
}
