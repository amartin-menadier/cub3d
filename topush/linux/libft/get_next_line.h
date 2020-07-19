/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:33:39 by user42            #+#    #+#             */
/*   Updated: 2020/07/19 20:58:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4

# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_struct
{
	char	*buf;
	char	*str;
	char	*tmp;
	int		nb_read;
	int		init;
}				t_struct;

int				get_next_line(int fd, char **line);
size_t			ft_strlengnl(const char *str);
char			*ft_substrgnl(char const *s, unsigned int start, size_t len);
char			*ft_strdupgnl(const char *src);
char			*ft_strjoingnl(char **s1, char *s2);
char			*ft_strchrgnl(const char *str, int c);

#endif
