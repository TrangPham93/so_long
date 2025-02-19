/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:07:57 by trpham            #+#    #+#             */
/*   Updated: 2025/02/19 10:51:11 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	game;
	t_data	data;
	void	*img;
	char	*relative_path = "./images/empty_space.xpm";
	int		img_width;
	int 	img_height;
	
	if (ac != 2)
	{
		perror("Please choose a map");
		exit(-1);
	}
	else
	{
		read_map(av[1], &game);

	}
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		perror("Failed to initialize the pointer");
		return (1);
	}
	data.mlx_win = mlx_new_window(data.mlx, 1200, 600, "Hello world!");
	if (!data.mlx_win)
	{
		perror("Could not create a window");
		return (1);
	}
	img = mlx_xpm_file_to_image(data.mlx, relative_path, &img_width, &img_height);
	if (!img)
	{
		perror("Failed to read images");
		mlx_destroy_image(data.mlx, img);
		return(1);
	}
	mlx_put_image_to_window(data.mlx, data.mlx_win, img, 0, 0);
	mlx_put_image_to_window(data.mlx, data.mlx_win, img, 32, 0);
	(void)img;
	mlx_loop(data.mlx); 
	on_destroy(&data);
	
	return (0);
}

