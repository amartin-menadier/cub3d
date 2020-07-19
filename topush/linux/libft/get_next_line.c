/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:07:21 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/19 20:59:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		get_next_line3(t_struct *info, int fd)
{
	if (!(info->buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	info->nb_read = read(fd, info->buf, BUFFER_SIZE);
	info->buf[info->nb_read] = 0;
	info->str = ft_strjoingnl(&info->str, info->buf);
	free(info->buf);
	info->buf = 0;
	return (0);
}

int		get_next_line2(t_struct *info, int fd, char **line)
{
	size_t	i;

	i = 0;
	while (ft_strchrgnl(info->str, '\n') == NULL && info->nb_read != 0)
		if (get_next_line3(info, fd) == -1)
			return (-1);
	if (ft_strchrgnl(info->str, '\n') != NULL)
	{
		while (i < ft_strlengnl(info->str) && info->str[i] != '\n')
			i += 1;
		*line = i == 0 ? ft_strdupgnl("") : ft_substrgnl(info->str, 0, i);
		info->tmp =
			ft_substrgnl(info->str, i + 1, ft_strlengnl(&info->str[i + 1]));
		free(info->str);
		info->str = ft_strdupgnl(info->tmp);
		free(info->tmp);
		return (1);
	}
	else
	{
		*line = ft_strdupgnl(info->str);
		free(info->str);
		info->str = 0;
		return (0);
	}
}

int		get_next_line(int fd, char **line)
{
	static t_struct	info;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	if (!info.str)
	{
		info.str = ft_strdupgnl("");
		info.nb_read = 1;
	}
	while (info.nb_read > 0 || ft_strchrgnl(info.str, '\n') != NULL)
		return (get_next_line2(&info, fd, line));
	*line = ft_strdupgnl(info.str);
	free(info.str);
	free(info.buf);
	info.buf = 0;
	info.str = 0;
	return (0);
}
