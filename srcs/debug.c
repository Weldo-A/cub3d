/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 04:20:57 by abernade          #+#    #+#             */
/*   Updated: 2024/11/13 18:25:18 by abernade         ###   ########.fr       */
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
	cubdata->mmap_sqr_size = MMAP_SQUARE_SIZE;

	return (cubdata);
}

static int	absolute(int val)
{
	return (val > 0 ? val : -val);
}


	// Bresenham line draw

static void line_low(int x0, int y0, int x1, int y1, mlx_texture_t *tx, int color)
{
	int		dx;
	int		dy;
	int		stepy;
	int		d;

	dx = x1 - x0;
	dy = y1 - y0;
	dy = dy > 0 ? dy : -dy;
	stepy = dy > 0 ? 1 : -1;
	d = 2 * dy - dx;
	while (x0 != x1)
	{
		if (x0 >= 0 && (uint32_t)x0 < tx->width && y0 >= 0 && (uint32_t)y0 < tx->height)
			pixel_to_texture(tx, x0, y0, color);
		if (d > 0)
		{
			y0 += stepy;
			d += 2 * (dy - dx);
		}
		else
			d += 2 * dy;
		x0++;
	}
}

static void line_high(int x0, int y0, int x1, int y1, mlx_texture_t *tx, int color)
{
	int		dx;
	int		dy;
	int		stepx;
	int		d;

	dx = x1 - x0;
	dy = y1 - y0;
	dx = dx > 0 ? dx : -dx;
	stepx = dx > 0 ? 1 : -1;
	d = 2 * dx - dy;
	while (y0 != y1)
	{
		if (x0 >= 0 && (uint32_t)x0 < tx->width && y0 >= 0 && (uint32_t)y0 < tx->height)
			pixel_to_texture(tx, x0, y0, color);
		if (d > 0)
		{
			x0 += stepx;
			d += 2 * (dx - dy);
		}
		else
			d += 2 * dx;
		y0++;
	}
}

void	draw_line(int x0, int y0, int x1, int y1, mlx_texture_t *tx, int color)
{
	if (x1 == x0)
	{
		int step = y1 > y0 ? 1 : -1;
		while (y0 != y1)
		{
			if (x0 >= 0 && (uint32_t)x0 < tx->width && y0 >= 0 && (uint32_t)y0 < tx->height)
				pixel_to_texture(tx, x0, y0, color);
			y0 += step;
		}
		if (x0 >= 0 && (uint32_t)x0 < tx->width && y0 >= 0 && (uint32_t)y0 < tx->height)
			pixel_to_texture(tx, x0, y0, color);
	}
	else if (y1 == y0)
	{
		int step = x1 > x0 ? 1 : -1;
		while (x0 != x1)
		{
			if (x0 >= 0 && (uint32_t)x0 < tx->width && y0 >= 0 && (uint32_t)y0 < tx->height)
				pixel_to_texture(tx, x0, y0, color);
			x0 += step;
		}
		if (x0 >= 0 && (uint32_t)x0 < tx->width && y0 >= 0 && (uint32_t)y0 < tx->height)
			pixel_to_texture(tx, x0, y0, color);
	}
	else if (absolute(x0 - x1) > absolute(y0 - y1))
	{
		if (x1 > x0)
			line_low(x0, y0, x1, y1, tx, color);
		else
			line_low(x1, y1, x0, y0, tx, color);
	}
	else
	{
		if (y1 > y0)
			line_high(x0, y0, x1, y1, tx, color);
		else
			line_high(x1, y1, x0, y0, tx, color);
	}
}
