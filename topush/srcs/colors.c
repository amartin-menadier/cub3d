/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadier <amenadier@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 14:19:09 by amenadier         #+#    #+#             */
/*   Updated: 2020/07/12 14:48:05 by amenadier        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned char
	*int_to_rgb(unsigned char *image, int color)
{
	int	blue;
	int	green;
	int	red;

	blue = color % 256;
	green = ((color - blue) / 256) % 256;
	red = ((color - blue) / (256 * 256)) - green / 256;
	image[0] = (unsigned char)blue;
	image[1] = (unsigned char)green;
	image[2] = (unsigned char)red;
	image[3] = (unsigned char)0;
	return (image);
}

void
	get_color(t_data *data, char *line, char *color)
{
	char	*tmp;
	int		rgb;

	if (!(tmp = ft_strtrim(&line[2], " ")))
		close_program(data, "Failed allocating memory for color ", color);
	if ((rgb = get_rgb_from_string(tmp)) == -1)
	{
		free(tmp);
		tmp = NULL;
		close_program(data, "Wrong color format - check ", color);
	}
	else if (!ft_strncmp(color, "F ", 2))
		data->settings.floor_color = rgb;
	else if (!ft_strncmp(color, "C ", 2))
		data->settings.ceiling_color = rgb;
	free(tmp);
	tmp = NULL;
}
