/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 04:15:52 by abernade          #+#    #+#             */
/*   Updated: 2024/12/11 15:10:08 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cubdata	*cubdata;

	cubdata = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(cubdata->mlx);
}

static void	mouse_check(t_cubdata *cub)
{
	static int		changes = 3;
	static int		diff = 0;
	static int32_t	oldx = 0;
	int32_t			x;
	int32_t			y;

	mlx_get_mouse_pos(cub->mlx, &x, &y);
	(void)y;
	if (changes > 0 && oldx != x)
		changes--;
	else if (x == oldx && !changes)
		cub->player->angle += diff * MOUSE_ANGLE_RATIO;
	else
		cub->player->angle += (x - oldx) * MOUSE_ANGLE_RATIO;
	diff = x - oldx;
	oldx = x;
	if (cub->player->angle < 0)
		cub->player->angle += 2.0f * M_PI;
	else if (cub->player->angle > 2.0f * M_PI)
		cub->player->angle -= 2.0f * M_PI;
}

static void	dump_rays(t_cubdata *cub)
{
	for(int i = 0; i < CAMERA_W; i++)
	{
		printf("\n---------------------- RAY %d ----------------------\n", i);
		printf("ray hit: %d\n", cub->rays[i].ray_hit);
		printf("v dist: %f\n", cub->rays[i].v_dist);
		printf("h dist: %f\n", cub->rays[i].h_dist);
	}
}

void	generic_hook(void	*cubdata)
{
	update_door_list(cubdata);
	input_check(cubdata);
	mouse_check(cubdata);
	update_rays(cubdata);

	static int	delay = 0;

	if (mlx_is_key_down(((t_cubdata*)cubdata)->mlx, MLX_KEY_P) && !delay)
	{
		delay = 30;
		dump_rays(cubdata);
	}
	if (delay)
		delay--;
	render(cubdata);
}
