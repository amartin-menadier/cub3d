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
get_delta_dist(t_data *data, t_dbl ray)
{
	t_dbl	delta_dist;

	if (ray.x == 0)
		delta_dist.z = 0;
	else if (ray.z == 0)
		delta_dist.z = 1;
	else
	//	delta_dist.z = fabs(1 / ray.z);
		delta_dist.z = sqrt(1 + square(ray.x) / square(ray.z));
	if (ray.z == 0)
		delta_dist.x = 0;
	else if (ray.x == 0)
		delta_dist.x = 1;
	else
	//	delta_dist.x = fabs(1 / ray.x);
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
DDA_step(t_dbl ray)
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
	while (data->map[(int)cell.z][(int)cell.x] != WALL)
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
wall_side(t_data *data, t_dbl ray)
{
	t_dbl	side;
	t_dbl	step;

	step = DDA_step(ray);
	side = ray_to_wall(data, ray, step, 1);
	if (!data->skybox[0][0])
		return (side.x);
	else
		return (ray_orientation(ray));
}

	double
perp_wall_dist(t_data *data, t_dbl cam, t_dbl ray)
{
	t_dbl	step;
	t_dbl	wall_cell;
	double	perp_wall_dist;
	double	side;

	step = DDA_step(ray);
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
