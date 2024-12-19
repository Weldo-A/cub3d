/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 04:20:57 by abernade          #+#    #+#             */
/*   Updated: 2024/12/10 15:44:17 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static t_cubdata	*init_allocations(void)
{
	t_cubdata	*cubdata;

	cubdata = malloc(sizeof(t_cubdata));
	if (!cubdata)
		return (NULL);
	cubdata->map = malloc(sizeof(t_map));
	if (!cubdata->map)
	{
		free(cubdata);
		return (NULL);
	}
	cubdata->player = malloc(sizeof(t_player));
	if (!cubdata->player)
	{
		free(cubdata->player);
		free(cubdata->map);
		free(cubdata);
		return (NULL);
	}
	return (cubdata);
}

t_cubdata	*debug_data_init(int ac, char **av)
{
	t_cubdata	*cubdata;

	cubdata = init_allocations();
	if (!cubdata)
		return (NULL);
	cubdata->player->angle = M_3PI_2;
	cubdata->mmap_sqr_size = MMAP_SQUARE_SIZE;
	cubdata->asset_list = NULL;
	ft_bzero(cubdata->rays, sizeof(t_ray) * CAMERA_W);
	if (start_parsing(ac, av, &cubdata) == 1)
	{
		free(cubdata->player);
		free(cubdata->map);
		free(cubdata);
		exit(1);
	}
	return (cubdata);
}
