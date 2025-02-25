/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:07:57 by trpham            #+#    #+#             */
/*   Updated: 2025/02/25 16:53:34 by trpham           ###   ########.fr       */
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
	load_window(&data, &game);
	load_background(&data, &game);
	render_img_exit_wall(&data, &game);
	
	render_img_collectibles(&data, &game);
	render_img_player(&data);
	
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, &on_keypress , &data);
	
	// mlx_hook(data.mlx_win, KeyRelease, KeyReleaseMask, &on_keyrelease , &vars);
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
	mlx_loop(data.mlx_ptr);
	// on_destroy(&data);
	// (void)vars;
	return (0);
}

int	on_keypress(int keycode, t_data *data)
{
	if (keycode == W)
	{
		if (data->game->map[data->game->player.y - 1][data->game->player.x]
			!= '1')
		{
			data->game->player.y--;
			render_img_player(data);
		}
		// (game->player.y)++;
	}
	else if (keycode == S)
	{
		if (data->game->map[data->game->player.y + 1][data->game->player.x] != '1')
		{
			data->game->player.y++;
			render_img_player(data);
		}
	}
	else if (keycode == A)
	{
		if (data->game->map[data->game->player.y][data->game->player.x - 1] != '1')
		{
			data->game->player.x--;
			render_img_player(data);
		}	
	}
	else if (keycode == D)
	{
		if (data->game->map[data->game->player.y][data->game->player.x + 1] != '1')
		{
			data->game->player.x++;
			render_img_player(data);
		}	
	}
	else if (keycode == ESC)
	{
		on_destroy((void *)data);	
	}
	return (0);
}


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
