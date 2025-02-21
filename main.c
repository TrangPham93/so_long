/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:07:57 by trpham            #+#    #+#             */
/*   Updated: 2025/02/21 17:18:46 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int on_destroy(void *param)
{
    t_data *data = (t_data *)param;
    
    if (data->mlx_win)
        mlx_destroy_window(data->mlx_ptr, data->mlx_win);
    if (data->mlx_ptr)
    {
        mlx_destroy_display(data->mlx_ptr);
    }
    // free(data->mlx_ptr);
    return (0);
}

int	on_keypress(int keycode, t_data *data)
{
	(void)data;
	printf("Pressed key: %d\\n", keycode);
	return (0);
}

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
	
	mlx_hook(data.mlx_win, KeyRelease, KeyPressMask, &on_keypress , &data);
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
	mlx_loop(data.mlx_ptr);
	// on_destroy(&data);
	return (0);
}
// int	quit_window(int keycode, t_data *data)
// {
// 	if (keycode == ESC)
// 	{
// 		on_destroy(data);
// 		exit(-1);
// 	}
// }

// int on_destroy(t_data *data)
// {
//     if (data->mlx_win)
//         mlx_destroy_window(data->mlx_ptr, data->mlx_win);
//     if (data->mlx_ptr)
//     {
//         mlx_destroy_display(data->mlx_ptr);
//         free(data->mlx_ptr);
//     }
//     return (0);
// }
