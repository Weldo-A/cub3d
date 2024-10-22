/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:01:42 by abernade          #+#    #+#             */
/*   Updated: 2024/10/23 00:32:31 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	map_element_at_pos(t_cubdata *cub, float x, float y)
{
	int	intx;
	int	inty;

	intx = (int)x;
	inty = (int)y;
	if (intx < 0 || inty < 0 || x > cub->map->width || y > cub->map->height)
		return ('\0');
	return (cub->map->map_str[inty * cub->map->width + intx]);
}
