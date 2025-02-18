/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:07:57 by trpham            #+#    #+#             */
/*   Updated: 2025/02/18 10:45:53 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(void *param)
{
	(void)param;
	exit(0); // Exit the program when the window is closed
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	
	mlx = mlx_init(); // Initialize MLX
	if (!mlx)
		return (1);
	mlx_win = mlx_new_window(mlx, 800, 600, "MLX Window Test");
	if (!mlx_win)
		return (1);

	mlx_hook(mlx_win, 17, 0, close_window, NULL); // Handle window close button
	mlx_loop(mlx); // Start the MLX loop

	return (0);
}

