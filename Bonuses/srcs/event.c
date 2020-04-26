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
get_dir_and_plane(t_frame *frame)
{
	if (frame->dir.angle < (PI / 2))
		frame->plane.angle = frame->dir.angle + 3 * PI / 2;
	else
		frame->plane.angle = frame->dir.angle - PI / 2;
	frame->dir.x = cos(frame->dir.angle);
	frame->dir.y = sin(frame->dir.angle);
	frame->plane.x = cos(frame->plane.angle);
	frame->plane.y = sin(frame->plane.angle);
}


	void
look_left(t_frame *frame)
{
	frame->dir.angle += ROT_SPEED;
	if (frame->dir.angle >= (2 * PI))
		frame->dir.angle -= (2 * PI);
	get_dir_and_plane(frame);
}

	void
look_right(t_frame *frame)
{
	frame->dir.angle -= ROT_SPEED;
	if (frame->dir.angle < 0)
		frame->dir.angle += (2 * PI);
	get_dir_and_plane(frame);
	/*
	double	old_dir_x;
	double	old_plane_x;
//	double	angle;
	t_dbl	*plane;

	plane = &frame->plane;
	old_dir_x = frame->dir.x;
	frame->dir.x = old_dir_x * cos(-ROT_SPEED) + frame->dir.y * sin(-ROT_SPEED);
	frame->dir.y = -old_dir_x * sin(-ROT_SPEED) + frame->dir.y * cos(-ROT_SPEED);
	if (fabs(frame->dir.x) > 1)
	{
		if (frame->dir.x > 1)
			frame->dir.x = 1;
		else
			frame->dir.x = -1;
	}
	if (fabs(frame->dir.y) > 1)
	{
		if (frame->dir.y > 1)
			frame->dir.y = 1;
		else
			frame->dir.y = -1;
	}
	old_plane_x = frame->plane.x;
//	plane->x = cos(acos(frame->dir.x) - PI / 2);
	plane->x = old_plane_x * cos(ROT_SPEED) - frame->plane.y * sin(ROT_SPEED);
	plane->y = old_plane_x * sin(ROT_SPEED) + frame->plane.y * cos(ROT_SPEED);
*/
}

	int
press_key(int key, t_data *data)
{
	if (data->life.value <= 0)
		return (game_over_answer(data, key));
	if (key == KEY_P)
		create_bmp(data, &data->scr, "./screenshots/screenshot");
	if (key == KEY_ESC)
		close_program(data, "\nSee you next time ! ", "\\o/\n");
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
	if(data->settings.map[(int)data->frame.pos.y][(int)data->frame.pos.x] > '1')
		sprite_hit(data);
//	ft_putnbr_fd(key, 1);
//	print_map(data);
//	print_sprite_list(data);
//	printf("\nvalue = %d;", data->life.value);
//	printf("\nspr_count = %d;", data->settings.spr_count);
//	printf("\n------------");
	data->frame.spr_sorted = 0;
	data->map.done = 0;
	data->frame.done = 0;
	return(key);
}

	int	
red_cross(t_data *data)
{
	close_program(data, "\nSee you next time ! ", "\\o/\n");
	return (0);
}

	void
hook_event(t_data *data)
{
	mlx_hook(data->window, 2, 1L << 0, press_key, data);
	mlx_hook(data->window, 17, 1L << 17, red_cross, data);
}
