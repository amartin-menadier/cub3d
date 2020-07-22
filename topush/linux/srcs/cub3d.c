/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:34:24 by amartin-          #+#    #+#             */
/*   Updated: 2020/07/22 16:22:15 by user42           ###   ########.fr       */
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
	if (ft_memcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
		close_program(data, "Map file name does not end with .cub\n", "");
	if ((data->settings.fd = open(argv[1], O_RDONLY)) == -1)
		close_program(data, "Couldn't open .cub file\n", "");
}

int
	main(int argc, char **argv)
{
	t_data	data;

	ft_putstr_fd("\nInitialiazing settings...", 1);
	init_settings(&data.settings);
	ft_putstr_fd("\nChecking args...", 1);
	check_args_errors(&data, argc, argv);
	ft_putstr_fd("\nParsing file...", 1);
	parse_cub_file(&data);
	ft_putstr_fd("\nInitialiazing data...", 1);
	init_data(&data);
	ft_putstr_fd("\nHooking event...", 1);
	if (!data.save)
		hook_event(&data);
	ft_putstr_fd("\nLoop hook RNF...", 1);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	ft_putstr_fd("\nMlx loop...", 1);
	mlx_loop(data.mlx);
	return (0);
}
