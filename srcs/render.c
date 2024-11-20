/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:15:57 by abernade          #+#    #+#             */
/*   Updated: 2024/11/20 15:10:13 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	draw_stripe(t_cubdata *cub, mlx_texture_t *tx, int line_h, int idx \
	, float offset)
{
	int	x;
	int	y;
	int	line_start;
	int	line_end;
	int	i;

	line_start = CAMERA_H / 2 - line_h / 2;
	line_end = CAMERA_H / 2 + line_h / 2;
	x = (int)roundf(remapf(offset, 0.0f, 1.0f, 0.0f, tx->width - 1));
	i = 0;
	while (i < CAMERA_H)
	{
		if (i < line_start)
			pixel_to_texture(cub->camera, idx, i, cub->ceiling_color);
		else if (i < line_end)
		{
			y = remap(i - line_start, 0, line_h - 1, 0, tx->height - 1);
			pixel_to_texture(cub->camera, idx, i, get_color(tx, x, y));
		}
		else
			pixel_to_texture(cub->camera, idx, i, cub->floor_color);
		i++;
	}
}

static void	draw_walls(t_cubdata *cub)
{
	float	dist;
	float	da;
	int		line_height;
	int		i;

	i = 0;
	while (i < CAMERA_W)
	{
		da = cub->player->angle - cub->rays[i].angle;
		if (da < 0)
			da += M_PI * 2;
		else if (da > M_PI * 2)
			da -= M_PI * 2;
		if (cub->rays[i].h_dist < cub->rays[i].v_dist)
			dist = cub->rays[i].h_dist;
		else
			dist = cub->rays[i].v_dist;
		dist *= cosf(da);
		line_height = ((float)CAMERA_H / dist) * 0.9f;
		draw_stripe(cub, cub->rays[i].wall_tx, line_height, i, \
			cub->rays[i].offset);
		i++;
	}
}

void	render(t_cubdata *cubdata)
{
	update_minimap_texture(cubdata);
	update_rays(cubdata);
	draw_walls(cubdata);
	merge_textures(cubdata->camera, cubdata->mmap, MMAP_X, MMAP_Y);
	texture_to_image(cubdata->camera, cubdata->main_img);
}
