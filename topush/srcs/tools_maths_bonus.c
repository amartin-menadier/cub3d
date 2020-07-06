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

#include "cub3d_bonus.h"

	double
square(double nb)
{
	return(nb * nb);
}

	double
dist(t_dbl obj1, t_dbl obj2)
{
	double	dist;

	dist = hypot((obj1.x - obj2.x), (obj1.z - obj2.z));
	return (dist);
}

	t_dbl
rotate_point(double angle, t_dbl *ctr_ptr, t_dbl *old_ptr)
{
	t_dbl	new;
	t_dbl	ctr;
	t_dbl	old;

	if (ctr_ptr == NULL)
	{
		ctr.x = 0;
		ctr.z = 0;
	}
	else
		ctr = *ctr_ptr;
	if (old_ptr == NULL)
	{
		old.x = 1;
		old.z = 0;
	}
	else
		old = *old_ptr;
	new.x = ctr.x;
	new.x += (cos(angle) * (old.x - ctr.x) - sin(angle) * (old.z - ctr.z));
	new.z = ctr.z;
	new.z += (sin(angle) * (old.x - ctr.x) + cos(angle) * (old.z - ctr.z));
	return (new);
}
