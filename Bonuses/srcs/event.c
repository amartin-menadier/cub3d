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
get_dir_and_plane(t_set *set)
{
	double	plane_angle;

	if (set->angle < (PI / 2))
		plane_angle = set->angle + 3 * PI / 2;
	else
		plane_angle = set->angle - PI / 2;
	set->dir.x = cos(set->angle);
	set->dir.y = sin(set->angle);
}


	void
look_left(t_set *set)
{
	set->angle += ROT_SPEED;
	if (set->angle >= (2 * PI))
		set->angle -= (2 * PI);
	get_dir_and_plane(set);
}

	void
look_right(t_set *set)
{
	set->angle -= ROT_SPEED;
	if (set->angle < 0)
		set->angle += (2 * PI);
	get_dir_and_plane(set);
}

	int
press_key(int key, t_data *data)
{
	if (data->set.life <= 0)
		return (game_over_answer(data, key));
	if (key == KEY_P)
		create_bmp(data, &data->scr, "./screenshots/screenshot");
	if (key == KEY_ESC)
		close_program(data, "\nSee you next time ! ", "\\o/\n");
	if (key == KEY_LEFT)
		look_left(&data->set);
	if (key == KEY_RIGHT)
		look_right(&data->set);
	if (key == KEY_Z)
		move_forward(&data->set, data->set.map);
	if (key == KEY_S)
		move_backward(&data->set, data->set.map);
	if (key == KEY_D)
		move_right(&data->set, data->set.map);
	if (key == KEY_Q)
		move_left(&data->set, data->set.map);
	if(data->set.map[(int)data->set.pos.y][(int)data->set.pos.x] > '1')
		sprite_hit(data);
	data->set.frame_done = 0;
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
