/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:07:21 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/19 20:56:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlengnl(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_substrgnl(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (!(sub = malloc(sizeof(char) * len + 1)))
		return (0);
	while (s[start] && i < len)
		sub[i++] = s[start++];
	sub[i] = 0;
	return (sub);
}

char	*ft_strdupgnl(const char *src)
{
	char	*str2;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (!(str2 = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	while (src[i])
	{
		str2[i] = src[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}

char	*ft_strjoingnl(char **s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char*)malloc(
			sizeof(**s1) * (ft_strlengnl(*s1) + ft_strlengnl(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while ((*s1)[i])
	{
		str[j++] = (*s1)[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i];
		i++;
	}
	str[j] = 0;
	free(*s1);
	*s1 = str;
	return (str);
}

char	*ft_strchrgnl(const char *str, int c)
{
	int		i;
	char	*str2;

	i = 0;
	str2 = (char *)str;
	while (str2[i] != c && str2[i])
		i++;
	if (str2[i] == '\0')
	{
		if (c != '\0')
			return (NULL);
	}
	return (&str2[i]);
}
