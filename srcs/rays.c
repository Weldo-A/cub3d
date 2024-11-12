/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:00:54 by abernade          #+#    #+#             */
/*   Updated: 2024/11/12 13:01:10 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <cub3d.h>

static float remap(float val, float in_min, float in_max, \
	float out_min, float out_max)
{
	return ((val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

void	update_rays(t_cubdata *cub)
{
	int i;
	float	max_angle;
	float	min_angle;

    i = 0;
	max_angle = cub->player->angle + (FOV / 2);
	min_angle = cub->player->angle - (FOV / 2);
    while (i < CAMERA_W)
    {
		cub->rays[i].angle = remap(i, 0, CAMERA_W - 1, min_angle, max_angle);
		i++;
    }
}
