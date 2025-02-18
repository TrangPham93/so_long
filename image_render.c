/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:44:35 by trpham            #+#    #+#             */
/*   Updated: 2025/02/18 16:51:34 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void put_background()
{
	void	*img;
	char	*relative_path = "./images/Wooden_House_Roof_Tilset.xpm";
	int		img_width;
	int 	img_height;

	img = mlx_xpm_file_to_image(data.mlx, relative_path, &img_width, &img_height);
	if (!img)
	{
		perror("Failed to read images");
		mlx_destroy_image(data.mlx, img);
		return(1);
	}
	mlx_put_image_to_window(data.mlx, data.mlx_win, img, 0, 0);
	(void)img;
}