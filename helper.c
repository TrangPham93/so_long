/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:45:21 by trpham            #+#    #+#             */
/*   Updated: 2025/03/01 15:13:59 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_error(char *s, char *to_free)
{
	if (to_free)
		free(to_free);
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(s, 2);
	// perror(s);
	exit(-1);
}

void	print_map(char **map, t_game *game)
{
	int	i;

	i = 0;
	if (!map)
		handle_error("there is no map to print", NULL);
	while (i < game->row_count)
	{
		printf("%s\n", map[i]);
		i++;
	}
}


void	free_arr(char **arr, int count)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// void	free_map(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->game->row_count)
// 	{
// 		free(data->game->map[i]);
// 		i++;
// 	}
// 	free(data->game->map);
// }

void	winner_print(void)
{
	ft_printf("-----------------------------------------------\n");
	ft_printf("|    🎉🎉🎉  Congratulations!!!!!  🎉🎉🎉     |\n");
	ft_printf("|    You found all collectibles and exit.     |\n");
	ft_printf("|        ✓✓✓✓✓✓✓✓ You won! ✓✓✓✓✓✓✓✓           |\n");
	ft_printf("-----------------------------------------------\n");
	exit(0);
}
