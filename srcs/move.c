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

	void
move_forward(t_frame *frame, char **map)
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

	void
move_backward(t_frame *frame, char **map)
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

	void
move_right(t_frame *frame, char **map)
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

	void
move_left(t_frame *frame, char **map)
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
