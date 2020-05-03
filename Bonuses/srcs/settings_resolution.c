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
get_resolution(t_data *data, char *line, t_set *set)
{
	int	i;
	i = 1;
	set->win_size.x = 0;
	set->win_size.y = 0;
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		set->win_size.x = (set->win_size.x * 10) + (line[i++] - '0');
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		set->win_size.y = (set->win_size.y * 10) + (line[i++] - '0');
	while (line[i] == ' ')
		i++;
	if (line[i])
		close_program(data, "Wrong resolution in .cub file\n", "");
	if (set->win_size.x < 50 || set->win_size.y < 50)
		close_program(data, "Resolution is too small\n", "");
	if (set->win_size.x > 2560)
		set->win_size.x = 2560;
	if (set->win_size.y > 1440)
		set->win_size.y = 1440;
}
