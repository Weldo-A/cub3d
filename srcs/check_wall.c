/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:02:44 by aduriez           #+#    #+#             */
/*   Updated: 2024/12/18 11:36:56 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	flood_fill(t_insert_data *data, int index, int *visited)
{
	if (!is_valid_index(data, index) || visited[index])
		return ;
	if (data->map[index].str == '1')
		return ;
	visited[index] = 1;
	flood_fill(data, index - data->max_line, visited);
	flood_fill(data, index + data->max_line, visited);
	flood_fill(data, index - 1, visited);
	flood_fill(data, index + 1, visited);
}

int	search_player(t_insert_data *data)
{
	int	i;
	int	count;
	int	count_y;

	count_y = 0;
	i = 0;
	count = 0;
	while (i < data->max_struct)
	{
		if (data->map[i].str == 'N' || data->map[i].str == 'S'
			|| data->map[i].str == 'E' || data->map[i].str == 'W')
		{
			data->orientation = data->map[i].str;
			data->player_place.y = i % data->max_line;
			data->player_place.x = i / data->max_line;
			data->map[i].str = '0';
			count++;
		}
		i++;
	}
	if (count != 1)
		return (1);
	return (0);
}

int	init_check_wall(t_insert_data *data, int **visited)
{
	if (!data || !data->map || data->max_line * data->nbr_line == 0)
		return (0);
	data->max_struct = data->max_line * data->nbr_line;
	*visited = ft_calloc(data->max_struct, sizeof(int));
	if (!*visited)
		return (handle_error("Memory allocation failed\n", NULL));
	if (search_player(data) == 1)
		return (handle_error(NULL, *visited));
	return (1);
}

int	check_visited_cells(t_insert_data *data, int *visited)
{
	int	i;

	i = 0;
	if (visited[0] == 1)
		return (0);
	while (i < data->max_struct)
	{
		if (visited[i] == 1 && is_accessible(data, i))
			return (0);
		i++;
	}
	return (1);
}

int	check_wall(t_insert_data *data)
{
	int	*visited;
	int	start_index;
	int	result;

	if (!init_check_wall(data, &visited))
		return (0);
	start_index = data->player_place.x * data->max_line + data->player_place.y;
	flood_fill(data, start_index, visited);
	result = check_visited_cells(data, visited);
	if (!result)
	{
		free(visited);
		return (0);
	}
	free(visited);
	return (1);
}
