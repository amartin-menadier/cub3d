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

	int
render_next_frame(t_data *data)
{
	int		x;
	t_img	*text_img;

	x = 0;
	while (x < data->settings.win_size.x)
	{
		set_ray(data, &data->frame, x);
		perform_DDA(data, &data->frame);
		data->frame.z_buffer[x] = data->frame.perp_wall_dist;
		set_drawing_limits(data, &data->frame);
		text_img = get_texture_img(&data->frame);
		draw_column(data, &data->frame, text_img, x);
		x++;
	}
	sort_sprites(&data->settings, &data->frame);
	draw_sprites(data, &data->settings, &data->frame, &data->frame.S_img);
	if (data->save == 1)
	{
		create_bmp(data, &data->img, "start.bmp");
		close_program(data, "First image of the game saved ", "\\o/\n");
	}	
	mlx_put_image_to_window(data->mlx, data->window, data->img.ptr, 0, 0);
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
		put_pixel(&data->img, pos, data->settings.ceiling_color);
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
	while (pos.y++ < data->settings.win_size.y)
		put_pixel(&data->img, pos, data->settings.floor_color);
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
