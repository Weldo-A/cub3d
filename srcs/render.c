/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:15:57 by abernade          #+#    #+#             */
/*   Updated: 2024/12/17 13:59:56 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	draw_stripe_background(t_cubdata *cub, int idx)
{
	int	i;

	i = 0;
	while (i < CAMERA_H / 2)
	{
		pixel_to_texture(cub->camera, idx, i, cub->ceiling_color);
		i++;
	}
	while (i < CAMERA_H)
	{
		pixel_to_texture(cub->camera, idx, i, cub->floor_color);
		i++;
	}
}

static void	draw_stripe(t_cubdata *cub, int line_h, int idx, float offset)
{
	int	x;
	int	y;
	int	line_start;
	int	i;

	static int	errors = 0;

	line_start = CAMERA_H / 2 - line_h / 2;
	x = (int)roundf((offset - 0.0f) * \
		(cub->rays[idx].wall_tx->width - 1) / 1.0f);
	i = 0;
	while (i < CAMERA_H)
	{
		if (i < line_start)
			pixel_to_texture(cub->camera, idx, i, cub->ceiling_color);
		else if (i < CAMERA_H / 2 + line_h / 2)
		{
			y = (i - line_start) * (cub->rays[idx].wall_tx->height - 1) \
				/ (line_h - 1);
			
			if (x > (int)cub->rays[idx].wall_tx->width || y > (int)cub->rays[idx].wall_tx->height || x < 0 || y < 0)
			{
				errors++;
				printf("\nERROR\t%d\n\n", errors);
				printf("x:\t%d\n", x);
				printf("width:\t%d\nheight:\t%d\n", cub->rays[idx].wall_tx->width, cub->rays[idx].wall_tx->height);
				
				t_asset *asset = cub->asset_list;
				while (asset && asset->tx != cub->rays[idx].wall_tx)
					asset = asset->next;
				if (asset)
					printf("asset name:\t%s\n", asset->name);
				else
					printf("not an asset ?????\n");
				
			}
			if (errors > 5)
				exit (1);
			
			pixel_to_texture(cub->camera, idx, i, \
				get_color(cub->rays[idx].wall_tx, x, y));
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
		if (cub->rays[i].ray_hit)
			da = cub->player->angle - cub->rays[i].angle;
		else
		{
			draw_stripe_background(cub, i);
			i++;
			continue ;
		}
		if (cub->rays[i].h_dist < cub->rays[i].v_dist)
			dist = cub->rays[i].h_dist;
		else
			dist = cub->rays[i].v_dist;
		dist *= cosf(da);
		line_height = (CAMERA_H / dist) * 0.9f;
		draw_stripe(cub, line_height, i, cub->rays[i].offset);
		i++;
	}
}

void	render(t_cubdata *cubdata)
{
	update_minimap_texture(cubdata);
	apply_minimap_mask(cubdata->mmap, cubdata->asset_list);
	draw_walls(cubdata);
	merge_textures(cubdata->camera, cubdata->mmap, MMAP_X, MMAP_Y);
	texture_to_image(cubdata->camera, cubdata->main_img);
}
