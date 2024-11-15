/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weldo <weldo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:01:42 by abernade          #+#    #+#             */
/*   Updated: 2024/11/15 17:05:13 by weldo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float	absolutef(float value)
{
	if (value >= 0)
		return (value);
	return (-value);
}

char	map_element_at_pos(t_map *map, float x, float y)
{
	int	intx;
	int	inty;

	intx = (int)x;
	inty = (int)y;
	if (intx < 0 || inty < 0 || x > map->width || y > map->height)
		return (0);
	return (map->map_str[inty * map->width + intx]);
}

uint32_t	get_color(const mlx_texture_t *tx, int x, int y)
{
	uint32_t	color;
	int			offset;

	offset = (y * tx->width + x) * 4;
	color = ((uint32_t)tx->pixels[offset++] << 24);
	color |= ((uint32_t)tx->pixels[offset++] << 16);
	color |= ((uint32_t)tx->pixels[offset++] << 8);
	color |= (uint32_t)tx->pixels[offset];
	return (color);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}
