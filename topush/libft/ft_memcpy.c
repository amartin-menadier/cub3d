/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:20:07 by amartin-          #+#    #+#             */
/*   Updated: 2019/10/22 14:53:20 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*copydst;
	char	*copysrc;

	copydst = (char *)dst;
	copysrc = (char *)src;
	if (copydst == copysrc)
		return (copydst);
	i = 0;
	while (i != n)
	{
		copydst[i] = copysrc[i];
		i++;
	}
	return (dst);
}
