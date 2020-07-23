/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_sprite_hit_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/23 20:18:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

char
	*new_level_path(char *old_path, char order)
{
	if (!ft_strncmp(old_path, "./cub/bonus/42_0.cub", 21))
		return (ft_strdup("./cub/bonus/42_from01.cub"));
	if (old_path[ft_strlen(old_path) - 5] == '1' && order == STAIRS_DOWN)
		return (ft_strdup("./cub/bonus/42_0.cub"));
	if (old_path[ft_strlen(old_path) - 5] == '1' && order == STAIRS_UP)
		return (ft_strdup("./cub/bonus/42_2.cub"));
	if (old_path[ft_strlen(old_path) - 5] == '2' && order == STAIRS_DOWN)
		return (ft_strdup("./cub/bonus/42_1.cub"));
	if (old_path[ft_strlen(old_path) - 5] == '2' && order == STAIRS_UP)
		return (ft_strdup("./cub/bonus/42_3.cub"));
	if (old_path[ft_strlen(old_path) - 5] == '3')
		return (ft_strdup("./cub/bonus/42_2.cub"));
	return (NULL);
}

void
	load_new_level(t_data *data, char order)
{
	char	*path;

	path = NULL;
	if (order != ELEVATOR)
		path = new_level_path(data->cub_path, order);
	else
		path = ft_strdup("./cub/bonus/skybox.cub");
	free_all(data);
	data->cub_path = ft_strdup(path);
	free(path);
	path = NULL;
	start_game(data);
}

void
	draw_victory(t_data *data, t_int pxl, t_int draw_start, t_int draw_end)
{
	t_int		img_pxl;
	t_dbl		step;
	t_int		size;
	int			color;
	t_img		img;

	size = data->win.size;
	img = data->piclib.victory;
	if ((step.x = ((double)data->piclib.victory.size.x / (double)size.x)) < 1)
		step.x = 1;
	if ((step.z = ((double)data->piclib.victory.size.y / (double)size.y)) < 1)
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

int
	victory(t_data *data, t_int win_size, t_img *img)
{
	t_int	pxl;
	t_int	draw_start;
	t_int	draw_end;

	data->life = -9999;
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
			draw_victory(data, pxl, draw_start, draw_end);
			pxl.y++;
		}
		pxl.x++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->win.ptr, 0, 0);
	return (-1);
}

void
	sprite_hit(t_data *data)
{
	t_int	cam;
	char	case_value;

	cam.x = (int)data->cam.x;
	cam.z = (int)data->cam.z;
	case_value = data->map[cam.z][cam.x];
	if (case_value == HEAL_SPR && data->life == 100)
		return ;
	if (case_value == DAMAGE_SPR)
		data->life -= 19;
	if (data->life <= 0)
		game_over(data, data->win.size, &data->piclib.game_over);
	if (case_value == NORMINET)
		victory(data, data->win.size, &data->piclib.victory);
	if (case_value == HEAL_SPR)
		data->life += 20;
	if (data->life > 100)
		data->life = 100;
	data->map[cam.z][cam.x] = EMPTY;
	data->spr_count--;
	free(data->spr);
	data->spr = NULL;
	get_sprites_in_map(data, data->map);
}
