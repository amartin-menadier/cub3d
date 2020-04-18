/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:07 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	void
draw_minimap_mask(t_data *data, t_minimap *map, t_img mask, int banner_end)
{
	t_int	pxl;
	int		diameter;
	int		ctr_dist;
	int		color;

	diameter = map->draw_end.x + map->margin * 2; // + margin ?
	pxl.x = 0;
	while (pxl.x < diameter)
	{
		pxl.y = 0;
		while (pxl.y < diameter)
		{
			ctr_dist = (int)hypot((map->center.x - pxl.x), (map->center.y - pxl.y));
			color = mask.colors[mask.size.x * (pxl.y % 16) + pxl.x % 32];
			if (ctr_dist == diameter / 2 - 1)
				color = WHITE;
			if (ctr_dist == diameter / 2)
				color = DARK_GREY;
			if (ctr_dist <= diameter / 2)
				put_pixel(&data->img, pxl, color);
				(void)banner_end;
			pxl.y++;
		}
		pxl.x++;
	}
}

	void
draw_mask(t_data *data, t_settings *settings, t_minimap *map, t_life *life)
{
	int		draw_end_y;
	int		color;
	t_int	pxl;
	t_img	mask;

	mask.ptr = NULL;
	create_img(data, "./textures/civ_mask.xpm", &mask);
	draw_end_y = life->draw_start.y + life->draw_end.y + 3;
	pxl.x = 0;
	while (pxl.x < settings->win_size.x)
	{
		pxl.y = 0;
		while (pxl.y < draw_end_y)
		{
			color = mask.colors[mask.size.x * (pxl.y % 16) + pxl.x % 32];
			if (pxl.y == draw_end_y - 2)
				color = WHITE;
			if (pxl.y == draw_end_y - 1)
				color = DARK_GREY;
			put_pixel(&data->img, pxl, color);
			pxl.y++;
		}
		pxl.x++;
	}
	draw_minimap_mask(data, map, mask, draw_end_y);
	mlx_destroy_image(data->mlx, mask.ptr);
}

	int
render_next_frame(t_data *data)
{
	int		x;
	t_img	*text_img;
	char	*life_value;

	if (data->life.value > 0 && data->frame.done == 0)
	{
		ft_putstr_fd("\nFRAME01", 1);
	set_floor(data, &data->settings, &data->floor);
	x = 0;
	while (x < data->settings.win_size.x)
	{
		if (x == 0)ft_putstr_fd("\nFRAME02", 1);
		set_ray(data, &data->frame, x);
		if (x == 0)ft_putstr_fd("\nFRAME03", 1);
		perform_DDA(data, &data->frame);
		if (x == 0)ft_putstr_fd("\nFRAME04", 1);
		data->frame.z_buffer[x] = data->frame.perp_wall_dist;
		if (x == 0)ft_putstr_fd("\nFRAME05", 1);
		set_drawing_limits(data, &data->frame);
		if (x == 0)ft_putstr_fd("\nFRAME06", 1);
		text_img = get_wall_texture(&data->frame);
		if (x == 0)ft_putstr_fd("\nFRAME07", 1);
		draw_column(data, &data->frame, text_img, x);
		x++;
	}
		ft_putstr_fd("\nFRAME08", 1);
	sort_sprites(&data->settings, &data->frame);
		ft_putstr_fd("\nFRAME09", 1);
	draw_sprites(data, &data->settings, &data->frame);
		ft_putstr_fd("\nFRAME110", 1);
	draw_mask(data, &data->settings, &data->map, &data->life);
	draw_minimap(data, &data->settings, &data->map);
		ft_putstr_fd("\nFRAME111", 1);
	draw_life_bar(data, &data->settings, &data->life);
	if (data->save == 1)
		create_bmp(data, &data->img, "start.bmp");
		ft_putstr_fd("\nFRAME112", 1);
	mlx_put_image_to_window(data->mlx, data->window, data->img.ptr, 0, 0);
	life_value = ft_itoa(data->life.value);
	mlx_string_put(data->mlx, data->window,
		data->life.ctr.x, data->life.ctr.y, GREY, life_value);
	free(life_value);
	data->frame.done = 1;
	}
	return (0);
}

	void
draw_column(t_data *data, t_frame *F, t_img *text_img, int x)
{
	t_int	pos;
	double	step;
	double	texPos;

	pos.x = x;
	pos.y = 0;
	while (pos.y < F->draw_start)
	{
	//	put_pixel(&data->img, pos, data->settings.ceiling_color);
		pos.y++;
	}
	step = 1.0 * text_img->size.y / F->line_height;
	texPos = (F->draw_start - data->settings.win_size.y / 2 +
			F->line_height / 2) * step;
	while (pos.y < F->draw_end)
	{
		F->text.y = (int)texPos & (text_img->size.y - 1);
		texPos += step;
		put_pixel(&data->img, pos, text_img->colors
				[(text_img->size.y * F->text.y + F->text.x)]);
		pos.y++;
	}
	pos.y--;
//	while (pos.y++ < data->settings.win_size.y)
//		put_pixel(&data->img, pos, data->settings.floor_color);
}

	void
set_drawing_limits(t_data *data, t_frame *F)
{
	F->line_height =
		abs((int)(data->settings.win_size.y / (F->perp_wall_dist)));
	F->draw_start = -F->line_height / 2 + data->settings.win_size.y / 2;
	if(F->draw_start < 0)
		F->draw_start = 0;
	F->draw_end = F->line_height / 2 + data->settings.win_size.y / 2;
	if(F->draw_end >= data->settings.win_size.y)
		F->draw_end = data->settings.win_size.y;
	if (F->side == 0)
		F->wall_x = F->pos.y + F->perp_wall_dist * F->ray.y;
	else
		F->wall_x = F->pos.x + F->perp_wall_dist * F->ray.x;
	F->wall_x -= floor((F->wall_x));
}

/*
 ** DDA = Digital Differential Analyser
 */

	void
perform_DDA(t_data *data, t_frame *F)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if(F->side_dist.x < F->side_dist.y)
		{
			F->side_dist.x += F->delta_dist.x;
			F->map.x += F->step.x;
			F->side = 0;
		}
		else
		{
			F->side_dist.y += F->delta_dist.y;
			F->map.y += F->step.y;
			F->side = 1;
		}
		if(data->settings.map[(int)F->map.y][(int)F->map.x] == '1')
			hit = 1;
	}
	if(F->side == 0)
		F->perp_wall_dist = (F->map.x - F->pos.x + (1 - F->step.x)/2)/ F->ray.x;
	else
		F->perp_wall_dist = (F->map.y - F->pos.y + (1 - F->step.y)/2)/ F->ray.y;
}

	void
set_ray(t_data *data, t_frame *F, int x)
{
	F->map.x = (int)F->pos.x;
	F->map.y = (int)F->pos.y;
	F->camera_x = 2 * x /(double)data->settings.win_size.x - 1;
	F->ray.x = F->dir.x + F->plane.x * F->camera_x;
	F->ray.y = F->dir.y + F->plane.y * F->camera_x;
	F->delta_dist.x =
		(F->ray.y == 0) ? 0 : ((F->ray.x == 0) ? 1 : fabs(1 / F->ray.x));
	F->delta_dist.y =
		(F->ray.x == 0) ? 0 : ((F->ray.y == 0) ? 1 : fabs(1 / F->ray.y));
	if (F->ray.x < 0)
		F->step.x = -1;
	else
		F->step.x = 1;
	if (F->ray.y < 0)
		F->step.y = -1;
	else
		F->step.y = 1;
	if (F->ray.x < 0)
		F->side_dist.x = (F->pos.x - F->map.x) * F->delta_dist.x;
	else
		F->side_dist.x = (F->map.x + 1.0 - F->pos.x) * F->delta_dist.x;
	if (F->ray.y < 0)
		F->side_dist.y = (F->pos.y - F->map.y) * F->delta_dist.y;
	else
		F->side_dist.y = (F->map.y + 1.0 - F->pos.y) * F->delta_dist.y;
}
