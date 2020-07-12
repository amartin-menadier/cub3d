/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_game_over_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadier <amenadier@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/12 14:47:31 by amenadier        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int
	game_over_answer(t_data *data, int key)
{
	char *path;

	if (key == Y)
	{
		path = ft_strdup(data->cub_path);
		free_all(data);
		data->cub_path = ft_strdup(path);
		free(path);
		path = NULL;
		start_game(data);
	}
	if (key == N || key == ESC)
		close_program(data, "\nSee you next time !", "\\o/\n");
	return (-1);
}

void
	draw_game_over(t_data *data, t_int pxl, t_int draw_start, t_int draw_end)
{
	t_int		img_pxl;
	t_dbl		step;
	t_int		size;
	int			color;
	t_img		img;

	size = data->win.size;
	img = data->piclib.game_over;
	if ((step.x = ((double)data->piclib.game_over.size.x / (double)size.x)) < 1)
		step.x = 1;
	if ((step.z = ((double)data->piclib.game_over.size.y / (double)size.y)) < 1)
		step.z = 1;
	img_pxl.x = (int)((pxl.x - draw_start.x) * step.x);
	img_pxl.y = (int)((pxl.y - draw_start.y) * step.z);
	if ((pxl.x < draw_start.x || pxl.x > draw_end.x)
			|| (pxl.y < draw_start.y || pxl.y > draw_end.y))
		color = BLACK;
	else
		color = img.colors[img.size.x * img_pxl.y + img_pxl.x];
	put_pixel(&data->win, pxl, color);
}

void
	game_over(t_data *data, t_int win_size, t_img *img)
{
	t_int	pxl;
	t_int	draw_start;
	t_int	draw_end;

	if ((draw_start.x = (win_size.x - img->size.x) / 2) <= 0)
		draw_start.x = 0;
	if ((draw_start.y = (win_size.y - img->size.y) / 2) <= 0)
		draw_start.y = 0;
	draw_end.x = win_size.x - draw_start.x;
	draw_end.y = win_size.y - draw_start.y;
	pxl.x = 0;
	while (pxl.x < win_size.x)
	{
		pxl.y = 0;
		while (pxl.y < win_size.y)
		{
			draw_game_over(data, pxl, draw_start, draw_end);
			pxl.y++;
		}
		pxl.x++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->win.ptr, 0, 0);
	mlx_string_put(data->mlx, data->window, (win_size.x / 2) - 119,
			9 * win_size.y / 10, WHITE, "DO YOU WANT TO TRY AGAIN ? (Y / N)");
}
