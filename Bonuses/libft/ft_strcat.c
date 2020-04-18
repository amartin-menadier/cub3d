/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 19:27:22 by amartin-          #+#    #+#             */
/*   Updated: 2019/10/21 15:17:54 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, char *src)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	len;
	char			*output;

	len = ft_strlen(dst) + ft_strlen(src);
	if ((output = malloc(sizeof(char) * (len + 1))) == 0)
		return (NULL);
	i = 0;
	while (i < ft_strlen(dst) && dst[i] != '\0')
	{
		output[i] = dst[i];
		i++;
	}
	j = 0;
	while (i < len && src[j] != '\0')
	{
		output[i] = src[j];
		i++;
		j++;
	}
	while (i <= len)
		output[i++] = '\0';
	return (output);
}
