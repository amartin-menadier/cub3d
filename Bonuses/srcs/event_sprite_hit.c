/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 12:15:52 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	void
sprite_hit(t_data *data)
{
	t_int	cam;
	char	case_value;
	
	cam.x = (int)data->cam.x;
	cam.z = (int)data->cam.z;
	case_value = data->map[cam.z][cam.x];
	if (case_value == HEAL_SPR && data->life == 100)
		return;
	if (case_value == DAMAGE_SPR)
		data->life -= 19;
	if (data->life <= 0)
		game_over(data, data->win.size, &data->piclib.game_over);
	if (case_value == HEAL_SPR)
		data->life += 20;
	if (data->life > 100)
		data->life = 100;
	data->map[cam.z][cam.x] = EMPTY;
	data->spr_count--;
	free(data->spr);
	data->spr = NULL;
	get_sprites_in_map(data, data->map);
}

