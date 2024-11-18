/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weldo <weldo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:00:54 by abernade          #+#    #+#             */
/*   Updated: 2024/11/18 18:41:52 by weldo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static float remap(float n, float in_min, float in_max, \
	float out_min, float out_max)
{
	return ((n - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

static void	v_collision(float originx, float originy, t_map *map, t_ray *ray)
{
	float	x;
	float	y;
	float	yo;
	int		dof;

	if (ray->slope == INFINITY)
		return ;
	x = floorf(originx) + (ray->step_x > 0.0f);
	y = -ray->slope * (originx - x) + originy;
	yo = ray->step_x * ray->slope;
	dof = 0;
	while (dof++ < 10)
	{
		if (map_element_at_pos(map, x + 0.1f * ray->step_x, y) == '1')
			break;
		y += yo;
		x += ray->step_x;
	}
	ray->hit_v = (dof <= 10);
	if (ray->hit_v)
	{
		ray->v_inter_x = x;
		ray->v_inter_y = y;
		ray->v_dist = sqrtf((originx - x) * (originx - x) \
			+ (originy - y) * (originy - y));
	}
	else
		ray->v_dist = 1000000.0f;
}

static void	h_collision(float originx, float originy, t_map *map, t_ray *ray)
{
	float	x;
	float	y;
	float	xo;
	int		dof;

	if (ray->ninv_slope == INFINITY)
		return ;
	y = floorf(originy) + (ray->step_y > 0.0f);
	x = originx + ray->ninv_slope * (originy - y);
	xo = -ray->step_y * ray->ninv_slope;
	dof = 0;
	while (dof++ < 10)
	{
		if (map_element_at_pos(map, x, y + 0.1f * ray->step_y) == '1')
			break;
		x += xo;
		y += ray->step_y;
	}
	ray->hit_h = (dof <= 10);
	if (ray->hit_h)
	{
		ray->h_inter_x = x;
		ray->h_inter_y = y;
		ray->h_dist = sqrtf((originx - x) * (originx - x) \
			+ (originy - y) * (originy - y));
	}
	else
		ray->h_dist = 1000000.0f;
}

static void	update_ray(t_ray *ray, float max_angle, float min_angle, int i)
{
	ray->angle = remap(i, 0.0f, CAMERA_W - 1.0f, min_angle, max_angle);
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
	ray->hit_h = false;
	ray->hit_v = false;
}

void	update_rays(t_cubdata *cub)
{
	int 	i;
	float	max_angle;
	float	min_angle;

    i = 0;
	max_angle = cub->player->angle + (FOV / 2.0f);
	min_angle = cub->player->angle - (FOV / 2.0f);
    while (i < CAMERA_W)
    {
		update_ray(&cub->rays[i], max_angle, min_angle, i);
		v_collision(cub->player->x, cub->player->y, cub->map, &cub->rays[i]);
		h_collision(cub->player->x, cub->player->y, cub->map, &cub->rays[i]);
		i++;
	}
}
