/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:44:26 by trpham            #+#    #+#             */
/*   Updated: 2025/02/19 17:29:37 by trpham           ###   ########.fr       */
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
	game->map = read_str;
	validate_map(game);
	close(fd);
}

void	validate_map(t_game *game)
{
	char	**arr;
	int		row_count;
	int		i;

	row_count = 1;
	i = 0;
	while ((game->map)[i])
	{
		if ((game->map)[i] == '\n')
			row_count++;
		i++;
	}
	game->row_count = row_count;
	arr = ft_split(game->map, '\n');
	if (is_rectangular(arr, game) != 0 || is_walled(arr, game) != 0
		|| have_three_elements(arr, game) != 0 || not_allowed_element(arr, game))
	{
		perror("Error\nThis is a bad map, please use another map!");
		exit(-1);
	}
	if (have_three_elements(arr, game) != 0)
	{
		perror("Error\nMissing element");
		exit(-1);
	}
	// i = 0;
	// while (i < row_count)
	// {
	// 	printf("%s\n", arr[i]);
	// 	i++;
	// }
}

int	is_rectangular(char **arr, t_game *game)
{
	int	i;
	int	len;
	int	std_len;

	i = 0;
	std_len = ft_strlen(*arr);
	while (i < (*game).row_count)
	{
		len = ft_strlen(arr[i]);
		if (len != std_len)
			return (-1);
		i++;
	}
	game->col_count = std_len;
	return (0);
}

int	is_walled(char **arr, t_game *game)
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
		if (arr[0][j] != '1' || arr[last_row][j] != '1')
			return (-1);
		j++;
	}
	while (i <= last_row)
	{
		if (arr[i][0] != '1' || arr[i][last_col] != '1')
			return (-1);
		i++;
	}
	return (0);
}

int	have_three_elements(char **arr, t_game *game)
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
			if (arr[i][j] == 'P')
				(*game).player_count++;
			else if (arr[i][j] == 'E')
				(*game).exit_count++;
			else if (arr[i][j] == 'C')
				(*game).collectible_count++;
			j++;
		}
	}
	if ((*game).player_count != 1 || (*game).exit_count != 1
		|| (*game).collectible_count < 1)
		return (-1);
	return (0);
}
