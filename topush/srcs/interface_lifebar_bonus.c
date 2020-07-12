/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_lifebar_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/12 19:27:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int
	lifebar_data(t_data *data, int mod)
{
	t_int	size;

	size.x = data->win.size.x / 3.3;
	size.y = fmax(minimap_data(data, SIZE_IN_PXL) / MINIMAP_CELLS, 3);
	if (mod == LENGTH)
		return (size.x);
	else if (mod == DRAW_START_X)
		return (fmax(data->win.size.x / 2 - size.x / 2,
				minimap_data(data, DRAW_END) + minimap_data(data, MARGIN)));
	else if (mod == DRAW_START_Y)
		return (minimap_data(data, DRAW_START));
	else if (mod == DRAW_END_X)
		return (lifebar_data(data, DRAW_START_X) + size.x);
	else if (mod == DRAW_END_Y)
		return (lifebar_data(data, DRAW_START_Y) + size.y);
	else if (mod == CENTER_X && data->life == 100)
		return ((data->win.size.x - 21) / 2);
	else if (mod == CENTER_X && data->life < 10)
		return ((data->win.size.x - 21) / 2 + 7);
	else if (mod == CENTER_X)
		return ((data->win.size.x - 21) / 2 + 4);
	else if (mod == CENTER_Y)
		return (minimap_data(data, DRAW_START) / 2 + lifebar_data(data,
			DRAW_END_Y) / 2 + 5);
		return (-9999);
}

void
	draw_life_string(t_data *data)
{
	char	*value;
	t_int	ctr;

	ctr.x = lifebar_data(data, CENTER_X);
	ctr.y = lifebar_data(data, CENTER_Y);
	value = ft_itoa(data->life);
	mlx_string_put(data->mlx, data->window, ctr.x, ctr.y, BLACK, value);
	free(value);
}

void
	draw_lifebar(t_data *data, int length, int color)
{
	t_int	win;
	t_int	draw_start;
	t_int	draw_end;

	draw_start.x = lifebar_data(data, DRAW_START_X);
	draw_start.y = lifebar_data(data, DRAW_START_Y);
	draw_end.x = lifebar_data(data, DRAW_END_X);
	draw_end.y = lifebar_data(data, DRAW_END_Y);
	win.x = draw_start.x;
	while (win.x <= draw_end.x)
	{
		win.y = draw_start.y;
		while (win.y <= draw_end.y)
		{
			if (win.x == draw_start.x || win.x == draw_end.x
				|| win.y == draw_start.y || win.y == draw_end.y)
				put_pixel(&data->win, win, BLACK);
			else if (((win.x - draw_start.x) * 100) / (length - 2)
				<= data->life)
				put_pixel(&data->win, win, color);
			win.y++;
		}
		win.x++;
	}
}
