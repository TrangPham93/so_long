/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:44:26 by trpham            #+#    #+#             */
/*   Updated: 2025/02/19 18:10:35 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map(const char *file_name, t_game *game)
{
	int		fd;
	char	*read_str;
	char	*row;

	is_valid_filename(file_name);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open read map");
		exit(-1);
	}
	read_str = "";
	while (1)
	{
		row = get_next_line(fd);
		if (!row)
			break ;
		read_str = ft_strjoin(read_str, row);
	}
	validate_map(read_str, game);
	close(fd);
}

void	validate_map(char *str, t_game *game)
{
	int		row_count;
	int		i;

	row_count = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			row_count++;
		i++;
	}
	game->row_count = row_count;
	game->map = ft_split(str, '\n');
	if (is_rectangular(game) != 0 || is_walled(game) != 0|| have_three_elements(game) != 0
			|| not_allowed_element(game))
	{
		perror("Error\nThis is a bad map, please use another map!");
		exit(-1);
	}
	reacheable_map(game);
	// i = 0;
	// while (i < row_count)
	// {
	// 	printf("%s\n", (game->map)[i]);
	// 	i++;
	// }
}

int	is_rectangular(t_game *game)
{
	int	i;
	int	len;
	int	std_len;

	i = 0;
	std_len = ft_strlen((game->map)[0]);
	while (i < (*game).row_count)
	{
		len = ft_strlen((game->map)[i]);
		if (len != std_len)
			return (-1);
		i++;
	}
	game->col_count = std_len;
	return (0);
}

int	is_walled(t_game *game)
{
	int	i;
	int	j;
	int	last_row;
	int	last_col;

	i = 0;
	j = 0;
	last_row = (*game).row_count - 1;
	last_col = (*game).col_count - 1;
	while (j <= last_col)
	{
		if ((game->map)[0][j] != '1' || (game->map)[last_row][j] != '1')
			return (-1);
		j++;
	}
	while (i <= last_row)
	{
		if ((game->map)[i][0] != '1' || (game->map)[i][last_col] != '1')
			return (-1);
		i++;
	}
	return (0);
}

int	have_three_elements(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	(*game).exit_count = 0;
	(*game).collectible_count = 0;
	(*game).player_count = 0;
	while (i++ < (*game).row_count - 1)
	{
		j = 1;
		while (j < (*game).col_count - 1)
		{
			if ((game->map)[i][j] == 'P')
			{
				(*game).player_count++;
				game->player.x = i;
				game->player.y = j; 
			}
			else if ((game->map)[i][j] == 'E')
			{
				(*game).exit_count++;
				game->exit.x = i;
				game->exit.y = j;
			}
			else if ((game->map)[i][j] == 'C')
				(*game).collectible_count++;
			j++;
		}
	}
	if ((*game).player_count != 1 || (*game).exit_count != 1
		|| (*game).collectible_count < 1)
		return (-1);
	return (0);
}
