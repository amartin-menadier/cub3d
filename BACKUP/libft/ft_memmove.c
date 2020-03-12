/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:19:34 by amartin-          #+#    #+#             */
/*   Updated: 2019/10/22 14:54:45 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*copydst;
	const unsigned char	*copysrc;

	copydst = (unsigned char *)dst;
	copysrc = (unsigned char *)src;
	if (dst == src)
		return (dst);
	if (copysrc > copydst)
		ft_memcpy(dst, src, n);
	else
	{
		while (n > 0)
		{
			copydst[n - 1] = copysrc[n - 1];
			n--;
		}
	}
	return (dst);
}
