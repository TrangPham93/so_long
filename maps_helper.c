/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:07:10 by trpham            #+#    #+#             */
/*   Updated: 2025/02/19 17:32:03 by trpham           ###   ########.fr       */
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

int	not_allowed_element(char **arr, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < (*game).row_count)
	{
		j = 0;
		while (j < (*game).col_count)
		{
			if (arr[i][j] != 'P' && arr[i][j] != 'E' && arr[i][j] != 'C'
					&& arr[i][j] != '1' && arr[i][j] != '0' )
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}




// printf("pos [%d][%d]\n", i, j);
// printf("update player_count at pos [%d][%d]\n", i, j);
// printf("update exit_count at pos [%d][%d]\n", i, j);
// printf("update collectible_count at pos [%d][%d]\n", i, j);
// printf("player %d\n", (*game).player_count);
// printf("eixt %d\n", (*game).exit_count);
// printf("collectible count %d\n", (*game).collectible_count);
