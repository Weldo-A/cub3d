/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:44:24 by aduriez           #+#    #+#             */
/*   Updated: 2024/12/19 15:08:46 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

static void	load_all_assets(t_cubdata **cubdata, t_insert_data *data)
{
	load_asset(&(*cubdata)->asset_list, data->no, NORTH_TX);
	load_asset(&(*cubdata)->asset_list, data->so, SOUTH_TX);
	load_asset(&(*cubdata)->asset_list, data->we, WEST_TX);
	load_asset(&(*cubdata)->asset_list, data->ea, EAST_TX);
	load_asset(&(*cubdata)->asset_list, "assets/Brick_Texture.png", DOOR_TX);
}

static void	setup_map_and_player(t_cubdata **cubdata, t_insert_data *data)
{
	int	i;

	i = 0;
	while (i < data->max_line * data->nbr_line)
	{
		(*cubdata)->map->map_str[i] = data->map[i].str;
		i++;
	}
	(*cubdata)->player->x = (float)data->player_place.y + 0.5f;
	(*cubdata)->player->y = (float)data->player_place.x + 0.5f;
	(*cubdata)->map->width = data->max_line;
	(*cubdata)->map->height = data->nbr_line;
}

int	insert_data(t_cubdata **cubdata, t_insert_data *data)
{
	int	i;

	i = 0;
	if (!check_file("assets/Brick_Texture.png")
		|| !check_extension("assets/Brick_Texture.png", ".png"))
	{
		youhandle_errors(10, data);
		return (1);
	}
	(*cubdata)->map->map_str = malloc(sizeof(char) * (data->max_struct + 2));
	if (*cubdata == NULL)
	{
		youhandle_errors(9, data);
		return (1);
	}
	(*cubdata)->map->map_str[data->max_struct + 1] = '\0';
	setup_map_and_player(cubdata, data);
	set_player_direction(data, cubdata);
	load_all_assets(cubdata, data);
	(*cubdata)->floor_color = str_rgb_to_hex(data->c);
	(*cubdata)->ceiling_color = str_rgb_to_hex(data->f);
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
		return (youhandle_errors(1, data));
	if (check_file_valid(0, av) == 1)
		return (youhandle_errors(2, data));
	data->nbr_line = insert_len_data(av[1], data);
	if (data->nbr_line == -1)
		return (youhandle_errors(3, data));
	if (start_insert_map(data, av[1]) == 1)
		return (youhandle_errors(4, data));
	if (check_color(data) == 1)
		return (youhandle_errors(5, data));
	if (data->check != 6)
		return (youhandle_errors(7, data));
	if (check_textures(data) == 0)
		return (youhandle_errors(8, data));
	if (insert_data(cubdata, data) == 1)
		return (1);
	free_insert_data(data, 0);
	return (0);
}
