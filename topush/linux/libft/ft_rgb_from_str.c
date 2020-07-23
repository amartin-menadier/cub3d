/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_from_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:15:41 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/23 18:48:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_between(char *string, int i, int mod)
{
	while (string[i] == ' ')
		i++;
	if (mod == 0 && ft_isdigit(string[i]))
		return (i);
	if (mod == 2 && string[i] != '\0')
		return (-1);
	if (string[i] == ',')
		i++;
	while (string[i] == ' ')
		i++;
	if (ft_isdigit(string[i]))
		return (i);
	else
		return (i);
}

int			check_rgb_string(char *string)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	i = check_between(string, i, 0);
	if (ft_isdigit(string[i]))
		count++;
	while (ft_isdigit(string[i]))
		i++;
	i = check_between(string, i, 1);
	if (ft_isdigit(string[i]))
		count++;
	while (ft_isdigit(string[i]))
		i++;
	i = check_between(string, i, 1);
	if (ft_isdigit(string[i]))
		count++;
	if (count != 3)
		return (0);
	else
		return (1);
}

int			get_rgb_from_string(char *string)
{
	int	rgb;
	int g;
	int b;
	int i;

	rgb = 0;
	g = 0;
	b = 0;
	i = 0;
	if (!check_rgb_string(string) || (i = check_between(string, i, 0)) == -1)
		return (-1);
	while (ft_isdigit(string[i]))
		rgb = rgb * 10 + string[i++] - '0';
	if ((i = check_between(string, i, 1)) == -1)
		return (-1);
	while (ft_isdigit(string[i]))
		g = g * 10 + string[i++] - '0';
	if ((i = check_between(string, i, 1)) == -1)
		return (-1);
	while (ft_isdigit(string[i]))
		b = b * 10 + string[i++] - '0';
	if ((check_between(string, i, 2)) == -1 || rgb > 255 || g > 255 || b > 255)
		return (-1);
	return (rgb = (((rgb << 8) + g) << 8) + b);
}
