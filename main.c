/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:07:57 by trpham            #+#    #+#             */
/*   Updated: 2025/02/28 15:58:17 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	on_keyrelease(int keycode, t_data *data)
{
	(void)data;
	printf("Pressed key: %d\\n", keycode);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;
	t_data	data;
	// t_vars	vars;
	
	// vars.game = &game;
	// vars.data = &data;
	data.game = &game;
	if (ac != 2)
		handle_error("No map is chosen");
	read_map(av[1], &game);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		handle_error("Failed to initialize Mlx");
	load_window(&data);
	load_asset(&data);

	data.game->total_collect = 0;
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, &on_keypress , &data);
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
	mlx_loop(data.mlx_ptr);
	// on_destroy(&data);
	// (void)vars;
	return (0);
}
