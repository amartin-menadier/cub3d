/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/12 19:23:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** dda = Digital Differential Analyser
*/

void
	get_perp_wall_dist(t_frame *frame)
{
	if (frame->side == 0)
		frame->perp_wall_dist =
			(frame->map.x - frame->pos.x
			+ (1 - frame->step.x) / 2) / frame->ray.x;
	else
		frame->perp_wall_dist =
			(frame->map.y - frame->pos.y
			+ (1 - frame->step.y) / 2) / frame->ray.y;
}

void
	perform_dda(t_data *data, t_frame *frame)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (frame->side_dist.x < frame->side_dist.y)
		{
			frame->side_dist.x += frame->delta_dist.x;
			frame->map.x += frame->step.x;
			frame->side = 0;
		}
		else
		{
			frame->side_dist.y += frame->delta_dist.y;
			frame->map.y += frame->step.y;
			frame->side = 1;
		}
		if (data->settings.map[(int)frame->map.y][(int)frame->map.x] == '1')
			hit = 1;
	}
	get_perp_wall_dist(frame);
}

void
	get_side_dist(t_frame *frame)
{
	if (frame->ray.x < 0)
		frame->side_dist.x =
			(frame->pos.x - frame->map.x) * frame->delta_dist.x;
	else
		frame->side_dist.x =
			(frame->map.x + 1.0 - frame->pos.x) * frame->delta_dist.x;
	if (frame->ray.y < 0)
		frame->side_dist.y =
			(frame->pos.y - frame->map.y) * frame->delta_dist.y;
	else
		frame->side_dist.y =
			(frame->map.y + 1.0 - frame->pos.y) * frame->delta_dist.y;
}

void
	set_ray(t_data *data, t_frame *frame, int x)
{
	frame->map.x = (int)frame->pos.x;
	frame->map.y = (int)frame->pos.y;
	frame->camera_x = 2 * x / (double)data->settings.win_size.x - 1;
	frame->ray.x = frame->dir.x + frame->plane.x * frame->camera_x;
	frame->ray.y = frame->dir.y + frame->plane.y * frame->camera_x;
	if (frame->ray.y == 0)
		frame->delta_dist.x = 0;
	else
		frame->delta_dist.x = (frame->ray.x == 0) ? 1 : fabs(1 / frame->ray.x);
	if (frame->ray.x == 0)
		frame->delta_dist.y = 0;
	else
		frame->delta_dist.y = (frame->ray.y == 0) ? 1 : fabs(1 / frame->ray.y);
	if (frame->ray.x < 0)
		frame->step.x = -1;
	else
		frame->step.x = 1;
	if (frame->ray.y < 0)
		frame->step.y = -1;
	else
		frame->step.y = 1;
	get_side_dist(frame);
}
