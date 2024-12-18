/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:03:27 by aduriez           #+#    #+#             */
/*   Updated: 2024/12/18 11:33:32 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_check_char(char c, t_insert_data *data, int *i)
{
	if (c == '1' || c == '0' || c == 'S' || c == 'D' || c == 'd')
	{
		data->map[*i].str = c;
		return (0);
	}
	if (c == ' ' || c == '\t' || c == '\n' || c == '\0')
	{
		data->map[*i].str = '1';
		return (0);
	}
	return (1);
}

void	ft_fill_remaining(t_insert_data *data, int *i, int *count, int x)
{
	if (*i >= (data->nbr_line * data->max_line))
		return ;
	data->map[*i].str = '1';
	(*i)++;
	(*count)++;
	while (*count < data->max_line)
	{
		if (*i >= (data->nbr_line * data->max_line))
			return ;
		data->map[*i].str = '1';
		data->map[*i].x = x;
		data->map[*i].y = *count;
		(*i)++;
		(*count)++;
	}
}

int	insert_data_map(char *line, t_insert_data *data, int x, int *i)
{
	int	count;

	count = 0;
	if (*i == (data->nbr_line * data->max_line))
		return (0);
	while (count < data->max_line)
	{
		if (*i >= (data->nbr_line * data->max_line))
			break ;
		data->map[*i].x = x;
		data->map[*i].y = count;
		if (line[count] == '\n' || line[count] == '\0')
			break ;
		if (ft_check_char(line[count], data, i) == 1)
			return (1);
		(*i)++;
		count++;
	}
	if ((line[count] == '\n' || line[count] == '\0') && count < data->max_line)
		ft_fill_remaining(data, i, &count, x);
	return (0);
}

int	insert_map(char *filename, t_insert_data *data, int *i)
{
	int		x;
	int		fd;
	int		count;
	char	*line;

	init_vars(&x, &count, &line);
	if (init_file(filename, &fd))
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (count >= data->start_map)
		{
			if (insert_data_map(line, data, x, i) == 1)
			{
				cleanup_resources(fd, line);
				return (1);
			}
			x++;
		}
		update_line(&line, fd, &count);
	}
	get_next_line(-1);
	close(fd);
	return (0);
}

int	start_insert_map(t_insert_data *data, char *arg)
{
	int	i;

	(void)arg;
	i = 0;
	(*data).map = malloc(sizeof(t_mini_map_data) * ((*data).nbr_line
				* (*data).max_line));
	if (!(*data).map)
		return (1);
	if (insert_map(arg, data, &i) == 1)
		return (1);
	if (check_wall(data) == 0)
		return (1);
	data->max_struct = i;
	return (0);
}
