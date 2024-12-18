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
