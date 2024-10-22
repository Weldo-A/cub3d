/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:48:01 by abernade          #+#    #+#             */
/*   Updated: 2024/10/22 17:08:25 by abernade         ###   ########.fr       */
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
	printf("intx: %i\t inty: %i\t", intx, inty);
	if (x < 0 || y < 0 \
		|| intx >= (int)cub->map->width || inty >= (int)cub->map->height)
		return (0x000000FF);
	c = cub->map->map_str[inty * cub->map->width + intx];
	if (c == '1')
		return (MMAP_COLOR_1);
	else
		return (MMAP_COLOR_0);
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
			printf("x: %f\ty: %f\t", x, y);
			uint32_t	color = get_color_at_pos(x, y, cub);
			printf("color:\t%X\n", color);
			pixel_to_texture(cub->mmap, i, j, color);
			x += MMAP_PIXEL_STEP;
			i++;
		}
		y += MMAP_PIXEL_STEP;
		j++;
	}
}
