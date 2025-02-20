/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:45:21 by trpham            #+#    #+#             */
/*   Updated: 2025/02/20 17:41:50 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int on_destroy(t_data *data)
{
    if (data->mlx_win)
        mlx_destroy_window(data->mlx_ptr, data->mlx_win);
    if (data->mlx_ptr)
    {
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
    }
    return (0);
}
void handle_error(char *s)
{    
    ft_printf("Error\n");
    perror(s);
    exit(-1);
}

void print_map(char **map, t_game *game)
{
    int i;
    
    i = 0;
	if (!map)
		handle_error("there is no map to print");
    while (i < game->row_count)
	{
		printf("%s\n", map[i]);
		i++;
    }
}