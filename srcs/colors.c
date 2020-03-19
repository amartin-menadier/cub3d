/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:06:30 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 11:52:48 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_color(t_data *data, char *line, char *color)
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
		data->settings.Floor_color = rgb;
	else if (!ft_strncmp(color, "C ", 2))
		data->settings.Ceiling_color = rgb;
	free(tmp);
	tmp = NULL;
}
