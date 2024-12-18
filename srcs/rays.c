/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:00:54 by abernade          #+#    #+#             */
/*   Updated: 2024/12/17 14:35:56 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	prepare_ray(t_ray *ray, float projplane_w, float p_angle, int i)
{
	ray->angle = map_angle(i, projplane_w, p_angle);
	if (ray->angle > 2.0f * M_PI)
		ray->angle -= 2.0f * M_PI;
	else if (ray->angle < 0.0f)
		ray->angle += 2.0f * M_PI;
	ray->slope = tanf(ray->angle);
	if (ray->slope == 0.0f)
		ray->ninv_slope = INFINITY;
	else if (ray->slope != INFINITY && ray->slope != NAN && ray->slope)
		ray->ninv_slope = -1 / ray->slope;
	else
		ray->ninv_slope = 0.0f;
	if (ray->angle < M_PI_2 || ray->angle > M_3PI_2)
		ray->step_x = 0.5f;
	else
		ray->step_x = -0.5f;
	if (ray->angle < M_PI)
		ray->step_y = 0.5f;
	else
		ray->step_y = -0.5f;
}

static void	update_ray(t_cubdata *cub, int idx)
{
	if (cub->rays[idx].v_dist > 1000.f && cub->rays[idx].h_dist > 1000.f)
		cub->rays[idx].ray_hit = false;
	else
	{
		cub->rays[idx].ray_hit = true;
		if (cub->rays[idx].v_dist < cub->rays[idx].h_dist)
			update_ray_v(cub, idx);
		else
			update_ray_h(cub, idx);
	}
}

void	update_rays(t_cubdata *cub)
{
	int	i;

	i = 0;
	while (i < CAMERA_W)
	{
		prepare_ray(&cub->rays[i], cub->projplane_w, cub->player->angle, i);
		v_collision(cub, i);
		h_collision(cub, i);
		update_ray(cub, i);
		i++;
	}
}
