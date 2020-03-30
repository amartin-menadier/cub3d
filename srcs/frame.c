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
	t_img	*textimg;

	x = 0;
	while (x < data->settings.win_width)
	{
		set_ray(data, &data->frame, x);
		perform_DDA(data, &data->frame);
		data->frame.Zbuffer[x] = data->frame.perpWallDist;
		set_drawing_limits(data, &data->frame);
		textimg = get_texture_img(&data->frame);
		draw_column(data, &data->frame, textimg, x);
		x++;
	}
	sort_sprites(&data->settings, &data->frame);
	draw_sprites(data, &data->settings, &data->frame, &data->frame.Sprite_img);
	if (data->save == 1)
		create_bmp(data, &data->img, "start.bmp");
	mlx_put_image_to_window(data->mlx, data->window, data->img.ptr, 0, 0);
	return (0);
}

	void
draw_column(t_data *data, t_frame *frame, t_img *textimg, int x)
{
	double step;
	double texPos;
	t_vector	pos;

	pos.x = x;
	pos.y = 0;
	while (pos.y < frame->drawStart)
	{
		put_pixel(&data->img, &pos, data->settings.Ceiling_color);
		pos.y++;
	}
	step = 1.0 * textimg->th / frame->lineHeight;
	texPos = (frame->drawStart - data->settings.win_height / 2 +
			frame->lineHeight / 2) * step - 0.5;
	while (pos.y < frame->drawEnd)
	{
		frame->texY = (int)texPos & (textimg->th - 1);
		texPos += step;
		put_pixel(&data->img, &pos,
				textimg->colors[textimg->th * frame->texY + frame->texX]);
		pos.y++;
	}
	pos.y--;
	while (pos.y++ < data->settings.win_height)
		put_pixel(&data->img, &pos, data->settings.Floor_color);
}

	void
set_drawing_limits(t_data *data, t_frame *frame)
{
	frame->lineHeight =
		abs((int)(data->settings.win_height / (frame->perpWallDist)));
	frame->drawStart = -frame->lineHeight / 2 + data->settings.win_height / 2;
	if(frame->drawStart < 0)
		frame->drawStart = 0;
	frame->drawEnd = frame->lineHeight / 2 + data->settings.win_height / 2;
	if(frame->drawEnd >= data->settings.win_height)
		frame->drawEnd = data->settings.win_height;
	if (frame->side == 0)//EA and WE
		frame->wallX = frame->posY + frame->perpWallDist * frame->rayY;
	else
		frame->wallX = frame->posX + frame->perpWallDist * frame->rayX;
	frame->wallX -= floor((frame->wallX));
}

/*
 * DDA = Digital Differential Analyser
 */

	void
perform_DDA(t_data *data, t_frame *frame)
{
	frame->hit = 0;
	while (frame->hit == 0)
	{
		if(frame->sideDistX < frame->sideDistY)
		{
			frame->sideDistX += frame->deltaDistX;
			frame->mapX += frame->stepX;
			frame->side = 0;
		}
		else
		{
			frame->sideDistY += frame->deltaDistY;
			frame->mapY += frame->stepY;
			frame->side = 1;
		}
		if(data->settings.map[(int)frame->mapY][(int)frame->mapX] == '1')
			frame->hit = 1;
	}
	if(frame->side == 0)
		frame->perpWallDist = (frame->mapX - data->frame.posX +
				(1 - frame->stepX)/2)/ frame->rayX ;
	else
		frame->perpWallDist = (frame->mapY - data->frame.posY +
				(1 - frame->stepY)/2)/ frame->rayY;
}

	void
set_ray(t_data *data, t_frame *frame, int x)
{
	frame->mapX = (int)frame->posX;
	frame->mapY = (int)frame->posY;
	frame->cameraX = 2 * x /(double)data->settings.win_width - 1;
	frame->rayX = frame->dirX + frame->planeX * frame->cameraX;
	frame->rayY = frame->dirY + frame->planeY * frame->cameraX;
	frame->deltaDistX = (frame->rayY == 0) ?
		0 : ((frame->rayX == 0) ? 1 : fabs(1 / frame->rayX));
	frame->deltaDistY = (frame->rayX == 0) ?
		0 : ((frame->rayY == 0) ? 1 : fabs(1 / frame->rayY));
	if (frame->rayX < 0)
		frame->stepX = -1;
	else
		frame->stepX = 1;
	if (data->frame.rayY < 0)
		frame->stepY = -1;
	else
		frame->stepY = 1;
	if (frame->rayX < 0)
		frame->sideDistX = (frame->posX - frame->mapX) * frame->deltaDistX;
	else
		frame->sideDistX = (frame->mapX + 1.0 - frame->posX) * frame->deltaDistX;
	if (data->frame.rayY < 0)
		frame->sideDistY = (frame->posY - frame->mapY) * frame->deltaDistY;
	else
		frame->sideDistY = (frame->mapY + 1.0 - frame->posY) * frame->deltaDistY;
}
