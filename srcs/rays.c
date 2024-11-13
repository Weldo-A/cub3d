/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:00:54 by abernade          #+#    #+#             */
/*   Updated: 2024/11/13 18:22:37 by abernade         ###   ########.fr       */
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
	// static int once = 0;
	float	x;
	float	y;
	int		dof;
	char	elem;

	if (ray->slope == INFINITY && ray->slope == NAN)
	{
		ray->hit_v = false;
		return ;
	}
	dof = 0;
	x = floorf(originx) + (ray->step_x > 0.0f);
	y = originy + ray->slope * (x - originx);
	elem = map_element_at_pos(map, x + 0.01f * ray->step_x, y + 0.01f * ray->step_y);
	// if (once < 540)
	// {
	// 	printf("RAY\t%d\n", once);
	// 	printf("ray angle: %f\tray step x: %f\t ray step y: %f\n", ray->angle, ray->step_x, ray->step_y);
	// 	printf("originx: %f\toriginy: %f\tslope: %f\n", originx, originy, ray->slope);
	// 	printf("x: %f\ty: %f\t\n", x, y);
	// 	printf("elem: %c\t\n\n", elem);
	// }
	
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
	// once++;
}


static void	h_collision(float originx, float originy, t_map *map, t_ray *ray)
{
	static int once = 0;
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
	if (!once)
		printf("\n\nx: %f\ty: %f\txo: %f\n", x, y, xo);
	while (dof++ < 10)
	{
		if (map_element_at_pos(map, x, y + 0.1 * ray->step_y) == '1')
			break;
		x += xo;
		y += ray->step_y;
		if (!once)
			printf("\n\nx: %f\ty: %f\tdof: %d\n", x, y, dof);
	}
	ray->h_inter_x = x;
	ray->h_inter_y = y;
	ray->h_dist = cosf(ray->angle) * (x - originx) - \
 		sinf(ray->angle) * (y - originy);
	once++;
}

// static void	h_collision(float originx, float originy, t_map *map, t_ray *ray, t_cubdata *cub)
// {
// 	static int once = 0;
// 	float	x;
// 	float	y;
// 	float	xo;
// 	int		dof;
// 	char	elem;

// 	if (once == 0)
// 	{
// 		printf("RAY\t%d\n", once);
// 		printf("ray angle: %f\tray step x: %f\t ray step y: %f\n", ray->angle, ray->step_x, ray->step_y);
// 		printf("originx: %f\toriginy: %f\t\nslope: %f\tninv_slope: %f\n", originx, originy, ray->slope, ray->ninv_slope);
// 	}

// 	dof = 0;
// 	y = floorf(originy) + (ray->step_y > 0.0f);
// 	x = originx + ray->ninv_slope * (originy - y);
// 	elem = map_element_at_pos(map, x, y);
// 	xo = -ray->ninv_slope * ray->step_y;

// 	if (once == 0)
// 	{
// 		printf("FIRST STEP: x: %f\ty: %f\t\n", x, y);
// 		printf("elem: %c\n", elem);
// 		printf("x offset: %f\n", xo);
		
// 		float x2;
// 		float y2;
		
// 		x2 = (cub->mmap->width / 2) + \
// 			(x - cub->player->x) * MMAP_SQUARE_SIZE;
// 		y2 = (cub->mmap->height / 2) + \
// 			(y - cub->player->y) * MMAP_SQUARE_SIZE;
// 		printf("\n\n\n\nX2: %f, Y2 %f\n\n\n\n", x2, y2);
// 		if (once == 0)
// 			pixel_to_texture(cub->mmap, (int)x2, (int)y2, GREEN);

// 	}
// 	while (elem != '1' && elem && dof++ < 10)
// 	{
// 		x += xo;
// 		y += ray->step_y;
// 		elem = map_element_at_pos(map, x + 0.01f * ray->step_x, y + 0.01f * ray->step_y);
// 		printf("newx %f newy %f\n", x, y);
		
// 		float x2;
// 		float y2;

// 		x2 = (cub->mmap->width / 2) + \
// 			(x - cub->player->x) * MMAP_SQUARE_SIZE;
// 		y2 = (cub->mmap->height / 2) + \
// 			(y - cub->player->y) * MMAP_SQUARE_SIZE;
// 		printf("\n\n\n\nX2: %f, Y2 %f\n\n\n\n", x2, y2);
// 		if (once == 0)
// 			pixel_to_texture(cub->mmap, (int)x2, (int)y2, GREEN);
// 	}
// 	ray->hit_h = (elem == '1');
// 	ray->h_inter_x = x;
// 	ray->h_inter_y = y;
// 	ray->h_dist = cosf(ray->angle) * (x - originx) - \
// 		sinf(ray->angle) * (y - originy);

// 	if (once == 0)
// 	{
// 		printf("x: %f\ty: %f\t\n", x, y);
// 		printf("elem: %c\t\n\n", elem);
// 	}

// 	once++;
// 	if (once == 540)
// 		once = 0;
// }

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
	static int	once = 0; // debug
	int 	i;
	float	max_angle;
	float	min_angle;

    i = 0;
	max_angle = cub->player->angle + (FOV / 2.0f);
	min_angle = cub->player->angle - (FOV / 2.0f);
    while (i < CAMERA_W)
    {
		//ft_bzero(&cub->rays[i], sizeof(t_ray));
		update_ray(&cub->rays[i], max_angle, min_angle, i);
		v_collision(cub->player->x, cub->player->y, cub->map, &cub->rays[i]);
		h_collision(cub->player->x, cub->player->y, cub->map, &cub->rays[i]);
		// if (!once)	
		// {												// debug
		// 	printf("ray %d\tplayerx: %f\tplayery: %f\tplayer_angle: %f\n", \
		// 		i, cub->player->x, cub->player->y, cub->player->angle);
		// 	printf("\tangle %f\n\th_dist %f\tv_dist %f\n\n", \
		// 		cub->rays[i].angle, cub->rays[i].h_dist, cub->rays[i].v_dist);	// debug
		// }

		
		float x;
		float y;
		float ox;
		float oy;
		
		ox = cub->player->x - ((float)MMAP_WIDTH / 2.0f) / (float)MMAP_SQUARE_SIZE;
		oy = cub->player->y - ((float)MMAP_HEIGHT / 2.0f) / (float)MMAP_SQUARE_SIZE;
		x = (cub->rays[i].h_inter_x - ox) * (float)MMAP_SQUARE_SIZE;
		y = (cub->rays[i].h_inter_y - oy) * (float)MMAP_SQUARE_SIZE;
		if (i == 0)
		{
			if (!once)
			{
				printf("interx: %f\tintery: %f\n", cub->rays[i].h_inter_x, cub->rays[i].h_inter_y);
				printf("xo: %f\tyo: %f\n", ox, oy);
				printf("print to x: %d\ty: %d\n", (int)round(x), (int)round(y));
			}
			draw_line(cub->mmap->width / 2 + 1, cub->mmap->height / 2 + 1, \
				(int)round(x), (int)round(y), cub->mmap, GREEN);
		}
		i++;
    }
	once++; // debug
}
