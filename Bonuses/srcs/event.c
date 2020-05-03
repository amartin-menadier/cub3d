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
sprite_hit(t_data *data, t_set *set)
{
	t_int	pos;
	char	case_value;
	
	pos.x = (int)set->pos.x;
	pos.y = (int)set->pos.y;
	case_value = set->map[pos.y][pos.x];
	if (case_value == HEAL_SPR && set->life == 100)
		return;
	if (case_value == DAMAGE_SPR)
		set->life -= 19;
	if (set->life <= 0)
		game_over(data);
	if (case_value == HEAL_SPR)
		set->life += 20;
	if (set->life > 100)
		set->life = 100;
	set->map[pos.y][pos.x] = EMPTY;
	set->spr_count--;
	free(set->spr);
	set->spr = NULL;
	get_sprites_data(data, set, set->map);
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
		sprite_hit(data, &data->set);
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
