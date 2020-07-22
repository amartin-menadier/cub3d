/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_look_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/20 17:40:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void
	look(t_dbl *angle, int key)
{
	if (key == LEFT)
		angle->x += ROT_SPEED;
	if (key == RIGHT)
		angle->x -= ROT_SPEED;
	if (key == DOWN)
		angle->y -= ROT_SPEED / 2;
	if (key == UP)
		angle->y += ROT_SPEED / 2;
	if (angle->y > PI / 2)
		angle->y = PI / 2;
	if (angle->y < -PI / 2)
		angle->y = -PI / 2;
}
