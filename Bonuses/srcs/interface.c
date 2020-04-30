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
draw_minimap_mask(t_data *data, t_img mask, int center)
{
	t_int	pxl;
	int		diameter;
	int		ctr_dist;
	int		color;

	diameter = minimap_data(data, DRAW_END) + minimap_data(data, MARGIN);
	pxl.x = 0;
	while (pxl.x < diameter)
	{
		pxl.y = 0;
		while (pxl.y < diameter)
		{
			ctr_dist = (int)round(hypot((center - pxl.x), (center - pxl.y)));
			color = mask.colors[mask.size.x * (pxl.y % 16) + pxl.x % 32];
			if (ctr_dist == diameter / 2 - 1)
				color = WHITE;
			if (ctr_dist == diameter / 2)
				color = DARK_GREY;
			if (ctr_dist <= diameter / 2)
				put_pixel(&data->scr, pxl, color);
			pxl.y++;
		}
		pxl.x++;
	}
}

	void
draw_mask(t_data *data, t_img mask)
{
	int		draw_end_y;
	int		color;
	t_int	pxl;

	draw_end_y = lifebar_data(data, DRAW_START_Y)
			+ lifebar_data(data, DRAW_END_Y) + 3; 
	pxl.x = 0;
	while (pxl.x < data->set.win_size.x)
	{
		pxl.y = 0;
		while (pxl.y < draw_end_y)
		{
			color = mask.colors[mask.size.x * (pxl.y % 16) + pxl.x % 32];
			if (pxl.y == draw_end_y - 2)
				color = WHITE;
			if (pxl.y == draw_end_y - 1)
				color = DARK_GREY;
			put_pixel(&data->scr, pxl, color);
			pxl.y++;
		}
		pxl.x++;
	}
	draw_minimap_mask(data, mask, minimap_data(data, CENTER));
}

	void
draw_lifebar(t_data *data, int length, int color)
{
	t_int	pxl;
	t_int	draw_start;
	t_int	draw_end;

	draw_start.x = lifebar_data(data, DRAW_START_X);
	draw_start.y = lifebar_data(data, DRAW_START_Y);
	draw_end.x = lifebar_data(data, DRAW_END_X);
	draw_end.y = lifebar_data(data, DRAW_END_Y);
	pxl.x = draw_start.x;
	while (pxl.x <= draw_end.x)
	{
		pxl.y = draw_start.y;
		while (pxl.y <= draw_end.y)
		{
			if (pxl.x == draw_start.x || pxl.x == draw_end.x
				|| pxl.y == draw_start.y || pxl.y == draw_end.y)
				put_pixel(&data->scr, pxl, BLACK);
			else if (((pxl.x - draw_start.x) * 100) / (length - 2)
				<= data->set.life)
				put_pixel(&data->scr, pxl, color);
			pxl.y++;
		}
		pxl.x++;
	}
}

	int
lifebar_data(t_data *data, int mod)
{
	t_int	size;

	size.x = data->set.win_size.x / 3.3;
	size.y = fmax(minimap_data(data, SIZE_IN_PXL) / MINIMAP_CELLS, 3);
	if (mod == LENGTH)
		return (size.x);
	else if (mod == DRAW_START_X)
		return (fmax(data->set.win_size.x / 2 - size.x / 2,
				minimap_data(data, DRAW_END) + minimap_data(data, MARGIN)));
	else if (mod == DRAW_START_Y)
		return (minimap_data(data, DRAW_START));
	else if (mod == DRAW_END_X)
		return (lifebar_data(data, DRAW_START_X) + size.x);
	else if (mod == DRAW_END_Y)
		return (lifebar_data(data, DRAW_START_Y) + size.y);
	else if (mod == CENTER_X && data->set.life == 100)
		return ((data->set.win_size.x - 21) / 2);
	else if (mod == CENTER_X && data->set.life < 10)
		return ((data->set.win_size.x - 21) / 2 + 7);
	else if (mod == CENTER_X)
		return ((data->set.win_size.x - 21) / 2 + 4);
	else if (mod == CENTER_Y)
		return (minimap_data(data, DRAW_START) / 2
				+ lifebar_data(data, DRAW_END_Y) / 2 + 5);
	return (-9999);
}

	void
draw_interface(t_data *data, t_piclib *piclib, t_set *set)
{
	int		lifebar_color;
	int		lifebar_length;
	t_int	minimap_center;

	draw_mask(data, data->piclib.mask);
	get_minimap_avatar(data);
	minimap_center.x = minimap_data(data, CENTER);
	minimap_center.y = minimap_center.x;
	draw_minimap(data, minimap_center, minimap_data(data, RADIUS));
	if (data->set.life >= 80)
		lifebar_color = GREEN;
	else if (data->set.life >= 33)
		lifebar_color = ORANGE;
	else
		lifebar_color = RED;
	lifebar_length = lifebar_data(data, LENGTH);
	draw_lifebar(data, lifebar_length, lifebar_color);
	(void)piclib;
	(void)set;
}
