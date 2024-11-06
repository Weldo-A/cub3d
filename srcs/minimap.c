/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:48:01 by abernade          #+#    #+#             */
/*   Updated: 2024/11/06 17:23:32 by abernade         ###   ########.fr       */
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
	if (x < 0 || y < 0 \
		|| intx >= (int)cub->map->width || inty >= (int)cub->map->height)
		return (0x0000FFFF);
	c = cub->map->map_str[inty * cub->map->width + intx];
	if (c == '1')
		return (MMAP_COLOR_1);
	else
		return (MMAP_COLOR_0);
}

void	draw_player(mlx_texture_t *mmap, t_asset *assets)
{
	mlx_texture_t	*player_icon;

	player_icon = get_asset(assets, MMAP_PLAYER_ICON);
	merge_textures(mmap, player_icon, mmap->width / 2, mmap->height / 2);
}

void	update_minimap_texture(t_cubdata *cub)
{
	int		i;
	int		j;
	float	x;
	float	y;
	float	origin_x;

	origin_x = cub->player->x - ((float)cub->mmap->width / 2 / cub->mmap_sqr_size);
	y = cub->player->y - ((float)cub->mmap->height / 2 / cub->mmap_sqr_size);
	j = 0;
	while (j < (int)cub->mmap->height)
	{
		i = 0;
		x = origin_x;
		while (i < (int)cub->mmap->width)
		{
			pixel_to_texture(cub->mmap, i, j, get_color_at_pos(x, y, cub));
			x += MMAP_PIXEL_STEP;
			i++;
		}
		y += MMAP_PIXEL_STEP;
		j++;
	}
	draw_player(cub ->mmap, cub->asset_list);
}
