/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:01:42 by abernade          #+#    #+#             */
/*   Updated: 2024/11/06 17:39:05 by abernade         ###   ########.fr       */
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
