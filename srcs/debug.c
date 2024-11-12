/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 04:20:57 by abernade          #+#    #+#             */
/*   Updated: 2024/11/12 18:08:55 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_cubdata	*debug_data_init(void)
{
	t_cubdata	*cubdata;

	cubdata = malloc(sizeof(t_cubdata));
	cubdata->map = malloc(sizeof(t_map));
	cubdata->map->map_str = malloc(sizeof(char) * (ft_strlen(MAP_DEBUG) + 1));
	strcpy(cubdata->map->map_str, MAP_DEBUG);
	cubdata->map->width = 9;
	cubdata->map->height = 5;
	cubdata->floor_color = FLOOR_DEBUG;
	cubdata->ceiling_color = CEILING_DEBUG;
	cubdata->player = malloc(sizeof(t_player_data));
	cubdata->player->x = 5.5f;
	cubdata->player->y = 3.5f;
	cubdata->player->angle = M_3PI_2;
	printf("INITIAL ANGLE %f\n\n", cubdata->player->angle);
	cubdata->mmap_sqr_size = MMAP_SQUARE_SIZE;

	return (cubdata);
}

static int	absolute(int val)
{
	return (val > 0 ? val : -val);
}

// Bresenham
void	draw_line(int x0, int y0, int x1, int y1, mlx_texture_t *tx, int color)
{
	float	fstep, pos;
	int		istep;

	if (absolute(x0 - x1) > (y0 - y1))
	{
		istep = (x0 < x1 ? 1 : -1);
		fstep = (float)(y0 - y1) / (float)(x0 - x1);
		pos = y0;
		while (x0 != x1)
		{
			pixel_to_texture(tx, x0, (int)pos, color);
			x0 += istep; pos += fstep;
		}
		pixel_to_texture(tx, x0, (int)pos, color);
	}
	else if (absolute(x0 - x1) < (y0 - y1))
	{
		istep = (y0 < y1 ? 1 : -1);
		fstep = (float)(x0 - x1) / (float)(y0 - y1);
		pos = x0;
		while (y0 != y1)
		{
			pixel_to_texture(tx, (int)pos, y0, color);
			y0 += istep; pos += fstep;
		}
		pixel_to_texture(tx, (int)pos, y0, color);
	}
}
