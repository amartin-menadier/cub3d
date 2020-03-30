/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:06:30 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 11:52:48 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


	int
is_map(t_data *data, t_settings *settings, int x, int y)
{
	char c;

	c = settings->map[y][x];
	if (c == ' ')
		return (1);
	if (c == '1')
		return (2);
	if (c == '2')
		return (3);
	if (c == '0')
		return (3);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (settings->player_orientation == (char)NULL)
		{
			settings->player_orientation = c;
			settings->init_posX = x;
			settings->init_posY = y;
		}
		else if (x != settings->init_posX || y != settings->init_posY)
			close_program(data, "More than one player set", "");
		return (4);
	}
	return (0);
}

	int
check_map_errors(t_data *data, t_settings *settings)
{
	int x;
	int y;

	y = 0;
	while (y < settings->map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(settings->map[y]))
		{
			if ((y == 0 || y == (settings->map_height - 1))
				&& is_map(data, settings, x, y) > 2)
				close_program(data, "Map not closed at top or bottom", "");
			if (!is_map(data, settings, x, y))
				close_program(data, "Wrong object in map", "");
			if (is_map(data, settings, x, y) >= 3)
				check_square_neighbors(data, settings, x, y);
			x++;
		}
		y++;
	}
	if (settings->player_orientation == (char)NULL)
		close_program(data, "No map or no player set :'(", "");
	return(0);
}

	void
check_square_neighbors(t_data *data, t_settings *settings, int x, int y)
{
	int i;
	int j;

	if (settings->map[y][x] >= '2' && settings->map[y][x] <= '9')
		settings->numSprites++;
	i = x - 1;
	while (i <= x + 1)
	{
		j = y - 1;
		while (j <= y + 1)
		{
			if (settings->map[j][i] == '\0' || settings->map[j][i] == ' ')
				close_program(data, "Map not closed", "");
			if (!is_map(data, settings, i, j))
				close_program(data, "Wrong object in map", "");
			j++;
		}
		i++;
	}
}

/*
// NB : map_height has not yet been incremented in fill_tmp hence +1 each time
*/

	char
**get_tmp_map(t_data *data, t_settings *settings, char **tmp, char *line)
{
	int i;

	i = 0;
	if (!(tmp = malloc(sizeof(char**) * (settings->map_height + 1))))
		close_program(data, "Failed allocating memory for tmp map\n", "");
	while (i < settings->map_height + 1)
	{
		if (!(tmp[i] = malloc(sizeof(char*) * (settings->map_width + 1))))
			close_program(data, "Failed allocating memory for tmp map\n", "");
		if (i != (settings->map_height))
			tmp[i] = ft_strcharcpy
				(tmp[i], settings->map[i], settings->map_width, ' ');
		else
			tmp[i] = ft_strcharcpy(tmp[i], line, settings->map_width, ' ');
		i++;
	}
	return (tmp);
}

	void
get_map(t_data *data, char *line, int i, t_settings *settings)
{
	char	**tmp;

	if (settings->map_width < (int)ft_strlen(line))
		settings->map_width = ft_strlen(line);
	i = 0;
	tmp = NULL;
	tmp = get_tmp_map(data, settings, tmp, line);
	free_map(settings);
	settings->map_height = settings->map_height + 1;
	i = 0;
	if (!(settings->map = malloc(sizeof(char**) * (settings->map_height))))
		close_program(data, "Failed allocating memory for map\n", "");
	while (i < settings->map_height)
	{
		if (!(settings->map[i] = malloc(sizeof(char*) * (settings->map_width))))
			close_program(data, "Failed allocating memory for map\n", "");
		settings->map[i] =
			ft_strcharcpy(settings->map[i], tmp[i], settings->map_width, ' ');
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	free(tmp);
	tmp = NULL;
}
