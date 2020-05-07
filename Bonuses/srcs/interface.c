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
draw_minimap_mask(t_data *data, t_img *mask, int center)
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
			color = mask->colors[mask->size.x * (pxl.y % 16) + pxl.x % 32];
			if (ctr_dist == diameter / 2 - 1)
				color = WHITE;
			if (ctr_dist == diameter / 2)
				color = DARK_GREY;
			if (ctr_dist <= diameter / 2)
				put_pixel(&data->win, pxl, color);
			pxl.y++;
		}
		pxl.x++;
	}
}

	void
draw_mask(t_data *data, t_img *mask)
{
	int		draw_end_y;
	int		color;
	t_int	pxl;

	draw_end_y = lifebar_data(data, DRAW_START_Y)
			+ lifebar_data(data, DRAW_END_Y) + 3; 
	pxl.x = 0;
	while (pxl.x < data->win.size.x)
	{
		pxl.y = 0;
		while (pxl.y < draw_end_y)
		{
			color = mask->colors[mask->size.x * (pxl.y % 16) + pxl.x % 32];
			if (pxl.y == draw_end_y - 2)
				color = WHITE;
			if (pxl.y == draw_end_y - 1)
				color = DARK_GREY;
			put_pixel(&data->win, pxl, color);
			pxl.y++;
		}
		pxl.x++;
	}
	draw_minimap_mask(data, mask, minimap_data(data, CENTER));
}

	void
draw_interface(t_data *data, t_piclib *piclib)
{
	int		lifebar_color;
	int		lifebar_length;
	t_int	minimap_center;

	draw_mask(data, &piclib->mask);
	get_minimap_avatar(data);
	minimap_center.x = minimap_data(data, CENTER);
	minimap_center.y = minimap_center.x;
	draw_minimap(data, minimap_center, minimap_data(data, RADIUS));
	if (data->life >= 80)
		lifebar_color = GREEN;
	else if (data->life >= 33)
		lifebar_color = ORANGE;
	else
		lifebar_color = RED;
	lifebar_length = lifebar_data(data, LENGTH);
	draw_lifebar(data, lifebar_length, lifebar_color);
}
