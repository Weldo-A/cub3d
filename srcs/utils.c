/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:01:42 by abernade          #+#    #+#             */
/*   Updated: 2024/11/22 02:53:47 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

bool	is_pos_valid(t_map *map, float x, float y)
{
	float	discard;
	float	step_x;
	float	step_y;

	if (map_element_at_pos(map, x, y) != '0')
		return (false);
	if (modff(x, &discard) < MIN_DIST_FROM_WALL)
		step_x = -1.0f;
	else if (modff(x, &discard) > 1.0f - MIN_DIST_FROM_WALL)
		step_x = 1.0f;
	else
		step_x = 0.0f;
	if (modff(y, &discard) < MIN_DIST_FROM_WALL)
		step_y = -1.0f;
	else if (modff(y, &discard) > 1.0f - MIN_DIST_FROM_WALL)
		step_y = 1.0f;
	else
		step_y = 0.0f;
	(void)discard;
	if (map_element_at_pos(map, x + step_x, y) != '0' \
		|| map_element_at_pos(map, x, y + step_y) != '0' \
		|| map_element_at_pos(map, x + step_x, y + step_y) != '0')
		return (false);
	return (true);
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
