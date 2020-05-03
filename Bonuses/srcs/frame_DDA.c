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
		delta_dist.y = 0;
	else if (ray.y == 0)
		delta_dist.y = 1;
	else
		delta_dist.y = fabs(1 / ray.y);
	if (ray.y == 0)
		delta_dist.x = 0;
	else if (ray.x == 0)
		delta_dist.x = 1;
	else
		delta_dist.x = fabs (1 / ray.x);
return (delta_dist);
}

	t_dbl
get_side_dist(t_dbl delta_dist, t_dbl pos, t_dbl ray)
{
	t_dbl	cell;
	t_dbl	side_dist;

	cell.x = (int)pos.x;
	cell.y = (int)pos.y;
	if (ray.x < 0)
		side_dist.x = (pos.x - cell.x) * delta_dist.x;
	else
		side_dist.x = (cell.x + 1.0 - pos.x) * delta_dist.x;
	if (ray.y < 0)
		side_dist.y = (pos.y - cell.y) * delta_dist.y;
	else
		side_dist.y = (cell.y + 1.0 - pos.y) * delta_dist.y;
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
	if (ray.y < 0)
		step.y = -1;
	else
		step.y = 1;
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
	side_dist = get_side_dist(delta_dist, data.set.pos, ray);
	cell.x = (int)data.set.pos.x;
	cell.y = (int)data.set.pos.y;
	while (data.set.map[(int)cell.y][(int)cell.x] != WALL)
	{
		if(side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			cell.x += step.x;
			side.x = (ray.x > 0 ? EA : WE);
		}
		else
		{
			side_dist.y += delta_dist.y;
			cell.y += step.y;
			side.x = (ray.y > 0 ? NO : SO);
		}
	}
	return (mod == 0 ? cell : side);
}

	double
perform_DDA(t_data *data, t_dbl pos, t_dbl ray, int mod)
{
	t_dbl	step;
	t_dbl	hit_wall;
	double	perp_wall_dist;
	t_dbl	side;

	step = get_DDA_step(ray);
	hit_wall = get_hit_wall(*data, ray, step, 0);
	side = get_hit_wall(*data, ray, step, 1);
	if(side.x == EA || side.x == WE)
		perp_wall_dist = (hit_wall.x - pos.x + (1 - step.x) / 2) / ray.x;
	else
		perp_wall_dist = (hit_wall.y - pos.y + (1 - step.y) / 2) / ray.y;
	if (data->skybox)
		perp_wall_dist = 1;
	if (mod == 0)
		return (perp_wall_dist);
	else
		return (side.x);
}
