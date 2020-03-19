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

int		presskey(int keycode, t_data *data)
{
	double	oldDirX;
	double oldPlaneX;
	double	rotSpeed = 0.18;
	double	moveSpeed = 0.33;
	t_frame	*frame;

	frame = &data->frame;
	data->keycode = keycode;
	//	render_next_frame(data); //possibilite d'utliser cela si loop_hook non utilise dans hook_event mais les images se chevauchent...
	printf("\nCMD = >%d<\n", keycode);
	if (keycode == ESC)
		close_program(data, "\nEverything went well ! ", "\\o/\n");
	if (keycode == LOOK_LEFT)
	{
		oldDirX = frame->dirX;
		frame->dirX = frame->dirX * cos(-rotSpeed) - frame->dirY * sin(-rotSpeed);
		frame->dirY = oldDirX * sin(-rotSpeed) + frame->dirY * cos(-rotSpeed);
		oldPlaneX = frame->planeX;
		frame->planeX = frame->planeX * cos(-rotSpeed) - frame->planeY * sin(-rotSpeed);
		frame->planeY = oldPlaneX * sin(-rotSpeed) + frame->planeY * cos(-rotSpeed);
	}
	if (keycode == LOOK_RIGHT)
	{
		oldDirX = frame->dirX;
		frame->dirX = frame->dirX * cos(rotSpeed) - frame->dirY * sin(rotSpeed);
		frame->dirY = oldDirX * sin(rotSpeed) + frame->dirY * cos(rotSpeed);
		oldPlaneX = frame->planeX;
		frame->planeX = frame->planeX * cos(rotSpeed) - frame->planeY * sin(rotSpeed);
		frame->planeY = oldPlaneX * sin(rotSpeed) + frame->planeY * cos(rotSpeed);
	}
	if (keycode == MOVE_FORWARD)
	{
		if(data->settings.map[(int)data->frame.posY][(int)(data->frame.posX + frame->dirX * moveSpeed)] != 49)
			data->frame.posX += frame->dirX * moveSpeed;
		if(data->settings.map[(int)(data->frame.posY + frame->dirY * moveSpeed)][(int)(data->frame.posX)] != 49)
			data->frame.posY += frame->dirY * moveSpeed;
	}
	if (keycode == MOVE_BACKWARD)
	{
		if(data->settings.map[(int)data->frame.posY][(int)(data->frame.posX - frame->dirX * moveSpeed)] != 49)
			data->frame.posX -= frame->dirX * moveSpeed;
		if(data->settings.map[(int)(data->frame.posY - frame->dirY * moveSpeed)][(int)data->frame.posX] != 49)
			data->frame.posY -= frame->dirY * moveSpeed;
	}
	if (keycode == MOVE_RIGHT)
	{
		if(data->settings.map[(int)data->frame.posY][(int)(data->frame.posX - frame->dirY * moveSpeed)] != 49)
			data->frame.posX -= frame->dirY * moveSpeed;
		if(data->settings.map[(int)(data->frame.posY + frame->dirX * moveSpeed)][(int)data->frame.posX] != 49)
			data->frame.posY += frame->dirX * moveSpeed;
	}
	if (keycode == MOVE_LEFT)
	{
		if(data->settings.map[(int)data->frame.posY][(int)(data->frame.posX + frame->dirY * moveSpeed)] != 49)
			data->frame.posX += frame->dirY * moveSpeed;
		if(data->settings.map[(int)(data->frame.posY - frame->dirX * moveSpeed)][(int)data->frame.posX] != 49)
			data->frame.posY -= frame->dirX * moveSpeed;
	}
	/*
	//move backwards if no wall behind you
	if (keyDown(SDLK_DOWN))
	{
	if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
	if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
	}
	//	if (keycode == LOOK_RIGHT)
	//		close_program(data, "\nEverything went well ! ", "\\o/\n");
	*/
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
				printf("R%c", data->settings.map[i][j]);
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
	//	printf("\nMap_height = %d", data->settings.win_height);
	printf("\npos_x = %f", data->frame.posX);
	printf("\npos_y = %f", data->frame.posY);
	printf("\nPlayer is located at (%f,%f)", data->frame.posX, data->frame.posY);
	printf("\ndirX = %f", data->frame.dirX);
	printf("\ndirY = %f", data->frame.dirY);
	printf("\nmapX = %f", data->frame.mapX);
	printf("\nmapY = %f", data->frame.mapY);
	printf("\nmap(mapY;mapX) (//!\\\\char) = %c", data->settings.map[(int)data->frame.mapY][(int)data->frame.mapX]);
	printf("\nrayX = %f", data->frame.rayX);
	printf("\nrayY = %f", data->frame.rayY);
	printf("\ndeltaDistX = %f", data->frame.deltaDistX);
	printf("\ndeltaDistY = %f", data->frame.deltaDistY);
	printf("\nsideDistX = %f", data->frame.sideDistX);
	printf("\nsideDistY = %f", data->frame.sideDistY);
	printf("\nstepX = %d", data->frame.stepX);
	printf("\nstepY = %d", data->frame.stepY);
	printf("\nside = %d", data->frame.side);
	printf("\nperpWallDist = %f", data->frame.perpWallDist);
	printf("\nlineHeight = %d", data->frame.lineHeight);
	printf("\n");
	return (keycode);
}

int		red_cross(t_data *data)
{
	//	print_params(data);
	close_program(data, "\nEverything went well ! ", "\\o/\n");
	return (0);
}

void	hook_event(t_data *data)
{
	//	ft_putstr_fd("\nI GET INTO HOOK EVENT", 1);
	mlx_hook(data->win, 2, 1L << 0, presskey, data);
	//	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_hook(data->win, 17, 1L << 17, red_cross, data);
	return ;
}
