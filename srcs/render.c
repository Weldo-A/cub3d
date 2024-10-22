/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:15:57 by abernade          #+#    #+#             */
/*   Updated: 2024/10/22 16:36:21 by abernade         ###   ########.fr       */
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

void	render(t_cubdata *cubdata)
{
	static int	i = 0;
	if (i == 0)
	{
		set_background(cubdata);

		update_minimap_texture(cubdata);
		mlx_image_t *img =  mlx_texture_to_image(cubdata->mlx, cubdata->mmap);
		mlx_image_to_window(cubdata->mlx, img, 0, 0);
		// merge_textures(cubdata->camera, cubdata->mmap, MMAP_X, MMAP_Y);
		// // ray casting part
		
		// camera_to_image(cubdata->camera, cubdata->main_img);

	}
	i++;

}
