/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_helper1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:07:10 by trpham            #+#    #+#             */
/*   Updated: 2025/03/05 13:50:25 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	is_valid_filename(const char *str)
{
	int		len;
	char	*file_type;

	len = ft_strlen(str);
	file_type = ft_substr(str, len - 4, 4);
	if (!file_type)
	{
		handle_error("substr file type not succeed", NULL);
		exit(-1);
	}
	if (ft_strcmp(file_type, ".ber") != 0)
	{
		handle_error("Not a valid file type", file_type);
		exit(-1);
	}
	free(file_type);
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
			if ((game->map)[i][j] != 'P' && (game->map)[i][j] != 'E'
				&& (game->map)[i][j] != 'C' && (game->map)[i][j] != '1'
				&& (game->map)[i][j] != '0')
			{
				handle_error("Not allowed elements", NULL);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
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
		{
			handle_error("Not rectangular map", NULL);
			return (-1);
		}
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
		{
			handle_error("Not walled map", NULL);
			return (-1);
		}
		j++;
	}
	while (i <= last_row)
	{
		if ((game->map)[i][0] != '1' || (game->map)[i][last_col] != '1')
		{
			handle_error("Not walled map", NULL);
			return (-1);
		}
		i++;
	}
	return (0);
}

char	**duplicate_map(t_game *game)
{
	char	**temp_map;
	int		i;

	temp_map = malloc(sizeof(char *) * game->row_count);
	if (!temp_map)
	{
		handle_error("Memory allocation for temporary map failed", NULL);
		return (NULL);
	}
	i = 0;
	while (i < game->row_count)
	{
		temp_map[i] = ft_strdup((game->map)[i]);
		if (!temp_map[i])
		{
			free_arr(temp_map, i);
			temp_map = NULL;
			handle_error("Strdup failed", NULL);
			return (NULL);
		}
		i++;
	}
	return (temp_map);
}
