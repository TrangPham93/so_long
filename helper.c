/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:45:21 by trpham            #+#    #+#             */
/*   Updated: 2025/02/21 17:18:39 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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