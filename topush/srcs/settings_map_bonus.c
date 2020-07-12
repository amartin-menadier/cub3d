/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadier <amenadier@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 14:44:51 by amenadier         #+#    #+#             */
/*   Updated: 2020/07/12 14:45:03 by amenadier        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int
	is_map(t_data *data, int x, int z)
{
	char	c;

	c = data->map[z][x];
	if (c == ' ')
		return (1);
	if (c == '1')
		return (2);
	if (c >= '2' && c <= '9')
		return (3);
	if (c == '0')
		return (3);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (data->angle.x < 0)
		{
			data->cam.x = 1.0 * x + 0.5;
			data->cam.z = 1.0 * z + 0.5;
			data->angle = get_first_angle(c);
			data->map[z][x] = '0';
		}
		else if (x != (int)data->cam.x || z != (int)data->cam.z)
			close_program(data, "More than one player data", "");
		return (4);
	}
	return (0);
}

int
	check_map_errors(t_data *data)
{
	int x;
	int z;

	z = 0;
	while (z < data->map_size.z)
	{
		x = 0;
		while (x < (int)ft_strlen(data->map[z]))
		{
			if ((z == 0 || z == (data->map_size.z - 1))
				&& is_map(data, x, z) > 2)
				close_program(data, "Map not closed at top or bottom", "");
			if (!is_map(data, x, z))
				close_program(data, "Wrong object in map", "");
			if (is_map(data, x, z) >= 3)
				check_cell_neighbors(data, x, z);
			x++;
		}
		z++;
	}
	if (data->angle.x == -1)
		close_program(data, "No map or no player data :'(", "");
	return (0);
}

void
	check_cell_neighbors(t_data *data, int x, int z)
{
	int i;
	int j;

	if (data->map[z][x] >= '2' && data->map[z][x] <= '9')
		data->spr_count++;
	i = x - 1;
	while (i <= x + 1)
	{
		j = z - 1;
		while (j <= z + 1)
		{
			if (data->map[j][i] == '\0' || data->map[j][i] == ' ')
				close_program(data, "Map not closed", "");
			if (!is_map(data, i, j))
				close_program(data, "Wrong object in map", "");
			j++;
		}
		i++;
	}
}

/*
** NB : map_size.y has not yet been incremented in fill_tmp hence +1 each time
*/

char
	**get_tmp_map(t_data *data, char **tmp, char *line)
{
	int i;

	i = 0;
	if (!(tmp = malloc(sizeof(char**) * (data->map_size.z + 1))))
		close_program(data, "Failed allocating memory for tmp map\n", "");
	while (i < data->map_size.z + 1)
	{
		if (!(tmp[i] = malloc(sizeof(char*) * (data->map_size.x + 1))))
			close_program(data, "Failed allocating memory for tmp map\n", "");
		if (i != 0)
			tmp[i] = 
				ft_strcharcpy(tmp[i], data->map[i - 1], data->map_size.x, ' ');
		else
			tmp[i] = ft_strcharcpy(tmp[i], line, data->map_size.x, ' ');
		i++;
	}
	return (tmp);
}

void
	get_map(t_data *data, char *line, int i)
{
	char	**tmp;

	if (data->map_size.x < (int)ft_strlen(line))
		data->map_size.x = ft_strlen(line);
	tmp = NULL;
	tmp = get_tmp_map(data, tmp, line);
	free_map(NULL, data->map, data->map_size.z);
	data->map_size.z = data->map_size.z + 1;
	i = 0;
	if (!(data->map = malloc(sizeof(char**) * data->map_size.z)))
		close_program(data, "Failed allocating memory for map\n", "");
	while (i < data->map_size.z)
	{
		if (!(data->map[i] = malloc(sizeof(char*) * data->map_size.x)))
			close_program(data, "Failed allocating memory for map\n", "");
		data->map[i] =
			ft_strcharcpy(data->map[i], tmp[i], data->map_size.x, ' ');
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	free(tmp);
	tmp = NULL;
}
