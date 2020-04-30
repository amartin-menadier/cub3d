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
game_over_answer(t_data *data, int key)
{
	char *path;

	if (key == KEY_Y)
	{
		path = ft_strdup(data->cub_path);
		free_all(data);
		data->cub_path = ft_strdup(path);
		free(path);
		path = NULL;
		start_game(data);
	}
	if (key == KEY_N || key == KEY_ESC)
		close_program(data, "\nSee you next time !", "\\o/\n");
	return (-1);
}

	void
draw_game_over(t_data *data, t_int pxl, t_int draw_start)
{
	t_int		g_o_pxl;
	t_dbl		step;
	t_int		win;

	win.x = data->set.win_size.x;
	win.y = data->set.win_size.y;
	if ((step.x = ((double)data->piclib.game_over.size.x / (double)win.x)) < 1)
		step.x = 1;
	if ((step.y = ((double)data->piclib.game_over.size.y / (double)win.y)) < 1)
		step.y = 1;
	g_o_pxl.x = (int)((pxl.x - draw_start.x) * step.x);
	g_o_pxl.y = (int)((pxl.y - draw_start.y) * step.y);
	put_pixel(&data->scr, pxl, data->piclib.game_over.colors
				[(data->piclib.game_over.size.x * g_o_pxl.y + g_o_pxl.x)]);
}

	void
game_over(t_data *data)
{
	t_int	pxl;
	t_int	win;
	t_int	draw_start;
	t_int	draw_end;

	create_img(data, "./textures/gameover.xpm", &data->piclib.game_over);
	win.x = data->set.win_size.x;
	win.y = data->set.win_size.y;
	if ((draw_start.x = (win.x - data->piclib.game_over.size.x) / 2) <= 0)
		draw_start.x = 0;
	if ((draw_start.y = (win.y - data->piclib.game_over.size.y) / 2) <= 0)
		draw_start.y = 0;
	draw_end.x = win.x - draw_start.x;
	draw_end.y = win.y - draw_start.y;
	pxl.x = 0;
	while (pxl.x < win.x)
	{
		pxl.y = 0;
		while (pxl.y < win.y)
		{
			if ((pxl.x < draw_start.x || pxl.x > draw_end.x) 
					|| (pxl.y < draw_start.y || pxl.y > draw_end.y))
				put_pixel(&data->scr, pxl, BLACK);
			else
				draw_game_over(data, pxl, draw_start);
			pxl.y++;
		}
		pxl.x++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->scr.ptr, 0, 0);
	mlx_string_put(data->mlx, data->window, (win.x / 2) - 119, 9 * win.y / 10, WHITE, "DO YOU WANT TO TRY AGAIN ? (Y / N)");
}
