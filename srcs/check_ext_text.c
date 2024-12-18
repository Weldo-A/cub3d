/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ext_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:29:41 by aduriez           #+#    #+#             */
/*   Updated: 2024/12/18 11:11:00 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	check_file(char *path)
{
	int	fd;
	int	dir_fd;

	dir_fd = open(path, O_DIRECTORY);
	if (dir_fd != -1)
	{
		close(dir_fd);
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	check_extension(char *file, char *ext)
{
	int	file_len;
	int	ext_len;

	if (!file || !ext)
		return (0);
	file_len = ft_strlen(file);
	ext_len = ft_strlen(ext);
	if (file_len <= ext_len)
		return (0);
	return (!ft_strcmp(&file[file_len - ext_len], ext));
}

void	trim_end_spaces(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str) - 1;
	while (len >= 0 && (str[len] == ' ' || str[len] == '\t'
			|| str[len] == '\n'))
		str[len--] = '\0';
}

int	check_textures(t_insert_data *data)
{
	if (!data->no || !data->so || !data->we || !data->ea)
	{
		printf("Error\nMissing texture direction\n");
		return (0);
	}
	trim_end_spaces(data->no);
	trim_end_spaces(data->so);
	trim_end_spaces(data->we);
	trim_end_spaces(data->ea);
	if (!check_extension(data->no, ".png") || !check_extension(data->so, ".png")
		|| !check_extension(data->we, ".png") || !check_extension(data->ea,
			".png"))
	{
		return (0);
	}
	if (!check_file(data->no) || !check_file(data->so) || !check_file(data->we)
		|| !check_file(data->ea))
	{
		return (0);
	}
	return (1);
}

int	check_remaining_chars(char *str, int idx)
{
	while (str[idx] && (str[idx] == ' ' || str[idx] == '\t'))
		idx++;
	if (str[idx] != '\0')
		return (1);
	return (0);
}
