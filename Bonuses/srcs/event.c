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
sprite_hit(t_data *data)
{
	t_int	pos;
	char	case_value;
	
	pos.x = (int)data->set.pos.x;
	pos.y = (int)data->set.pos.y;
	case_value = data->set.map[pos.y][pos.x];
	if (case_value == '3' && data->set.life == 100)
		return;
	if (case_value == '2')
		data->set.life -= 19;
	if (data->set.life <= 0)
		game_over(data);
	if (case_value == '3')
		data->set.life += 20;
	if (data->set.life > 100)
		data->set.life = 100;
	data->set.map[pos.y][pos.x] = '0';
	data->set.spr_count--;
	free(data->set.spr);
	data->set.spr = NULL;
	get_sprites_data(data, &data->set, data->set.map);
}

	void
look(double *angle, int key)
{
	if (key == LEFT)
		*angle += ROT_SPEED;
	if (key == RIGHT)
		*angle -= ROT_SPEED;
}

	int
press_key(int key, t_data *data)
{
	if (data->set.life <= 0)
		return (game_over_answer(data, key));
	if (key == P)
		create_bmp(data, &data->scr, "./screenshots/screenshot");
	if (key == ESC)
		close_program(data, "\nSee you next time ! ", "\\o/\n");
	if (LOOK(key))
		look(&data->set.angle, key);
	if (MOVE(key))
		move(&data->set, data->set.map, key);
	if(data->set.map[(int)data->set.pos.y][(int)data->set.pos.x] > WALL)
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
