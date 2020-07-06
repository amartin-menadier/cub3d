/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:07 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
/*
** NB : cam_height = 0 at the top of the screen and  win_height -1 at the bottom
** three steps = some kneeling to gather momentum / jump / gravity to init pos
*/

	void
kneel(t_data *data, int way)
{
	int		kneel_speed;

	kneel_speed = way * data->win.size.y / 20;
	data->cam.y -= kneel_speed;
	if (data->cam.y < data->win.size.y / 4)
		data->cam.y = data->win.size.y / 4;
	if (data->cam.y >= data->win.size.y / 2)
	{
		data->cam.y = data->win.size.y / 2;
		data->current_event = 0;
	}
	data->frame_done = 0;
}

	void
jump(t_data *data, clock_t time_diff)
{
	int		jump_speed;

	jump_speed = data->win.size.y / 15;
	if (time_diff < 2 * CLOCKS_PER_SEC / 8)
		data->cam.y += jump_speed;
	else
		data->cam.y -= jump_speed;
	if (data->cam.y <= data->win.size.y / 2)
	{
		data->cam.y = data->win.size.y / 2;
		data->current_event = 0;
	}
	if (data->cam.y > data->win.size.y)
		data->cam.y = data->win.size.y;
	data->frame_done = 0;
}


