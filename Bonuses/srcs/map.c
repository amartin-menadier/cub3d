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

	double
get_first_angle(char c)
{
	double	angle;
	
	if (c == 'E')
		angle = 0;
	if (c == 'N')
		angle = PI / 2;
	if (c == 'W')
		angle = PI;
	if (c == 'S')
		angle = 3 * PI / 2;
	return (angle);
}

	int
is_map(t_data *data, t_set *set, int x, int y)
{
	char	c;

	c = set->map[y][x];
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
		if (set->angle < 0)
		{
			set->pos.x = 1.0 * x + 0.5;
			set->pos.y = 1.0 * y + 0.5;
			set->angle = get_first_angle(c);
			set->map[y][x] = '0';
		}
		else if (x != (int)set->pos.x || y != (int)set->pos.y)
			close_program(data, "More than one player set", "");
		return (4);
	}
	return (0);
}

	int
check_map_errors(t_data *data, t_set *set)
{
	int x;
	int y;

	y = 0;
	while (y < set->map_size.y)
	{
		x = 0;
		while (x < (int)ft_strlen(set->map[y]))
		{
			if ((y == 0 || y == (set->map_size.y - 1))
				&& is_map(data, set, x, y) > 2)
				close_program(data, "Map not closed at top or bottom", "");
			if (!is_map(data, set, x, y))
				close_program(data, "Wrong object in map", "");
			if (is_map(data, set, x, y) >= 3)
				check_cell_neighbors(data, set, x, y);
			x++;
		}
		y++;
	}
	if (set->angle == -1)
		close_program(data, "No map or no player set :'(", "");
	return(0);
}

	void
check_cell_neighbors(t_data *data, t_set *set, int x, int y)
{
	int i;
	int j;

	if (set->map[y][x] >= '2' && set->map[y][x] <= '9')
		set->spr_count++;
	i = x - 1;
	while (i <= x + 1)
	{
		j = y - 1;
		while (j <= y + 1)
		{
			if (set->map[j][i] == '\0' || set->map[j][i] == ' ')
				close_program(data, "Map not closed", "");
			if (!is_map(data, set, i, j))
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
**get_tmp_map(t_data *data, t_set *set, char **tmp, char *line)
{
	int i;

	i = 0;
	if (!(tmp = malloc(sizeof(char**) * (set->map_size.y + 1))))
		close_program(data, "Failed allocating memory for tmp map\n", "");
//	tmp[0] = NULL;
	while (i < set->map_size.y + 1)
	{
		if (!(tmp[i] = malloc(sizeof(char*) * (set->map_size.x + 1))))
			close_program(data, "Failed allocating memory for tmp map\n", "");
		if (i != 0)
		//(set->map_size.y))
			tmp[i] = ft_strcharcpy
				(tmp[i], set->map[i - 1], set->map_size.x, ' ');
		else
			tmp[i] = ft_strcharcpy(tmp[i], line, set->map_size.x, ' ');
		i++;
	}
	return (tmp);
}

	void
get_map(t_data *data, char *line, int i, t_set *set)
{
	char	**tmp;

	if (set->map_size.x < (int)ft_strlen(line))
		set->map_size.x = ft_strlen(line);
	i = 0;
	tmp = NULL;
	tmp = get_tmp_map(data, set, tmp, line);
	free_map(set->map, set->map_size.y);
	set->map_size.y = set->map_size.y + 1;
	i = 0;
	if (!(set->map = malloc(sizeof(char**) * set->map_size.y)))
		close_program(data, "Failed allocating memory for map\n", "");
	while (i < set->map_size.y)
	{
		if (!(set->map[i] = malloc(sizeof(char*) * set->map_size.x)))
			close_program(data, "Failed allocating memory for map\n", "");
		set->map[i] =
			ft_strcharcpy(set->map[i], tmp[i], set->map_size.x, ' ');
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	free(tmp);
	tmp = NULL;
}
