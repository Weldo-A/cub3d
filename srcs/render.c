/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weldo <weldo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:15:57 by abernade          #+#    #+#             */
/*   Updated: 2024/11/18 18:30:27 by weldo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	set_background(t_cubdata * cubdata)
{
	int	x;
	int	y;

	y = 0;
	while (y < CAMERA_H / 2)
	{
		x = 0;
		while (x < CAMERA_W)
		{
			pixel_to_texture(cubdata->camera, x, y, cubdata->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < CAMERA_H)
	{
		x = 0;
		while (x < CAMERA_W)
		{
			pixel_to_texture(cubdata->camera, x, y, cubdata->floor_color);
			x++;
		}
		y++;
	}
}

static void	draw_stripe(t_cubdata *cub, int line_h, int idx)
{
	int line_start;
	int line_end;
	int	i;

	line_start = CAMERA_H / 2 - line_h / 2;
	line_end = CAMERA_H / 2 + line_h / 2;
	i = 0;
	while (i < CAMERA_H)
	{
		if (i < line_start)
			pixel_to_texture(cub->camera, idx, i, cub->ceiling_color);
		else if (i <= line_end)
			pixel_to_texture(cub->camera, idx, i, GREEN);
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
		if (line_height > CAMERA_H)
			line_height = CAMERA_H;
		draw_stripe(cub, line_height, i);
		i++;
	}
}

void	render(t_cubdata *cubdata)
{
	set_background(cubdata);
	update_minimap_texture(cubdata);
	update_rays(cubdata);
	draw_walls(cubdata);
	merge_textures(cubdata->camera, cubdata->mmap, MMAP_X, MMAP_Y);
	texture_to_image(cubdata->camera, cubdata->main_img);

}
