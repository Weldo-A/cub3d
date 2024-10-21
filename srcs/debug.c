/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 04:20:57 by abernade          #+#    #+#             */
/*   Updated: 2024/10/21 06:09:16 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_cubdata	*debug_data_init(void)
{
	t_cubdata	*cubdata;

	cubdata = malloc(sizeof(t_cubdata));
	cubdata->map = malloc(sizeof(char) * (ft_strlen(MAP_DEBUG) + 1));
	strcpy(cubdata->map, MAP_DEBUG);
	cubdata->floor_color = FLOOR_DEBUG;
	cubdata->ceiling_color = CEILING_DEBUG;

	return (cubdata);
}