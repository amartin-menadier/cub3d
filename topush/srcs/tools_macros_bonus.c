/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_macros_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/20 17:40:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int
	is_look(int key)
{
	if (key == LEFT || key == RIGHT || key == DOWN || key == UP)
		return (1);
	else
		return (0);
}

int
	is_move(int key)
{
	if (key == Z || key == Q || key == S || key == D
		|| key == SPACE || key == V)
		return (1);
	else
		return (0);
}

int
	is_wall(char map_element)
{
	if (map_element == '1' || (map_element >= '6' && map_element <= '9'))
		return (1);
	else
		return (0);
}

int
	is_obstacle(char map_element)
{
	if (map_element == '1' || map_element == '4')
		return (1);
	else
		return (0);
}
