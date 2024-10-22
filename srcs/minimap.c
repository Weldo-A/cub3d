/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:48:01 by abernade          #+#    #+#             */
/*   Updated: 2024/10/22 04:01:57 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static uint32_t	get_color_at_pos(float x, float y, t_cubdata *cub)
{
	int		intx;
	int		inty;
	char	c;

	intx = (int)x;
	inty = (int)y;
	if (intx < 0 || inty < 0 \
		|| intx > (int)cub->map->width || inty > (int)cub->map->height)
		return (0xFFFFFFFF);
	c = cub->map->map_str[inty * cub->map->width + intx];
	if (c == 0)
		return (MMAP_COLOR_0);
	else
		return (MMAP_COLOR_1);
}

void	update_minimap_texture(t_cubdata *cub)
{
	int		i;
	int		j;
	float	x;
	float	y;
	float	origin_x;

	origin_x = cub->player->x - (cub->mmap->width / 2 / cub->mmap_sqr_size);
	y = cub->player->y - (cub->mmap->height / 2 / cub->mmap_sqr_size);
	j = 0;
	while (j < (int)cub->mmap->height)
	{
		i = 0;
		x = origin_x;
		while (i < (int)cub->mmap->width)
		{
			((uint32_t *)cub->mmap->pixels)[j * cub->mmap->width + i] = \
				get_color_at_pos(x, y, cub);
			x += MMAP_PIXEL_STEP;
			i++;
		}
		y += MMAP_PIXEL_STEP;
		j++;
	}
}
