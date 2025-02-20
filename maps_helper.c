/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:07:10 by trpham            #+#    #+#             */
/*   Updated: 2025/02/20 13:38:33 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	is_valid_filename(const char *str)
{
	int	len;
	char	*file_type;
	
	len = ft_strlen(str);
	file_type =	ft_substr(str, len - 4, 4);
	if (ft_strcmp(file_type, ".ber") != 0)
	{
		perror("Error\nNot a valid file");
		exit(-1);
	}	
}

int	not_allowed_element(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < (*game).row_count)
	{
		j = 0;
		while (j < (*game).col_count)
		{
			if ((game->map)[i][j] != 'P' && (game->map)[i][j] != 'E' && (game->map)[i][j] != 'C'
					&& (game->map)[i][j] != '1' && (game->map)[i][j] != '0' )
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	reacheable_map(t_game *game)
{
	char	**temp_map;
	int		i;

	temp_map = malloc(sizeof(char *) * game->row_count);
	if (!temp_map)
		exit(-1);
	i = 0;
	while (i < game->row_count)
	{
		temp_map[i] = ft_strdup((game->map)[i]);
		i++;
	}
	
	// i = 0;
	// while (i < game->row_count)
	// {
	// 	printf("%s\n", temp_map[i]);
	// 	i++;
	// }
}

void  flood_fill(t_game *game)
{
	char old_value;

	old_value = (game->map)[game->player.y][game->player.x];
	fill(game, old_value, game->player.x, game->player.y);
	
}

int fill(t_game *game, char old_value, int x, int y)
{
	if (x <= 1 || x >= game->col_count - 1 || y < 0 || y >= game->row_count - 1  || game->map[y][x] != old_value || game->map[y][x] == '1')
		return (-1);
	game->map[y][x] = '1';
	game->right = fill(game, old_value, x + 1, y);
	game->left = fill(game, old_value, x - 1, y);
	game->down = fill(game, old_value, x, y + 1);
	game->up = fill(game, old_value, x, y - 1);

	if (game->down == '1' || game->up == '1' || game->left == '1' || game->right == '1')
		return (0);
	return (-1);
}

// printf("pos [%d][%d]\n", i, j);
// printf("update player_count at pos [%d][%d]\n", i, j);
// printf("update exit_count at pos [%d][%d]\n", i, j);
// printf("update collectible_count at pos [%d][%d]\n", i, j);
// printf("player %d\n", (*game).player_count);
// printf("eixt %d\n", (*game).exit_count);
// printf("collectible count %d\n", (*game).collectible_count);
