/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:21:57 by abernade          #+#    #+#             */
/*   Updated: 2024/12/02 17:47:16 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	add_nearby_doors(t_cubdata *cub)
{
	int	x;
	int	y;

	y = cub->player->y - 1;
	while (y <= cub->player->y + 1)
	{
		x = cub->player->x - 1;
		while (x <= cub->player->x + 1)
		{
			if (map_element_at_pos(cub->map, y, x) == DOOR_CHAR)
				add_door_to_list(cub->active_doors);
			x++;
		}
		y++;
	}
}

static void	remove_inactive_doors(t_cubdata *cub)
{
	t_door	*door;

	door = cub->active_doors;
	while (door)
	{
		if (door->state <= 0)
			if (door->x < cub->player->x - 1 \
				|| door->x > cub->player->x + 1 \
				|| door->y < cub->player->y - 1 \
				|| door->y > cub->player->y + 1)
			{
				remove_door(&cub->active_doors, door);
			}
		door = door->next;
	}
}

static void	update_doors_state(t_cubdata *cub)
{
	t_door			*door;

	door = cub->active_doors;
	while (*door)
	{
		if (is_door_nearby(door, cub->player))
		{
			if (door->state < DOOR_OPEN_FRAMES)
				door->state++;
		}
		else
			door->state--;
		door = door->next;
	}
}

void	update_door_list(t_cubdata *cub)
{
	add_nearby_doors(cub);
	remove_inactive_doors(cub);
	update_doors_state(cub->active_doors);
}