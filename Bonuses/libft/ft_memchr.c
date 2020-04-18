/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:27:53 by amartin-          #+#    #+#             */
/*   Updated: 2019/10/22 14:35:44 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*ptr;
	char	*copy;
	size_t	i;

	ptr = 0;
	copy = (char*)s;
	i = 0;
	while (i < n)
	{
		if (copy[i] == ((char)c))
		{
			ptr = &copy[i];
			return (ptr);
		}
		i++;
	}
	return (0);
}
