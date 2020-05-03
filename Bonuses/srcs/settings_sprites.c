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

	int
sprite_player_same_cell(t_set *set, int i)
{
	t_int	spr;
	t_int	player;

	spr.x = (int)set->spr[i].x;
	spr.y = (int)set->spr[i].y;
	player.x = (int)set->pos.x;
	player.y = (int)set->pos.y;

	if (spr.x == player.x && spr.y == player.y)
		return (1);
	else
		return (0);
}

	int
get_sprite_y(t_data *data, t_img img, int scr_y, int height_on_scr)
{
	int		spr_pxl_y;
	int		spr_height;
	int		step;
	
	spr_height= img.size.y;
	step = scr_y - data->set.win_size.y / 2 + height_on_scr / 2;
	spr_pxl_y = ((step * spr_height) / height_on_scr);
	return (spr_pxl_y);
}

	int
get_sprite_x(t_img img, int scr_x, int width_on_scr, double center_x)
{
	int		spr_pxl_x;
	int		spr_width;

	spr_width = img.size.x;
	spr_pxl_x = (int)(256 * fabs(scr_x - (- width_on_scr / 2 
					+ center_x)) * spr_width / width_on_scr) / 256;
	return (spr_pxl_x);
}
