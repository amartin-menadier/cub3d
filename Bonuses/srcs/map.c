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
	if (c >= '2' && c <= '9')
		return (3);
	if (c == '0')
		return (3);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (settings->player_orientation == (char)NULL)
		{
			settings->player_orientation = c;
			settings->starting_pos.x = x;
			settings->starting_pos.y = y;
		}
		else if (x != settings->starting_pos.x || y != settings->starting_pos.y)
		{
			printf("\n--");
			printf("\n--");
			printf("\n--");
			printf("\n--");
			ft_putnbr_fd(x, 1);
			printf("\n--");
			ft_putnbr_fd(y, 1);
			printf("\n--");
			ft_putnbr_fd(settings->starting_pos.x, 1);
			printf("\n--");
			ft_putnbr_fd(settings->starting_pos.y, 1);
			printf("\n--");
			close_program(data, "More than one player set", "");
			}
		return (4);
	}
	return (0);
}

	int
check_map_errors(t_data *data, t_settings *settings)
{
	int x;
	int y;

//		if (settings->player_orientation != (char)NULL)
//		settings->map[settings->starting_pos.y]
//		[settings->starting_pos.x] = settings->player_orientation;
	y = 0;
	while (y < settings->map_size.y)
	{
		x = 0;
		while (x < (int)ft_strlen(settings->map[y]))
		{
			if ((y == 0 || y == (settings->map_size.y - 1))
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
		settings->spr_count++;
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
** NB : map_size.y has not yet been incremented in fill_tmp hence +1 each time
*/

	char
**get_tmp_map(t_data *data, t_settings *settings, char **tmp, char *line)
{
	int i;

	i = 0;
	if (!(tmp = malloc(sizeof(char**) * (settings->map_size.y + 1))))
		close_program(data, "Failed allocating memory for tmp map\n", "");
	while (i < settings->map_size.y + 1)
	{
		if (!(tmp[i] = malloc(sizeof(char*) * (settings->map_size.x + 1))))
			close_program(data, "Failed allocating memory for tmp map\n", "");
		if (i != (settings->map_size.y))
			tmp[i] = ft_strcharcpy
				(tmp[i], settings->map[i], settings->map_size.x, ' ');
		else
			tmp[i] = ft_strcharcpy(tmp[i], line, settings->map_size.x, ' ');
		i++;
	}
	return (tmp);
}

	void
get_map(t_data *data, char *line, int i, t_settings *settings)
{
	char	**tmp;

	if (settings->map_size.x < (int)ft_strlen(line))
		settings->map_size.x = ft_strlen(line);
	i = 0;
	tmp = NULL;
	tmp = get_tmp_map(data, settings, tmp, line);
	free_map(settings);
	settings->map_size.y = settings->map_size.y + 1;
	i = 0;
	if (!(settings->map = malloc(sizeof(char**) * settings->map_size.y)))
		close_program(data, "Failed allocating memory for map\n", "");
	while (i < settings->map_size.y)
	{
		if (!(settings->map[i] = malloc(sizeof(char*) * settings->map_size.x)))
			close_program(data, "Failed allocating memory for map\n", "");
		settings->map[i] =
			ft_strcharcpy(settings->map[i], tmp[i], settings->map_size.x, ' ');
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	free(tmp);
	tmp = NULL;
}
