/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:44:35 by trpham            #+#    #+#             */
/*   Updated: 2025/02/20 19:01:03 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_window(t_data data, t_game game)
{
	data.mlx_win = mlx_new_window(data.mlx_ptr, game.col_count * 32,
		game.row_count * 32 , "so_long");
	if (!data.mlx_win)
		handle_error("Failed to initialize a window");
	mlx_loop(data.mlx_ptr);
}

void	load_background(t_data data, t_game game)
{
	// t_img	*img_player;
	char	*relative_path = "./images/empty_space.xpm";
	void	*background_img;
	int	img_height;
	int img_width;
	
	background_img = mlx_xpm_file_to_image(data.mlx_ptr, relative_path,
		&img_width, &img_height);
	if (!background_img)
	{
		mlx_destroy_image(data.mlx_ptr, background_img);
		handle_error("Failed to load image");
	}
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, background_img, 0, 0);
	// game.img_player.img_width = 32;
	// game.img_player.img_height = 32;	
	// game.img_player.img = mlx_xpm_file_to_image(data.mlx_ptr, relative_path,
	// 	&game.img_player.img_width, &game.img_player.img_height);
	// if (!game.img_player.img)
	// {
	// 	mlx_destroy_image(data.mlx_ptr, game.img_player.img);
	// 	handle_error("Failed to load image");
	// }
	// mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, game.img_player.img, 0, 0);
	(void)game;
}