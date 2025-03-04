/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:39:11 by trpham            #+#    #+#             */
/*   Updated: 2025/03/04 15:59:09 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include <X11/X.h>

# define IMG_W 32
# define IMG_H 32
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define AU 65362
# define AD 65364
# define AL 65361
# define AR 65363

typedef struct s_axis
{
	int		x;
	int		y;
}	t_axis;

typedef struct s_game
{
	char	**map;
	int		row_count;
	int		col_count;
	int		player_count;
	int		exit_count;
	int		collectible_count;
	t_axis	player;
	int		total_move;
	int		total_collect;
}	t_game;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*img_player;
	void	*img_background;
	void	*img_exit;
	void	*img_wall;
	void	*img_collects;
	t_game	*game;

}	t_data;

// initialize data structure
void	init_data(t_data *data);

// read map and validate the maps
void	read_map(const char *file_name, t_data *data);
char	*read_and_join_line(int fd);
void	is_valid_filename(const char *str);
int		validate_map(char *str, t_data *data);
int		is_rectangular(t_game *game);
int		is_walled(t_game *game);
int		one_player_and_exit(t_game *game);
int		collectible_exist(t_game *game);
int		not_allowed_element(t_game *game);
char	**duplicate_map(t_game *game);
void	reset_temp_map(t_game *game, char **temp_map);

// check whether the map allows the player to exit and all collectibles
int		check_path(t_game *game);
int		exit_reachable(t_game *game, char **temp_map, int x, int y);
int		collectables_reachable(t_game *game, char **temp_map, int x, int y);
int		check_all_collectables(t_game *game, char **temp_map);

// load assets
void	load_window(t_data *data);
void	load_asset(t_data *data);

// rendering all images
void	render_image(t_data *data);
void	render_img_background(t_data *data);
void	render_img_exit_wall(t_data *data);
void	render_img_player(t_data *data);
void	render_img_collectibles(t_data *data);

// keyboard action
int		on_keypress(int keycode, t_data *data);
void	move_player(t_data *data, int new_x, int new_y);
int		on_destroy(t_data *data);

// helper function
void	handle_error(char *s, char *to_free);
void	winner_print(void);
void	free_arr(char **arr, int count);

#endif