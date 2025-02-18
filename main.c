/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:07:57 by trpham            #+#    #+#             */
/*   Updated: 2025/02/18 16:51:43 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(void)
{
	t_data	data;
	
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
	
	mlx_loop(data.mlx); 
	on_destroy(&data);
	
	return (0);
}

