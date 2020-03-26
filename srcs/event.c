/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:42:54 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 21:56:07 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	look_left(t_frame *frame)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rotSpeed = 0.18;
	double	*PlaneX;
	double	*PlaneY;

	PlaneX = &frame->planeX;
	PlaneY = &frame->planeY;
	oldDirX = frame->dirX;
	frame->dirX = oldDirX * cos(-rotSpeed) - frame->dirY * sin(-rotSpeed);
	frame->dirY = oldDirX * sin(-rotSpeed) + frame->dirY * cos(-rotSpeed);
	oldPlaneX = frame->planeX;
	*PlaneX = oldPlaneX * cos(-rotSpeed) - frame->planeY * sin(-rotSpeed);
	*PlaneY = oldPlaneX * sin(-rotSpeed) + frame->planeY * cos(-rotSpeed);
}

void	look_right(t_frame *frame)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rotSpeed = 0.18;
	double	*PlaneX;
	double	*PlaneY;

	PlaneX = &frame->planeX;
	PlaneY = &frame->planeY;
	oldDirX = frame->dirX;
	frame->dirX = frame->dirX * cos(rotSpeed) - frame->dirY * sin(rotSpeed);
	frame->dirY = oldDirX * sin(rotSpeed) + frame->dirY * cos(rotSpeed);
	oldPlaneX = frame->planeX;
	*PlaneX = frame->planeX * cos(rotSpeed) - frame->planeY * sin(rotSpeed);
	*PlaneY = oldPlaneX * sin(rotSpeed) + frame->planeY * cos(rotSpeed);
}

void	move_forward(t_frame *frame, char **map)
{
	double	moveSpeed = 0.33;
	double	*posX;
	double	*posY;

	posX = &frame->posX;
	posY = &frame->posY;
	if(map[(int)*posY][(int)(*posX + frame->dirX * moveSpeed)] != 49)
		*posX += frame->dirX * moveSpeed;
	if(map[(int)(*posY + frame->dirY * moveSpeed)][(int)*posX] != 49)
		*posY += frame->dirY * moveSpeed;
}

void	move_backward(t_frame *frame, char **map)
{
	double	moveSpeed = 0.33;
	int		posX;
	int		posY;

	posX = (int)frame->posX;
	posY = (int)frame->posY;
	if(map[posY][(int)(frame->posX - frame->dirX * moveSpeed)] != 49)
		frame->posX -= frame->dirX * moveSpeed;
	if(map[(int)(frame->posY - frame->dirY * moveSpeed)][posX] != 49)
		frame->posY -= frame->dirY * moveSpeed;
}

void	move_right(t_frame *frame, char **map)
{
	double	moveSpeed = 0.33;
	int		posX;
	int		posY;

	posX = (int)frame->posX;
	posY = (int)frame->posY;
	if(map[posY][(int)(frame->posX - frame->dirY * moveSpeed)] != 49)
		frame->posX -= frame->dirY * moveSpeed;
	if(map[(int)(frame->posY + frame->dirX * moveSpeed)][posX] != 49)
		frame->posY += frame->dirX * moveSpeed;
}

void	move_left(t_frame *frame, char **map)
{
	double	moveSpeed = 0.33;
	int		posX;
	int		posY;

	posX = (int)frame->posX;
	posY = (int)frame->posY;
	if(map[posY][(int)(frame->posX + frame->dirY * moveSpeed)] != 49)
		frame->posX += frame->dirY * moveSpeed;
	if(map[(int)(frame->posY - frame->dirX * moveSpeed)][posX] != 49)
		frame->posY -= frame->dirX * moveSpeed;
}

int		presskey(int keycode, t_data *data)
{
	printf("\nCMD = >%d<\n", keycode);//a supprimer a terme
	if (keycode == ESC)
		close_program(data, "\nEverything went well ! ", "\\o/\n");
	if (keycode == LOOK_LEFT)
		look_left(&data->frame);
	if (keycode == LOOK_RIGHT)
		look_right(&data->frame);
	if (keycode == MOVE_FORWARD)
		move_forward(&data->frame, data->settings.map);
	if (keycode == MOVE_BACKWARD)
		move_backward(&data->frame, data->settings.map);
	if (keycode == MOVE_RIGHT)
		move_right(&data->frame, data->settings.map);
	if (keycode == MOVE_LEFT)
		move_left(&data->frame, data->settings.map);
	data->frame.sprites_sorted = 0;
	print_map(data);// a supprimer a terme
	print_image(data);
//	print_sprites(data);
	int i=0;//a supprimer a terme

	while (i < data->settings.numSprites)
	{
		data->settings.spritetext[i] = '2';
		i++;
	}
//	sort_sprites(data, &data->settings, &data->frame);
//	ft_putstr_fd("\nNB : sprites may be not sorted after key event and before main loop", 1);
//	print_sprites(data);
//	print_Zbuffer(data);
	return (keycode);
}

int		red_cross(t_data *data)
{
	close_program(data, "\nEverything went well ! ", "\\o/\n");
	return (0);
}

void	hook_event(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, presskey, data);
	//	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_hook(data->win, 17, 1L << 17, red_cross, data);
	return ;
}
