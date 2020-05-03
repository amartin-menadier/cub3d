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
draw_life_string(t_data *data)
{
	char	*value;
	t_int	ctr;

	ctr.x = lifebar_data(data, CENTER_X);
	ctr.y = lifebar_data(data, CENTER_Y);
	value = ft_itoa(data->set.life);
	mlx_string_put(data->mlx, data->window, ctr.x, ctr.y, BLACK, value);
	free(value);
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
