/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:07:57 by trpham            #+#    #+#             */
/*   Updated: 2025/02/18 15:58:52 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// typedef struct s_data
// {
// 	void	*mlx;
// 	void	*mlx_win;

// }	t_data;

// typedef struct s_img
// {
// 	void	*img;
// 	char	*addr;
// }	t_img;


int on_destroy(t_data *data)
{
    if (data->mlx_win)
        mlx_destroy_window(data->mlx, data->mlx_win);
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    return (0);
}


int	main(void)
{
	t_data	data;
	void	*img;
	char	*relative_path = "./images/Wooden_House_Roof_Tilset.xpm";
	int		img_width;
	int 	img_height;
	
	
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
	(void)img;
	mlx_loop(data.mlx); 
	on_destroy(&data);
	
	return (0);
}

