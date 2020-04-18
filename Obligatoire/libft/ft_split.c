/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:33:33 by amartin-          #+#    #+#             */
/*   Updated: 2019/10/22 12:33:38 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_tab(char const *str, char c)
{
	int i;
	int	count_tab;

	i = 0;
	count_tab = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			count_tab++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count_tab);
}

static char	*ft_strdupspec(char const *str, char c)
{
	char	*dest;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	if (!(dest = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	dest = ft_strncpy(dest, str, i);
	return (dest);
}

char		**ft_split(char const *str, char c)
{
	int		i;
	int		k;
	char	**tab;

	if (!(tab = (char**)malloc(sizeof(char*) * (ft_size_tab(str, c) + 1)))
			|| !str)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i] && k < ft_size_tab(str, c))
	{
		while (str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			tab[k] = ft_strdupspec(str + i, c);
			k++;
		}
		while (str[i] && str[i] != c)
			i++;
	}
	tab[k] = 0;
	return (tab);
}
