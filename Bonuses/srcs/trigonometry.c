/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/03/12 12:15:52 by amartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	t_dbl
rotate_point(double angle, t_dbl *ctr_ptr, t_dbl *old_ptr)
{
	t_dbl	new;
	t_dbl	ctr;
	t_dbl	old;

	if (ctr_ptr == NULL)
	{
		ctr.x = 0;
		ctr.y = 0;
	}
	else
		ctr = *ctr_ptr;
	if (old_ptr == NULL)
	{
		old.x = 1;
		old.y = 0;
	}
	else
		old = *old_ptr;
	new.x = ctr.x;
	new.x += (cos(angle) * (old.x - ctr.x) - sin(angle) * (old.y - ctr.y));
	new.y = ctr.y;
	new.y += (sin(angle) * (old.x - ctr.x) + cos(angle) * (old.y - ctr.y));
	return (new);
}
