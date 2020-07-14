/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:52:09 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/05 15:52:21 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define SPACE(x) (x=='\t'||x=='\v'||x=='\f'||x=='\r'||x=='\n'||x==' ')

static int	whatsign(const char *str)
{
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	while (str[i] && !ft_isdigit(str[i]))
	{
		if (str[i] == '-')
			sign = -1;
		else if (str[i] == '+')
			sign = 1;
		i++;
	}
	return (sign);
}

int			ft_atoi(const char *str)
{
	int		n;
	int		i;
	int		sign;
	char	*s;

	n = 0;
	i = 0;
	s = ft_strdup(str);
	sign = (whatsign(s));
	while (SPACE(s[i]))
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (ft_isdigit(s[i]))
	{
		n *= 10;
		n += (s[i] - '0');
		i++;
	}
	free(s);
	s = NULL;
	return (n * sign);
}
