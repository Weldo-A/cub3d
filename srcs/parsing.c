/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:44:24 by aduriez           #+#    #+#             */
/*   Updated: 2024/12/18 10:46:58 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	insert_len_data(char *filename, t_insert_data *data)
{
	char	*line;
	int		count;
	int		fd;
	int		x;

	count = 0;
	line = NULL;
	x = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_search_orientation(line, data, &count, x) == -1)
		{
			cleanup_resources(fd, line);
			return (-1);
		}
		update_line(&line, fd, &x);
	}
	get_next_line(-1);
	close(fd);
	return (count);
}

void	set_player_direction(t_insert_data *data, t_cubdata **cubdata)
{
	if (!data || !cubdata || !(*cubdata)->player)
		return ;
	if (data->orientation == 'N')
		(*cubdata)->player->angle = 3 * M_PI / 2;
	else if (data->orientation == 'S')
		(*cubdata)->player->angle = M_PI / 2;
	else if (data->orientation == 'E')
		(*cubdata)->player->angle = 0;
	else if (data->orientation == 'W')
		(*cubdata)->player->angle = M_PI;
}

void	insert_data(t_cubdata **cubdata, t_insert_data *data)
{
	int	i;

	i = 0;
	(*cubdata)->map->map_str = malloc(sizeof(char) * (data->max_struct + 2));
	(*cubdata)->map->map_str[data->max_struct + 1] = '\0';
	while (i < data->max_line * data->nbr_line)
	{
		(*cubdata)->map->map_str[i] = data->map[i].str;
		i++;
	}
	(*cubdata)->player->x = (float)data->player_place.y + 0.5f;
	(*cubdata)->player->y = (float)data->player_place.x + 0.5f;
	(*cubdata)->map->width = data->max_line;
	(*cubdata)->map->height = data->nbr_line;
	set_player_direction(data, cubdata);
	load_asset(&(*cubdata)->asset_list, data->no, NORTH_TX);
	load_asset(&(*cubdata)->asset_list, data->so, SOUTH_TX);
	load_asset(&(*cubdata)->asset_list, data->we, WEST_TX);
	load_asset(&(*cubdata)->asset_list, data->ea, EAST_TX);
	load_asset(&(*cubdata)->asset_list, "assets/Brick_Texture.png", DOOR_TX);
	(*cubdata)->floor_color = str_rgb_to_hex(data->c);
	(*cubdata)->ceiling_color = str_rgb_to_hex(data->f);
}

static int	init_data(t_insert_data **data)
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
	(*data)->so = NULL;
	(*data)->we = NULL;
	(*data)->c = NULL;
	(*data)->f = NULL;
	(*data)->map = NULL;
	return (0);
}

int	start_parsing(int ac, char **av, t_cubdata **cubdata)
{
	t_insert_data	*data;

	if (!av || !cubdata || !*cubdata)
		return (1);
	if (init_data(&data))
		return (1);
	if (ac != 2)
		return (handle_errors(1, data));
	if (check_file_valid(0, av) == 1)
		return (handle_errors(2, data));
	data->nbr_line = insert_len_data(av[1], data);
	if (data->nbr_line == -1)
		return (handle_errors(3, data));
	if (start_insert_map(data, av[1]) == 1)
		return (handle_errors(4, data));
	if (check_color(data) == 1)
		return (handle_errors(5, data));
	if (data->check != 6)
		return (handle_errors(7, data));
	if (check_textures(data) == 0)
		return (handle_errors(8, data));
	insert_data(cubdata, data);
	print_mini_map_data(data);
	free_insert_data(data, 0);
	return (0);
}
