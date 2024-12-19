/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_insert_maps.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:08:55 by aduriez           #+#    #+#             */
/*   Updated: 2024/12/18 11:10:49 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	init_file(char *filename, int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
		return (1);
	return (0);
}

void	cleanup_resources(int fd, char *line)
{
	get_next_line(-1);
	close(fd);
	free(line);
}

void	init_vars(int *x, int *count, char **line)
{
	*x = 0;
	*count = 0;
	*line = NULL;
}

void	update_line(char **line, int fd, int *count)
{
	free(*line);
	*line = get_next_line(fd);
	(*count)++;
}

int	init_data(t_insert_data **data)
{
	*data = malloc(sizeof(t_insert_data));
	if (!*data)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		return (1);
	}
	(*data)->check = 0;
	(*data)->max_line = 0;
	(*data)->start_map = 999999999;
	(*data)->no = NULL;
	(*data)->ea = NULL;
	(*data)->door = NULL;
	(*data)->so = NULL;
	(*data)->we = NULL;
	(*data)->c = NULL;
	(*data)->f = NULL;
	(*data)->map = NULL;
	return (0);
}
