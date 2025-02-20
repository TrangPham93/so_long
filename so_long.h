/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:39:11 by trpham            #+#    #+#             */
/*   Updated: 2025/02/20 17:25:06 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h> // for perror()
# include "./libft/includes/get_next_line.h"
# include "./libft/includes/libft.h"
# include "./libft/includes/ft_printf.h"

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

typedef struct s_axis
{
	int		x; //col == j
	int		y; //row == i
}	t_axis;

typedef struct s_game
{
	char	**map;
	int		row_count;
	int		col_count;
	int		player_count;
	int		exit_count;
	int		collectible_count;
	int		up;
	int		down;
	int		left;
	int		right;
	t_axis	player;
	t_axis	exit;
}	t_game;

// read map and validate the maps
void	read_map(const char *file_name, t_game *game);
void	is_valid_filename(const char *str);
void	validate_map(char *str, t_game *game);
int		is_rectangular(t_game *game);
int		is_walled(t_game *game);
int		have_three_elements(t_game *game);
int		not_allowed_element(t_game *game);

// check whether the map allows the player to exit and all collectibles
int		check_path(t_game *game);
int		exit_reachable(t_game *game, char **temp_map, int x, int y);
int		collectables_reachable(t_game *game, char **temp_map, int x, int y);
int		check_all_collectables(t_game *game, char **temp_map);

// map helper function
char	**duplicate_map(t_game *game);
void	free_temp_map(t_game *game, char **temp_map);

void	handle_error(char *s);

//please delete before submit
void	print_map(char **map, t_game *game);

int		on_destroy(t_data *data);

#endif