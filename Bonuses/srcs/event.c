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

#include "cub3d.h"

	int
press_key(int key, t_data *data)
{
	if (data->life <= 0)
		return (game_over_answer(data, key));
	if (data->current_event == JUMP)
		return (0);
	if (key == P)
		create_bmp(data, &data->win, "./screenshots/screenshot");
	if (key == ESC)
		close_program(data, "\nSee you next time ! ", "\\o/\n");
	if (LOOK(key))
		look(&data->angle, key);
	if (MOVE(key))
		move(data, data->map, &data->cam, key);
	if(data->map[(int)data->cam.z][(int)data->cam.x] > WALL)
		sprite_hit(data);
	data->frame_done = 0;
	return(key);
}

	int	
red_cross(t_data *data)
{
	close_program(data, "\nSee you next time ! ", "\\o/\n");
	return (0);
}

	int
release_key(int key, t_data *data)
{
	if (key == V && data->current_event != JUMP)
		data->current_event = UNKNEEL;
	return (key);
}

	void
deal_current_event(t_data *data)
{
	clock_t time_diff;

	time_diff = clock () - data->time;
	if (data->current_event == KNEEL)
		kneel(data, 1);
	else if (data->current_event == UNKNEEL)
		kneel(data, -1);
	else if (data->current_event == JUMP && time_diff <= 2 * CLOCKS_PER_SEC / 4)
		jump(data, time_diff);
	else if (data->current_event == JUMP)
		data->current_event = 0;
	else
		data->cam.y = data->win.size.y / 2;
}

	void
hook_event(t_data *data)
{
	deal_current_event(data);
	mlx_hook(data->window, 2, 1L << 0, press_key, data);
	mlx_hook(data->window, 3, 1L << 1, release_key, data);
	mlx_hook(data->window, 17, 1L << 17, red_cross, data);
}
