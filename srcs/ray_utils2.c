/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:20:18 by abernade          #+#    #+#             */
/*   Updated: 2024/12/17 14:44:10 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	update_ray_door(t_cubdata *cub, int idx, char ray_type)
{
	t_door	*door;
	float	door_state;
	float	discard;

	cub->rays[idx].wall_tx = get_asset(cub->asset_list, DOOR_TX);
	if (ray_type == 'v')
		door = search_door(cub->active_doors, cub->rays[idx].v_inter_x, \
			cub->rays[idx].v_inter_y);
	else
		door = search_door(cub->active_doors, cub->rays[idx].h_inter_x, \
			cub->rays[idx].h_inter_y);
	if (!door)
		door_state = 0;
	else
		door_state = door->state;
	if (ray_type == 'v')
		cub->rays[idx].offset = modff(cub->rays[idx].v_inter_y, &discard) \
			- ((float)door_state / DOOR_OPEN_FRAMES);
	else
		cub->rays[idx].offset = modff(cub->rays[idx].h_inter_x, &discard) \
			- ((float)door_state / DOOR_OPEN_FRAMES);
	(void)discard;
}

static void	update_ray_wall(t_cubdata *cub, int idx, char ray_type)
{
	float	discard;

	if (ray_type == 'v')
	{
		if (cub->rays[idx].angle > M_PI_2 && cub->rays[idx].angle < M_3PI_2)
			cub->rays[idx].wall_tx = get_asset(cub->asset_list, WEST_TX);
		else
			cub->rays[idx].wall_tx = get_asset(cub->asset_list, EAST_TX);
		cub->rays[idx].offset = modff(cub->rays[idx].v_inter_y, &discard);
	}
	else
	{
		if (cub->rays[idx].angle < M_PI)
			cub->rays[idx].wall_tx = get_asset(cub->asset_list, SOUTH_TX);
		else
			cub->rays[idx].wall_tx = get_asset(cub->asset_list, NORTH_TX);
		cub->rays[idx].offset = modff(cub->rays[idx].h_inter_x, &discard);
	}
	(void)discard;
}

void	update_ray_v(t_cubdata *cub, int idx)
{
	int		x;

	x = cub->rays[idx].v_inter_x + 0.01f * cub->rays[idx].step_x;
	if (map_element_at_pos(cub->map, x, cub->rays[idx].v_inter_y) \
		== DOOR_CHAR_Y)
		update_ray_door(cub, idx, 'v');
	else
		update_ray_wall(cub, idx, 'v');
}

void	update_ray_h(t_cubdata *cub, int idx)
{
	int		y;

	y = cub->rays[idx].h_inter_y + 0.01f * cub->rays[idx].step_y;
	if (map_element_at_pos(cub->map, cub->rays[idx].h_inter_x, y) \
		== DOOR_CHAR_X)
		update_ray_door(cub, idx, 'h');
	else
		update_ray_wall(cub, idx, 'h');
}
