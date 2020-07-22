/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_resolution_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:30:34 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/20 17:37:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

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
	if (data->win.size.x > 1400)
		data->win.size.x = 1400;
	if (data->win.size.y > 800)
		data->win.size.y = 800;
}
