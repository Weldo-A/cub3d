/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:39:36 by aduriez           #+#    #+#             */
/*   Updated: 2024/12/17 16:19:53 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_valid_index(t_insert_data *data, int index)
{
	if (index < 0 || index >= data->max_struct)
		return (0);
	if ((index % data->max_line) == 0 && data->map[index].str == '1')
		return (0);
	if ((index + 1) % data->max_line == 0 && data->map[index].str == '1')
		return (0);
	return (1);
}

int	check_border_case(t_insert_data *data, int index)
{
	return (index < data->max_line || index >= data->max_struct - data->max_line
		|| index % data->max_line == 0 || (index + 1) % data->max_line == 0);
}

int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'd' || c == 'D');
}

int	is_accessible(t_insert_data *data, int index)
{
	char	up;
	char	down;
	char	left;
	char	right;
	int		result;

	result = 0;
	if (check_border_case(data, index))
		result = 1;
	else
	{
		up = data->map[index - data->max_line].str;
		down = data->map[index + data->max_line].str;
		left = data->map[index - 1].str;
		right = data->map[index + 1].str;
		if (!is_valid_char(up) || !is_valid_char(down) || !is_valid_char(left)
			|| !is_valid_char(right))
			result = 1;
	}
	return (result);
}
