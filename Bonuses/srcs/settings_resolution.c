/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:06:30 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 11:52:48 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	void
get_resolution(t_data *data, char *line)
{
	int	i;
	i = 1;
	data->win.size.x = 0;
	data->win.size.y = 0;
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		data->win.size.x = (data->win.size.x * 10) + (line[i++] - '0');
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		data->win.size.y = (data->win.size.y * 10) + (line[i++] - '0');
	while (line[i] == ' ')
		i++;
	if (line[i])
		close_program(data, "Wrong resolution in .cub file\n", "");
	if (data->win.size.x < 50 || data->win.size.y < 50)
		close_program(data, "Resolution is too small\n", "");
	if (data->win.size.x > 2560)
		data->win.size.x = 2560;
	if (data->win.size.y > 1440)
		data->win.size.y = 1440;
}
