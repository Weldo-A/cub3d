/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_enlever.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:55:32 by aduriez           #+#    #+#             */
/*   Updated: 2024/12/18 15:46:14 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	print_mini_map_data(t_insert_data *data)
{
	int x;
	int y;
	int index;

	index = 0;
	printf("\n----- Map -----\n");
	x = 0;
	while (x < data->nbr_line)
	{
		y = 0;
		while (y < data->max_line)
		{
			printf("%c", data->map[index].str);
			y++;
			index++;
		}
		printf("\n");
		x++;
	}
	printf("--------------\n");
}
