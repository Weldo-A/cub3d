/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:01:42 by abernade          #+#    #+#             */
/*   Updated: 2024/11/19 15:31:42 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float remap(int n, int in_min, int in_max, int out_min, int out_max)
{
	return ((n - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

float remapf(float n, float in_min, float in_max, \
	float out_min, float out_max)
{
	return ((n - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

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
