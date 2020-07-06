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

#include "cub3d_bonus.h"

	int
img_color(int *colors, int pxl_x, int pxl_y, t_int size)
{
	if (pxl_x >= size.x && pxl_y >= size.y)
		return (GREY);
	else if (pxl_x < 0 && pxl_y < 0)
		return (BLUE);
	else if (pxl_x >= size.x)
		return (RED);
	else if (pxl_y >= size.y)
		return (DARK_GREY);
	else if (pxl_x < 0)
		return (ORANGE);
	else if (pxl_y < 0)
		return (GREEN);
	else
		return (colors[size.x * pxl_y + pxl_x]);
}

	unsigned char
*int_to_rgb(unsigned char *copy, int color)
{
	int	blue;
	int	green;
	int	red;

	blue = color % 256;
	green = ((color - blue) / 256) % 256;
	red = ((color - blue) / (256 * 256)) - green / 256;
	copy[0] = (unsigned char)blue;
	copy[1] = (unsigned char)green;
	copy[2] = (unsigned char)red;
	copy[3] = (unsigned char)0;
	return (copy);
}

