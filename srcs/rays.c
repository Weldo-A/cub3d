/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:00:54 by abernade          #+#    #+#             */
/*   Updated: 2024/11/12 18:03:23 by abernade         ###   ########.fr       */
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
	int		dof;
	char	elem;

	if (ray->slope != INFINITY && ray->slope != NAN)
	{
		ray->hit_v = false;
		return ;
	}
	dof = 0;
	x = floorf(originx) + (ray->step_x > 0.0f);
	y = originy + ray->slope * (ray->slope * (x - originx));
	elem = map_element_at_pos(map, x, y);
	while (elem && elem != '1' && dof++ < 10)
	{
		x += ray->step_x;
		y += ray->slope * ray->step_y;
		elem = map_element_at_pos(map, x, y);
	}
	ray->hit_v = (elem == '1');
	ray->v_inter_x = x;
	ray->v_inter_y = y;
	ray->v_dist = cosf(ray->angle) * (x - originx) - \
		sinf(ray->angle) * (y - originy);
}

static void	h_collision(float originx, float originy, t_map *map, t_ray *ray)
{
	float	x;
	float	y;
	int		dof;
	char	elem;

	dof = 0;
	y = floorf(originy) + (ray->step_y > 0.0f);
	x = originx + ray->inv_slope * (y - originy);
	elem = map_element_at_pos(map, x, y);
	while (elem && elem != '1' && dof++ < 10)
	{
		x += ray->inv_slope * ray->step_y;
		y += ray->step_y;
		elem = map_element_at_pos(map, x, y);
	}
	ray->hit_h = (elem == '1');
	ray->h_inter_x = x;
	ray->h_inter_y = y;
	ray->h_dist = cosf(ray->angle) * (x - originx) - \
		sinf(ray->angle) * (y - originy);
}

static void	update_ray(t_ray *ray, float max_angle, float min_angle, int i)
{
	ray->angle = remap(i, 0.0f, CAMERA_W - 1.0f, min_angle, max_angle);
	if (ray->angle > 2.0f * M_PI)
		ray->angle -= 2.0f * M_PI;
	else if (ray->angle < 0.0f)
		ray->angle += 2.0f * M_PI;
	ray->slope = tanf(ray->angle);
	if (ray->slope != INFINITY && ray->slope != NAN)
		ray->inv_slope = 1.0f / ray->slope;
	else
		ray->inv_slope = 0.0f;
	if (ray->angle < M_PI_2 || ray->angle > M_3PI_2)
		ray->step_x = 1.0f;
	else
		ray->step_x = -1.0f;
	if (ray->angle < M_PI)
		ray->step_y = 1.0f;
	else
		ray->step_y = -1.0f;
}

void	update_rays(t_cubdata *cub)
{
	static int	once = 0; // debug
	int 	i;
	float	max_angle;
	float	min_angle;

    i = 0;
	max_angle = cub->player->angle + (FOV / 2.0f);
	min_angle = cub->player->angle - (FOV / 2.0f);
    while (i < CAMERA_W)
    {
		ft_bzero(&cub->rays[i], sizeof(t_ray));
		update_ray(&cub->rays[i], max_angle, min_angle, i);
		v_collision(cub->player->x, cub->player->y, cub->map, &cub->rays[i]);
		h_collision(cub->player->x, cub->player->y, cub->map, &cub->rays[i]);
		if (!once)	
		{												// debug
			printf("ray %d\tplayerx: %f\tplayery: %f\tplayer_angle: %f\n", \
				i, cub->player->x, cub->player->y, cub->player->angle);
			printf("\tangle %f\n\th_dist %f\tv_dist %f\n\n", \
				cub->rays[i].angle, cub->rays[i].h_dist, cub->rays[i].v_dist);	// debug
		}
		i++;
    }
	once = 1; // debug
}
