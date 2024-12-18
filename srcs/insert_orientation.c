/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_orientation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:20:13 by aduriez           #+#    #+#             */
/*   Updated: 2024/12/17 17:27:19 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_handle_map_line(char *line, t_insert_data *data, int *count, int x)
{
	if (data->check != 6)
		return (-1);
	if (data->start_map > x)
		data->start_map = x;
	if (data->max_line < (int)ft_strlen_no_new_line(line))
		data->max_line = ft_strlen_no_new_line(line);
	(*count)++;
	return (0);
}

int	ft_search_orientation(char *line, t_insert_data *data, int *count, int x)
{
	int	i;

	i = 0;
	i = dell_space(line, &i);
	if (ft_strncmp(&line[i], "C", 1) == 0)
		ft_insert_c(line, data);
	else if (ft_strncmp(&line[i], "F", 1) == 0)
		ft_insert_f(line, data);
	else if (ft_strncmp(&line[i], "NO", 2) == 0)
		ft_insert_no(line, data);
	else if (ft_strncmp(&line[i], "EA", 2) == 0)
		ft_insert_ea(line, data);
	else if (ft_strncmp(&line[i], "SO", 2) == 0)
		ft_insert_so(&line[i], data);
	else if (ft_strncmp(&line[i], "WE", 2) == 0)
		ft_insert_we(line, data);
	else if (ft_strncmp(&line[i], "\n", 1) == 0)
		return (0);
	else if (ft_strncmp(&line[i], "1", 1) == 0 || ft_strncmp(&line[i], "0",
			1) == 0)
		return (ft_handle_map_line(line, data, count, x));
	else
		return (-1);
	return (0);
}

void	ft_insert_f(char *line, t_insert_data *data)
{
	char	*end;
	int		i;

	i = 0;
	if (!line || !data || data->f != NULL)
	{
		data->check = 9999;
		return ;
	}
	end = ft_copy_end(line, 'F');
	if (!(end))
		return ;
	i = dell_space(end, &i);
	if (!end[i])
	{
		free(end);
		return ;
	}
	data->f = ft_strdup_new_line(&end[i]);
	free(end);
	if (!data->f)
		return ;
	data->check++;
}
