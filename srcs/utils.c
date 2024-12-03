/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:01:42 by abernade          #+#    #+#             */
/*   Updated: 2024/12/03 19:43:12 by abernade         ###   ########.fr       */
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

static bool	is_door_pos_walkable(t_cubdata *cub, char door_type, float x, float y)
{
	t_door	*door;
	float	fract;
	float	discard;

	door = search_door(cub->active_doors, x, y);
	if (!door)
		error_exit(DOOR_WALK);
	if (door_type == DOOR_CHAR_X)
		fract = modff(y, &discard);
	else
		fract = modff(x, &discard);
	return (door->state == 30 || fract > 0.5f + MIN_DIST_FROM_WALL \
		|| fract < 0.5f - MIN_DIST_FROM_WALL);
}

static bool	is_pos_valid(t_cubdata *cub, float x, float y)
{
	char	map_char;

	map_char = map_element_at_pos(cub->map, x, y);
	if (!map_char || map_char == '1')
		return (false);
	if (map_char == '0')
		return (true);
	if (map_char == DOOR_CHAR_X || map_char == DOOR_CHAR_Y)
		return (is_door_pos_walkable(cub, map_char, x, y));
	return (false);
}

bool	is_pos_walkable(t_cubdata *cub, float x, float y)
{
	float	discard;
	float	step_x;
	float	step_y;

	if (map_element_at_pos(cub->map, x, y) == '1')
		return (false);
	if (modff(x, &discard) < MIN_DIST_FROM_WALL)
		step_x = -MIN_DIST_FROM_WALL;
	else if (modff(x, &discard) > 1.0f - MIN_DIST_FROM_WALL)
		step_x = MIN_DIST_FROM_WALL;
	else
		step_x = 0.0f;
	if (modff(y, &discard) < MIN_DIST_FROM_WALL)
		step_y = -MIN_DIST_FROM_WALL;
	else if (modff(y, &discard) > 1.0f - MIN_DIST_FROM_WALL)
		step_y = MIN_DIST_FROM_WALL;
	else
		step_y = 0.0f;
	(void)discard;
	if (!is_pos_valid(cub, x + step_x, y) \
		|| !is_pos_valid(cub, x, y + step_y) \
		|| !is_pos_valid(cub, x + step_x, y + step_y))
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
