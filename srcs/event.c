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

	void
look_left(t_frame *frame)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rotSpeed = 0.18;
	double	*PlaneX;
	double	*PlaneY;

	PlaneX = &frame->planeX;
	PlaneY = &frame->planeY;
	oldDirX = frame->dirX;
	frame->dirX = oldDirX * cos(-rotSpeed) - frame->dirY * sin(-rotSpeed);
	frame->dirY = oldDirX * sin(-rotSpeed) + frame->dirY * cos(-rotSpeed);
	oldPlaneX = frame->planeX;
	*PlaneX = oldPlaneX * cos(-rotSpeed) - frame->planeY * sin(-rotSpeed);
	*PlaneY = oldPlaneX * sin(-rotSpeed) + frame->planeY * cos(-rotSpeed);
}

	void
look_right(t_frame *frame)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rotSpeed = 0.18;
	double	*PlaneX;
	double	*PlaneY;

	PlaneX = &frame->planeX;
	PlaneY = &frame->planeY;
	oldDirX = frame->dirX;
	frame->dirX = frame->dirX * cos(rotSpeed) - frame->dirY * sin(rotSpeed);
	frame->dirY = oldDirX * sin(rotSpeed) + frame->dirY * cos(rotSpeed);
	oldPlaneX = frame->planeX;
	*PlaneX = frame->planeX * cos(rotSpeed) - frame->planeY * sin(rotSpeed);
	*PlaneY = oldPlaneX * sin(rotSpeed) + frame->planeY * cos(rotSpeed);
}

	int
press_key(int key, t_data *data)
{
	if (key == KEY_P)
		create_bmp(data, &data->img, "./screenshots/screenshot");
	if (key == KEY_ESC)
		close_program(data, "\nEverything went well ! ", "\\o/\n");
	if (key == KEY_LEFT)
		look_left(&data->frame);
	if (key == KEY_RIGHT)
		look_right(&data->frame);
	if (key == KEY_Z)
		move_forward(&data->frame, data->settings.map);
	if (key == KEY_S)
		move_backward(&data->frame, data->settings.map);
	if (key == KEY_D)
		move_right(&data->frame, data->settings.map);
	if (key == KEY_Q)
		move_left(&data->frame, data->settings.map);
	data->frame.sprites_sorted = 0;
	return(key);
}

	int	
red_cross(t_data *data)
{
	close_program(data, "\nEverything went well ! ", "\\o/\n");
	return (0);
}

	void
hook_event(t_data *data)
{
	mlx_hook(data->window, 2, 1L << 0, press_key, data);
	mlx_hook(data->window, 17, 1L << 17, red_cross, data);
	return ;
}
