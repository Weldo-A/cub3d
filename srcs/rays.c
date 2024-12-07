/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:00:54 by abernade          #+#    #+#             */
/*   Updated: 2024/11/20 17:38:01 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	v_collision(float px, float py, t_map *map, t_ray *ray)
{
	float	x;
	float	y;
	float	yo;
	int		dof;

	if (ray->slope == INFINITY)
		return ;
	x = floorf(px) + (ray->step_x > 0.0f);
	y = -ray->slope * (px - x) + py;
	yo = ray->step_x * ray->slope;
	dof = 0;
	ray->v_dist = 1000000.0f;
	while (dof++ < 15)
	{
		if (map_element_at_pos(map, x + 0.1f * ray->step_x, y) == '1')
			break ;
		y += yo;
		x += ray->step_x;
	}
	if (dof <= 15)
	{
		ray->v_inter_x = x;
		ray->v_inter_y = y;
		ray->v_dist = sqrtf((px - x) * (px - x) + (py - y) * (py - y));
	}
}

static void	h_collision(float px, float py, t_map *map, t_ray *ray)
{
	float	x;
	float	y;
	float	xo;
	int		dof;

	if (ray->ninv_slope == INFINITY)
		return ;
	y = floorf(py) + (ray->step_y > 0.0f);
	x = px + ray->ninv_slope * (py - y);
	xo = -ray->step_y * ray->ninv_slope;
	dof = 0;
	ray->h_dist = 1000000.0f;
	while (dof++ < 15)
	{
		if (map_element_at_pos(map, x, y + 0.1f * ray->step_y) == '1')
			break ;
		x += xo;
		y += ray->step_y;
	}
	if (dof <= 15)
	{
		ray->h_inter_x = x;
		ray->h_inter_y = y;
		ray->h_dist = sqrtf((px - x) * (px - x) + (py - y) * (py - y));
	}
}

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
		ray->step_x = 1.0f;
	else
		ray->step_x = -1.0f;
	if (ray->angle < M_PI)
		ray->step_y = 1.0f;
	else
		ray->step_y = -1.0f;
}

static void	update_ray(t_cubdata *cub, int idx)
{
	float	discard;

	if (cub->rays[idx].v_dist < cub->rays[idx].h_dist)
	{
		if (cub->rays[idx].angle > M_PI_2 && cub->rays[idx].angle < M_3PI_2)
			cub->rays[idx].wall_tx = get_asset(cub->asset_list, EAST_TX);
		else
			cub->rays[idx].wall_tx = get_asset(cub->asset_list, WEST_TX);
		cub->rays[idx].offset = modff(cub->rays[idx].v_inter_y, &discard);
	}
	else
	{
		if (cub->rays[idx].angle < M_PI)
			cub->rays[idx].wall_tx = get_asset(cub->asset_list, NORTH_TX);
		else
			cub->rays[idx].wall_tx = get_asset(cub->asset_list, SOUTH_TX);
		cub->rays[idx].offset = modff(cub->rays[idx].h_inter_x, &discard);
	}
	(void)discard;
}

void	update_rays(t_cubdata *cub)
{
	int	i;

	i = 0;
	while (i < CAMERA_W)
	{
		prepare_ray(&cub->rays[i], cub->projplane_w, cub->player->angle, i);
		v_collision(cub->player->x, cub->player->y, cub->map, &cub->rays[i]);
		h_collision(cub->player->x, cub->player->y, cub->map, &cub->rays[i]);
		update_ray(cub, i);
		i++;
	}
}
