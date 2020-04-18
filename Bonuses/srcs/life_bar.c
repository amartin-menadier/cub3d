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

//PENSER A INIT ET FREE !!!
//
	void
sprite_hit(t_data *data)
{
	t_int	pos;
	char	case_value;
	
		ft_putstr_fd("\nLIFE00", 1);
	pos.x = (int)data->frame.pos.x;
	pos.y = (int)data->frame.pos.y;
	case_value = data->settings.map[pos.y][pos.x];
	if (case_value == '3' && data->life.value == 100)
		return;
	if (case_value == '2')
		data->life.value -= 19;
	if (data->life.value <= 0)
		game_over(data);
	if (case_value == '3')
		data->life.value += 20;
	if (data->life.value > 100)
		data->life.value = 100;
	data->settings.map[pos.y][pos.x] = '0';
	data->settings.spr_count--;
	free_sprites(&data->settings, &data->frame);
	get_sprites_data(data, &data->settings, data->settings.map);
}

	void
draw_life_bar(t_data *data, t_settings *settings, t_life *life)
{
	t_int	pxl;

	(void)settings;
	pxl.x = life->draw_start.x;
	while (pxl.x <= life->draw_end.x)
	{
		pxl.y = life->draw_start.y;
		while (pxl.y <= life->draw_end.y)
		{
			if (pxl.x == life->draw_start.x || pxl.x == life->draw_end.x 
				|| pxl.y == life->draw_start.y || pxl.y == life->draw_end.y)
				put_pixel(&data->img, pxl, 0);
			else if (((pxl.x - life->draw_start.x) * 100) / (life->size.x - 2)
				<= life->value)
				put_pixel(&data->img, pxl, life->color);
			pxl.y++;
		}
		pxl.x++;
	}
}

	void
set_life_bar_limits(t_data *data, t_settings *settings, t_life *life)
{
	if ((life->size.y = data->map.case_size) < 3)
		life->size.y = 3;
	life->size.x = settings->win_size.x / 3;
	while ((life->size.x + data->map.size) * 1.1 > settings->win_size.x)
		life->size.x /= 1.2;
	life->draw_start.x = settings->win_size.x / 2 - life->size.x / 2;
	if (life->draw_start.x < data->map.draw_end.x + data->map.margin)
		life->draw_start.x = data->map.draw_end.x + data->map.margin;
	life->draw_end.x = life->draw_start.x + life->size.x;
	life->draw_start.y = data->map.draw_start.y;
	life->draw_end.y = life->draw_start.y + life->size.y;
	life->ctr.x = (settings->win_size.x - 21) / 2;
	if (life->value < 100)
		life->ctr.x += 4;
	if (life->value < 10)
		life->ctr.x += 3;
	life->ctr.y = life->draw_end.y / 2 + life->draw_start.y / 2 + 5;
if (life->value >= 80)
		life->color = GREEN;
	else if (life->value >= 33)
		life->color = ORANGE;
	else
		life->color = RED;
}
