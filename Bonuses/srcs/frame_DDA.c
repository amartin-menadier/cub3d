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

#include "cub3d.h"

/*
 ** DDA = Digital Differential Analyser
 */

	t_dbl
get_delta_dist(t_dbl ray)
{
	t_dbl	delta_dist;

	if (ray.x == 0)
		delta_dist.z = 0;
	else if (ray.z == 0)
		delta_dist.z = 1;
	else
		delta_dist.z = fabs(1 / ray.z);
	if (ray.z == 0)
		delta_dist.x = 0;
	else if (ray.x == 0)
		delta_dist.x = 1;
	else
		delta_dist.x = fabs (1 / ray.x);
return (delta_dist);
}

	t_dbl
get_side_dist(t_dbl delta_dist, t_dbl cam, t_dbl ray)
{
	t_dbl	cell;
	t_dbl	side_dist;

	cell.x = (int)cam.x;
	cell.z = (int)cam.z;
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
get_DDA_step(t_dbl ray)
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
get_hit_wall(t_data data, t_dbl ray, t_dbl step, int mod)
{
	t_dbl	cell;
	t_dbl	delta_dist;
	t_dbl	side_dist;
	t_dbl	side;

	delta_dist = get_delta_dist(ray);
	side_dist = get_side_dist(delta_dist, data.cam, ray);
	cell.x = (int)data.cam.x;
	cell.z = (int)data.cam.z;
	while (data.map[(int)cell.z][(int)cell.x] != WALL)
	{
		if(side_dist.x < side_dist.z)
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
perform_DDA(t_data *data, t_dbl cam, t_dbl ray, int mod)
{
	t_dbl	step;
	t_dbl	hit_wall;
	double	perp_wall_dist;
	t_dbl	side;

	step = get_DDA_step(ray);
	hit_wall = get_hit_wall(*data, ray, step, 0);
	side = get_hit_wall(*data, ray, step, 1);
	if(side.x == EA || side.x == WE)
		perp_wall_dist = (hit_wall.x - cam.x + (1 - step.x) / 2) / ray.x;
	else
		perp_wall_dist = (hit_wall.z - cam.z + (1 - step.z) / 2) / ray.z;
	if (data->skybox)
		perp_wall_dist = 1;
	if (mod == 0)
		return (perp_wall_dist);
	else
		return (side.x);
}
