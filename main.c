/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:07:57 by trpham            #+#    #+#             */
/*   Updated: 2025/02/21 14:54:30 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	game;
	t_data	data;

	if (ac != 2)
		handle_error("No map is chosen");
	read_map(av[1], &game);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		handle_error("Failed to initialize Mlx");
	load_window(&data, &game);
	load_background(&data, &game);
	render_img_exit_wall(&data, &game);
	
	render_img_collectibles(&data, &game);
	render_img_player(&data, &game);
	
	mlx_loop(data.mlx_ptr);
	on_destroy(&data);
	return (0);
}
