/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:30:34 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/23 20:03:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	check_resolution(t_data *data, t_settings *settings)
{
	int	x_max;
	int y_max;

	mlx_get_screen_size(data->mlx, &x_max, &y_max);
	if (settings->win_size.x > x_max)
		settings->win_size.x = x_max;
	if (settings->win_size.y > y_max)
		settings->win_size.y = y_max;
}

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
		close_program(data, "Wrong resolution format\n", "");
	if (settings->win_size.x < 1 || settings->win_size.y < 1)
		close_program(data, "Wrong resolution format\n", "");
}
