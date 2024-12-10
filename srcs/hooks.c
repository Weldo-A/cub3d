/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 04:15:52 by abernade          #+#    #+#             */
/*   Updated: 2024/12/10 14:46:20 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

extern int g_debug;

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cubdata	*cubdata;

	cubdata = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(cubdata->mlx);
}

static void	mouse_check(t_cubdata *cub)
{
	static int		changes = 0;
	static int32_t	oldx = 0;
	int32_t			x;
	int32_t			y;

	mlx_get_mouse_pos(cub->mlx, &x, &y);
	(void)y;
	if (changes < 3 && oldx != x)
		changes++;
	else
		cub->player->angle += (x - oldx) * MOUSE_ANGLE_RATIO;
	oldx = x;
	if (cub->player->angle < 0)
		cub->player->angle += 2.0f * M_PI;
	else if (cub->player->angle > 2.0f * M_PI)
		cub->player->angle -= 2.0f * M_PI;
}

void	generic_hook(void	*cubdata)
{
	static int debug_cd = 0;

	if (g_debug)
	{
		debug_cd = 30;
		g_debug = 0;
	}

	if (mlx_is_key_down(((t_cubdata *)cubdata)->mlx, MLX_KEY_P) && !debug_cd)
		g_debug = 1;

	if (debug_cd)
		debug_cd--;
	
	update_door_list(cubdata);
	input_check(cubdata);
	mouse_check(cubdata);
	update_rays(cubdata);
	render(cubdata);
}
