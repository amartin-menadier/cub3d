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

void	fill_resolution(t_data *data, char *line, t_settings *settings)
{
	int	i;
	i = 1;
	settings->win_width = 0;
	settings->win_height = 0;
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		settings->win_width = (settings->win_width * 10) + (line[i++] - '0');
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		settings->win_height = (settings->win_height * 10) + (line[i++] - '0');
	while (line[i] == ' ')
		i++;
	if (line[i])
		close_program(data, "Wrong resolution in .cub file\n", "");
	if (settings->win_width < 50 || settings->win_height < 50)
		close_program(data, "Resolution is too small\n", "");
	if (settings->win_width > 2560)
		settings->win_width = 2560;
	if (settings->win_height > 1440)
		settings->win_height = 1440;
}
