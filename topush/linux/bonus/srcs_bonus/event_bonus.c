/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/15 14:10:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int
	press_key(int key, t_data *data)
{
	if (key == ESC)
		close_program(data, "\nSee you next time ! ", "\\o/\n");
	if (data->life == -9999)
		return (victory(data, data->win.size, &data->piclib.victory));
	if (data->life <= 0)
		return (game_over_answer(data, key));
	if (!ft_strncmp(data->cub_path, "./cub/bonus/42_start1.cub", 25)
		|| !ft_strncmp(data->cub_path, "./cub/bonus/skybox.cub", 22))
		replace_cub_path(data, "./cub/bonus/42_1.cub");
	if (data->current_event == JUMP)
		return (0);
	if (key == P)
		create_bmp(data, &data->win, "./screenshots/screenshot");
	if (is_look(key))
		look(&data->angle, key);
	if (is_move(key))
		move(data, data->map, &data->cam, key);
	if (data->map[(int)data->cam.z][(int)data->cam.x] > CLASSIC_WALL)
		sprite_hit(data);
	data->frame_done = 0;
	return (key);
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

	if (!data->current_event)
	{
		data->cam.y = data->win.size.y / 2;
		return ;
	}
	else
		time_diff = clock() - data->time;
	if (data->current_event == KNEEL)
		kneel(data, 1);
	else if (data->current_event == UNKNEEL)
		kneel(data, -1);
	else if (data->current_event == JUMP && time_diff <= 2 * CLOCKS_PER_SEC / 4)
		jump(data, time_diff);
	else if (data->current_event == JUMP)
		data->current_event = 0;
}

void
	hook_event(t_data *data)
{
	deal_current_event(data);
	mlx_hook(data->window, 2, 1L << 0, press_key, data);
	mlx_hook(data->window, 3, 1L << 1, release_key, data);
	mlx_hook(data->window, 0, 1L << 17, red_cross, data);
	return ;
}
