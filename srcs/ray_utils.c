/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:02:59 by abernade          #+#    #+#             */
/*   Updated: 2024/12/04 01:55:43 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	save_v_inter(t_ray *ray, t_point *point, t_player_data *p)
{
	ray->v_inter_x = point->x;
	ray->v_inter_y = point->y;
	ray->v_dist = sqrtf((p->x - point->x) * (p->x - point->x) \
		+ (p->y - point->y) * (p->y - point->y));
}

void	save_h_inter(t_ray *ray, t_point *point, t_player_data *p)
{
	ray->h_inter_x = point->x;
	ray->h_inter_y = point->y;
	ray->h_dist = sqrtf((p->x - point->x) * (p->x - point->x) \
		+ (p->y - point->y) * (p->y - point->y));
}
