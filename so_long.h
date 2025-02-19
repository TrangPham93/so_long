/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:39:11 by trpham            #+#    #+#             */
/*   Updated: 2025/02/19 15:59:22 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <mlx.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h> // for perror()
#include "./libft/includes/get_next_line.h"
#include "./libft/includes/libft.h"

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;

}	t_data;

typedef struct s_img
{
	void	*img;
	char	*addr;
	void	*resized_img;
	char	*resized_addr;
}	t_img;

typedef struct s_game
{
	char	*map;
	int		row_count;
	int		col_count;
	int		player_count;
	int		exit_count;
	int		collectible_count;
	
}	t_game;

void	read_map(const char *file_name,t_game *game);
void	validate_map(t_game *game);
int 	is_rectangular(char **arr, t_game *game);
int 	is_walled(char **arr, t_game *game);
int 	have_three_elements(char **arr, t_game *game);


int		on_destroy(t_data *data);


#endif