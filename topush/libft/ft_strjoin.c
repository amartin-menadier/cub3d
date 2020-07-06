/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 19:35:09 by amartin-          #+#    #+#             */
/*   Updated: 2019/10/22 18:09:42 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		str1_len;
	int		str2_len;
	char	*str;
	int		i;

	str1_len = ft_strlen((char *)s1);
	str2_len = ft_strlen((char *)s2);
	if (!(str = malloc(sizeof(char) * (str1_len + str2_len) + 1)))
		return (0);
	i = 0;
	str1_len = 0;
	str2_len = 0;
	while (s1[str1_len])
		str[i++] = s1[str1_len++];
	while (s2[str2_len])
		str[i++] = s2[str2_len++];
	str[i] = 0;
	return (str);
}
