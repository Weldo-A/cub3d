/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 04:20:57 by abernade          #+#    #+#             */
/*   Updated: 2024/12/18 15:40:45 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_cubdata	*data_init(int ac, char **av)
{
	t_cubdata	*cubdata;

	cubdata = malloc(sizeof(t_cubdata));
	cubdata->map = malloc(sizeof(t_map));
	cubdata->player = malloc(sizeof(t_player));
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
