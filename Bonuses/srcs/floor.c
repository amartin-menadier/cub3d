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
set_floor(t_data *data, t_settings *settings, t_floor *flr)
{
	t_int	pxl;

	pxl.y = 0;
	while (pxl.y < settings->win_size.y)
	{
		flr->ray0.x = data->frame.dir.x - data->frame.plane.x;
		flr->ray0.y = data->frame.dir.y - data->frame.plane.y;
		flr->ray1.x = data->frame.dir.x + data->frame.plane.x;
		flr->ray1.y = data->frame.dir.y + data->frame.plane.y;
		flr->pxl_height = pxl.y - settings->win_size.y / 2;
		flr->cam_height = 0.5 * settings->win_size.y;
		flr->depth = flr->cam_height / flr->pxl_height;
		flr->step.x = flr->depth * (flr->ray1.x - flr->ray0.x) / settings->win_size.x;
		flr->step.y = flr->depth * (flr->ray1.y - flr->ray0.y) / settings->win_size.x;
		flr->pos.x = data->frame.pos.x + flr->depth * flr->ray0.x;
		flr->pos.y = data->frame.pos.y + flr->depth * flr->ray0.y;
		pxl.x = 0;
		while (pxl.x < settings->win_size.x)
		{
			flr->cell.x = (int)(flr->pos.x);
			flr->cell.y = (int)(flr->pos.y);
			flr->txt_pxl.x = (int)(flr->flr_img.size.x * (flr->pos.x - flr->cell.x)) & (flr->flr_img.size.x - 1);
			flr->txt_pxl.y = (int)(flr->flr_img.size.y * (flr->pos.y - flr->cell.y)) & (flr->flr_img.size.y - 1);
			flr->pos.x += flr->step.x;
			flr->pos.y += flr->step.y;
			int	color;
			color = flr->flr_img.colors[flr->flr_img.size.x * flr->txt_pxl.y + flr->txt_pxl.x];
			color = (color >> 1) & 8355711; // make a bit darker
			put_pixel(&data->img, pxl, color);
			color = flr->clg_img.colors[flr->clg_img.size.x * flr->txt_pxl.y + flr->txt_pxl.x];
			color = (color >> 1) & 8355711; // make a bit darker
			pxl.y = settings->win_size.y - pxl.y - 1;
			put_pixel(&data->img, pxl, color);
			pxl.y = settings->win_size.y - pxl.y - 1;
			pxl.x++;
		}
		pxl.y++;
	}
}
