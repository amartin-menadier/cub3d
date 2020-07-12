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

void
	check_args_errors(t_data *data, int argc, char **argv)
{
	if (argc == 1 || argc > 3)
		close_program(data, "Invalid number of arguments\n", "");
	if (argc == 3 && ft_memcmp(argv[2], "--save", 6))
		close_program(data, "Second argument is not --save\n", "");
	else if (argc == 3)
		data->save = 1;
	else
		data->save = 0;
	if(ft_memcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
		close_program(data, "File extension is not .cub\n", "");
	if ((data->settings.fd = open(argv[1], O_RDONLY)) == -1)
		close_program(data, "Couldn't open .cub file\n", "");
}

int
	main(int argc, char **argv)
{
	t_data data;

	check_args_errors(&data, argc, argv);
	parse_cub_file(&data);
	init_data(&data);
	hook_event(&data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
