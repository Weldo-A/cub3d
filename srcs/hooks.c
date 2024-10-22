/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 04:15:52 by abernade          #+#    #+#             */
/*   Updated: 2024/10/22 17:32:20 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cubdata *cubdata;

	cubdata = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(cubdata->mlx);
	if (keydata.key == MLX_KEY_T)
		printf("T was pressed\n");
}

void	generic_hook(void	*cubdata)
{
	handle_inputs(cubdata);
	render(cubdata);
}