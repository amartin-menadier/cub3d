/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:55:24 by amartin-          #+#    #+#             */
/*   Updated: 2019/10/22 15:44:11 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (count == 0 || size == 0)
		if (!(ptr = malloc(1)))
			return (0);
	if (!(ptr = malloc(size * count)))
		return (0);
	while (i < (size * count))
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
