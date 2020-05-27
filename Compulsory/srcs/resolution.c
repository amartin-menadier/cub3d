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
get_resolution(t_data *data, char *line, t_settings *settings)
{
	int	i;
	i = 1;
	settings->win_size.x = 0;
	settings->win_size.y = 0;
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		settings->win_size.x = (settings->win_size.x * 10) + (line[i++] - '0');
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		settings->win_size.y = (settings->win_size.y * 10) + (line[i++] - '0');
	while (line[i] == ' ')
		i++;
	if (line[i])
		close_program(data, "Wrong resolution in .cub file\n", "");
	if (settings->win_size.x < 50 || settings->win_size.y < 50)
		close_program(data, "Resolution is too small\n", "");
	if (settings->win_size.x > 1400)
		settings->win_size.x = 1400;
	if (settings->win_size.y > 800)
		settings->win_size.y = 800;
}
