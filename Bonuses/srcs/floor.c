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

//FLOOR CASTING

	void
set_floor(t_data *data, t_set *set, t_floor *flr)
{
	t_int	pxl;

	pxl.y = 0;
	while (pxl.y < set->win_size.y)
	{
//		flr->ray0.x = data->set.dir.x - data->set.plane.x;
//		flr->ray0.y = data->set.dir.y - data->set.plane.y;
//		flr->ray1.x = data->set.dir.x + data->set.plane.x;
//		flr->ray1.y = data->set.dir.y + data->set.plane.y;
		flr->ray0.x = cos(set->angle) - cos(set->angle - PI / 2);
		flr->ray0.y = sin(set->angle) - sin(set->angle - PI / 2);
		flr->ray1.x = cos(set->angle) + cos(set->angle - PI / 2);
		flr->ray1.y = sin(set->angle) + sin(set->angle - PI / 2);
	
		flr->pxl_height = pxl.y - set->win_size.y / 2;
		flr->cam_height = 0.5 * set->win_size.y;
		flr->depth = flr->cam_height / flr->pxl_height;
		flr->step.x = flr->depth * (flr->ray1.x - flr->ray0.x) / set->win_size.x;
		flr->step.y = flr->depth * (flr->ray1.y - flr->ray0.y) / set->win_size.x;
		flr->pos.x = data->set.pos.x + flr->depth * flr->ray0.x;
		flr->pos.y = data->set.pos.y + flr->depth * flr->ray0.y;
		pxl.x = 0;
		while (pxl.x < set->win_size.x)
		{
			flr->cell.x = (int)(flr->pos.x);
			flr->cell.y = (int)(flr->pos.y);
			flr->txt_pxl.x = (int)(data->piclib.flr.size.x * (flr->pos.x - flr->cell.x)) & (data->piclib.flr.size.x - 1);
			flr->txt_pxl.y = (int)(data->piclib.flr.size.y * (flr->pos.y - flr->cell.y)) & (data->piclib.flr.size.y - 1);
			flr->pos.x += flr->step.x;
			flr->pos.y += flr->step.y;
			int	color;
			color = data->piclib.flr.colors[data->piclib.flr.size.x * flr->txt_pxl.y + flr->txt_pxl.x];
			color = (color >> 1) & 8355711; // make a bit darker
			put_pixel(&data->scr, pxl, color);
			color = data->piclib.sky.colors[data->piclib.sky.size.x * flr->txt_pxl.y + flr->txt_pxl.x];
			color = (color >> 1) & 8355711; // make a bit darker
			pxl.y = set->win_size.y - pxl.y - 1;
			put_pixel(&data->scr, pxl, color);
			pxl.y = set->win_size.y - pxl.y - 1;
			pxl.x++;
		}
		pxl.y++;
	}
}
/*
	void
set_floor(t_data *data, t_set *set, t_floor *flr)
{
	t_int	pxl;

	pxl.y = 0;
	while (pxl.y < set->win_size.y)
	{
//		flr->ray0.x = data->set.dir.x - data->set.plane.x;
//		flr->ray0.y = data->set.dir.y - data->set.plane.y;
//		flr->ray1.x = data->set.dir.x + data->set.plane.x;
//		flr->ray1.y = data->set.dir.y + data->set.plane.y;
		flr->ray0.x = cos(set->angle) - cos(set->angle - PI / 2);
		flr->ray0.y = sin(set->angle) - sin(set->angle - PI / 2);
		flr->ray1.x = cos(set->angle) + cos(set->angle - PI / 2);
		flr->ray1.y = sin(set->angle) + sin(set->angle - PI / 2);
	
		flr->pxl_height = pxl.y - set->win_size.y / 2;
		flr->cam_height = 0.5 * set->win_size.y;
		flr->depth = flr->cam_height / flr->pxl_height;
		flr->step.x = flr->depth * (flr->ray1.x - flr->ray0.x) / set->win_size.x;
		flr->step.y = flr->depth * (flr->ray1.y - flr->ray0.y) / set->win_size.x;
		flr->pos.x = data->set.pos.x + flr->depth * flr->ray0.x;
		flr->pos.y = data->set.pos.y + flr->depth * flr->ray0.y;
		pxl.x = 0;
		while (pxl.x < set->win_size.x)
		{
			flr->cell.x = (int)(flr->pos.x);
			flr->cell.y = (int)(flr->pos.y);
			flr->txt_pxl.x = (int)(data->piclib.flr.size.x * (flr->pos.x - flr->cell.x)) & (data->piclib.flr.size.x - 1);
			flr->txt_pxl.y = (int)(data->piclib.flr.size.y * (flr->pos.y - flr->cell.y)) & (data->piclib.flr.size.y - 1);
			flr->pos.x += flr->step.x;
			flr->pos.y += flr->step.y;
			int	color;
			color = data->piclib.flr.colors[data->piclib.flr.size.x * flr->txt_pxl.y + flr->txt_pxl.x];
			color = (color >> 1) & 8355711; // make a bit darker
			put_pixel(&data->scr, pxl, color);
			color = data->piclib.sky.colors[data->piclib.sky.size.x * flr->txt_pxl.y + flr->txt_pxl.x];
			color = (color >> 1) & 8355711; // make a bit darker
			pxl.y = set->win_size.y - pxl.y - 1;
			put_pixel(&data->scr, pxl, color);
			pxl.y = set->win_size.y - pxl.y - 1;
			pxl.x++;
		}
		pxl.y++;
	}
}
