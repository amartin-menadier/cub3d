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

void	draw_column(t_data *data, t_frame *frame, t_img *textimg, int x)
{
	int		y;
	double step;
	double texPos;

	y = 0;
	while (y < frame->drawStart)
		my_mlx_pixel_put(&data->img, x, y++, data->settings.Ceiling_color);
	step = 1.0 * textimg->th / frame->lineHeight;
	texPos = (frame->drawStart - data->settings.win_height / 2 +
			frame->lineHeight / 2) * step;
	while (y < frame->drawEnd)
	{
		frame->texY = (int)texPos & (textimg->th - 1);
		texPos += step;
		my_mlx_pixel_put(&data->img, x, y,
				textimg->colors[textimg->th * frame->texY + frame->texX]);
		y++;
	}
	while (y < data->settings.win_height)
		my_mlx_pixel_put(&data->img, x, y++, data->settings.Floor_color);
}

t_img	*pick_texture(t_frame *frame)
{
	t_img	*textimg;

	if (frame->side == 0)//EA and WE
	{
		if (frame->rayX >0)//EA
			textimg = &frame->EA_img;
		else//WE
			textimg = &frame->WE_img;
	}
	else
	{
		if (frame->rayY >0)//SO
			textimg = &frame->SO_img;
		else//NO
			textimg = &frame->NO_img;
	}
	frame->texX = (int)(frame->wallX * (double)textimg->tw);
	if(frame->side == 0 && frame->rayX > 0)
		frame->texX = textimg->tw - frame->texX - 1;
	if(frame->side == 1 && frame->rayY < 0)
		frame->texX = textimg->tw - frame->texX - 1;
	return (textimg);
}

void	set_drawing_limits(t_data *data, t_frame *frame)
{
	frame->lineHeight = abs((int)(data->settings.win_height / (frame->perpWallDist)));
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

void	perform_DDA(t_data *data, t_frame *frame)
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
		if(data->settings.map[(int)frame->mapY][(int)frame->mapX] > '0')
			frame->hit = 1;
	}
	if(frame->side == 0)
		frame->perpWallDist = (frame->mapX - data->frame.posX +
				(1 - frame->stepX)/2)/ frame->rayX ;
	else
		frame->perpWallDist = (frame->mapY - data->frame.posY +
				(1 - frame->stepY)/2)/ frame->rayY;
}

void	set_ray(t_data *data, t_frame *frame, int x)
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

int		render_next_frame(t_data *data)
{
	int		x;
	t_img	*textimg;

	x = 0;
	while (x < data->settings.win_width)
	{
		set_ray(data, &data->frame, x);
		perform_DDA(data, &data->frame);
		set_drawing_limits(data, &data->frame);
		textimg = pick_texture(&data->frame);
		draw_column(data, &data->frame, textimg, x);

		x++;
		t_frame *frame = &data->frame;
		if (x == 1 && frame->time == 0)
		{
			frame->time++;
			printf("\n Debut du raycasting");
			int i = 0;
			int j = 0;
			while (i < data->settings.map_height)
			{
				j = 0;
				if (i <= 9)
					printf("\nmap [ %d] : > ", i);
				else
					printf("\nmap [%d] : > ", i);
				while (j < (int)ft_strlen(data->settings.map[i]))
				{
					if (i == (int)data->frame.posY && j == (int)data->frame.posX)
					{
						if (data->frame.dirY <= 0 && (fabs(data->frame.dirY) > fabs(data->frame.dirX)))
							printf("P^");
						else if (data->frame.dirX >= 0  && (data->frame.dirX > fabs(data->frame.dirY)))
							printf("P>");
						else if (data->frame.dirY >= 0  && (data->frame.dirY > fabs(data->frame.dirX)))
							printf("Pv");
						else if (data->frame.dirX <= 0  && (fabs(data->frame.dirX) > fabs(data->frame.dirY)))
							printf("<P");
						else
							printf("ERROR");
					}
					else if (i == (int)data->frame.mapY && j == (int)data->frame.mapX)
						printf("r%c", data->settings.map[i][j]);
					else if (data->settings.map[i][j] == '0') 
						printf("  ");
					else if (data->settings.map[i][j] == '1') 
						printf("[]");
					else
						printf("%c ", data->settings.map[i][j]);

					j++;
				}
				i++;
				printf("<");
			}
		}

	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
	return (0);
}
