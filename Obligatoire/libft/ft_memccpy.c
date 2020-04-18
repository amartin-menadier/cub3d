/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:36:42 by amartin-          #+#    #+#             */
/*   Updated: 2019/10/21 13:37:01 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*copydst;
	unsigned char	*copysrc;

	copydst = (unsigned char*)dst;
	copysrc = (unsigned char*)src;
	while (n--)
	{
		*copydst = *copysrc;
		if (*copydst == (unsigned char)c)
			return (copydst + 1);
		copydst++;
		copysrc++;
	}
	return (NULL);
}
