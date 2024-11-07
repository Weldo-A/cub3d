/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 04:20:57 by abernade          #+#    #+#             */
/*   Updated: 2024/11/07 10:33:06 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_cubdata	*debug_data_init(void)
{
	t_cubdata	*cubdata;

	cubdata = malloc(sizeof(t_cubdata));
	cubdata->map = malloc(sizeof(t_map));
	cubdata->map->map_str = malloc(sizeof(char) * (ft_strlen(MAP_DEBUG) + 1));
	strcpy(cubdata->map->map_str, MAP_DEBUG);
	cubdata->map->width = 9;
	cubdata->map->height = 5;
	cubdata->floor_color = FLOOR_DEBUG;
	cubdata->ceiling_color = CEILING_DEBUG;
	cubdata->player = malloc(sizeof(t_player_data));
	cubdata->player->x = 5.5f;
	cubdata->player->y = 3.5f;
	cubdata->player->angle = M_3PI_2;
	cubdata->mmap_sqr_size = MMAP_SQUARE_SIZE;

	return (cubdata);
}