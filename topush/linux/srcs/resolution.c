/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadier <amenadier@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:30:34 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/12 14:45:26 by amenadier        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	get_res_size(char *line, int *size)
{
	int	len;

	len = 0;
	while (line[len] && ft_isdigit(line[len]))
	{
		if (len < 9)
			*size = (*size * 10) + (line[len] - '0');
		else
			*size = 1000000;
		len++;
	}
	while (line[len] && line[len] == ' ')
		len++;
	return (len);
}

void
	get_resolution(t_data *data, char *line, t_settings *settings)
{
	int	i;

	i = 1;
	settings->win_size.x = 0;
	settings->win_size.y = 0;
	while (line[i] && line[i] == ' ')
		i++;
	i += get_res_size(&line[i], &settings->win_size.x);
	i += get_res_size(&line[i], &settings->win_size.y);
	if (line[i])
		close_program(data, "Wrong resolution in .cub file\n", "");
	if (settings->win_size.x < 50 || settings->win_size.y < 50)
		close_program(data, "Resolution is too small\n", "");
	if (settings->win_size.x > 1400)
		settings->win_size.x = 1400;
	if (settings->win_size.y > 800)
		settings->win_size.y = 800;
}
