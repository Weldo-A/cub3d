/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubdata.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:38:37 by abernade          #+#    #+#             */
/*   Updated: 2024/11/20 15:21:21 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cubdata_mlx_init(t_cubdata *cubdata)
{
	cubdata->mlx = mlx_init(WINDOW_W, WINDOW_H, "cub3d", false);
	if (!cubdata->mlx)
		error_exit(MLX_ERR);
	cubdata->main_img = mlx_new_image(cubdata->mlx, WINDOW_W, WINDOW_H);
	if (!cubdata->main_img)
		error_exit(MLX_ERR);
	mlx_set_cursor_mode(cubdata->mlx, MLX_MOUSE_DISABLED);
	mlx_set_mouse_pos(cubdata->mlx, 0, 0);
	cubdata->camera = new_texture(CAMERA_W, CAMERA_H);
	cubdata->mmap = new_texture(MMAP_WIDTH, MMAP_HEIGHT);
	load_asset(&cubdata->asset_list, MMAP_PLAYER_PATH, MMAP_PLAYER_ICON);
	cubdata->projplane_w = PROJPLANE_DIST * tanf(FOV / 2) * 2;
}

void	delete_cubdata(t_cubdata *cubdata)
{
	delete_all_assets(&cubdata->asset_list);
	mlx_delete_texture(cubdata->camera);
	mlx_delete_texture(cubdata->mmap);
	mlx_delete_image(cubdata->mlx, cubdata->main_img);
	mlx_terminate(cubdata->mlx);
	free(cubdata->player);
	free(cubdata->map->map_str);
	free(cubdata->map);
	free(cubdata);
}
