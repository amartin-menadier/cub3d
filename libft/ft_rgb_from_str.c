/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_from_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:15:41 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/07 02:03:12 by amartin-         ###   ########.fr       */
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
	if ((i = check_between(string, i, 0)) == -1)
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
