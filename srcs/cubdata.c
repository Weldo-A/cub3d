/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubdata.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:38:37 by abernade          #+#    #+#             */
/*   Updated: 2024/10/21 06:09:23 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cubdata_mlx_init(t_cubdata *cubdata)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	cubdata->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!cubdata->mlx)
		error_exit(MLX_ERR);
	cubdata->main_img = mlx_new_image(cubdata->mlx, WIDTH, HEIGHT);
	if (!cubdata->main_img)
		error_exit(MLX_ERR);
	cubdata->camera = new_texture(WIDTH, HEIGHT);
	cubdata->minimap = new_texture(WIDTH, HEIGHT);
}

void	delete_cubdata(t_cubdata *cubdata)
{
	mlx_delete_image(cubdata->mlx, cubdata->main_img);
	mlx_terminate(cubdata->mlx);
	free(cubdata->map);
	free(cubdata);
}
