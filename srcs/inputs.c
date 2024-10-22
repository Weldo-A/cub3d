/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:32:25 by abernade          #+#    #+#             */
/*   Updated: 2024/10/23 00:38:56 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	forward(t_cubdata *cub)
{
	float	x;
	float	y;
	char	map_element;


	x = cub->player->x + POS_INCREMENT * cosf(cub->player->angle);
	y = cub->player->y + POS_INCREMENT * sinf(cub->player->angle);
	map_element = map_element_at_pos(cub, x, y);
	printf("%c\n", map_element);
	if (map_element == '0' || map_element == 'N')
	{
		cub->player->x = x;
		cub->player->y = y;
	}
}

static void	backward(t_cubdata *cub)
{
	float	x;
	float	y;
	char	map_element;

	x = cub->player->x - POS_INCREMENT * cosf(cub->player->angle);
	y = cub->player->y - POS_INCREMENT * sinf(cub->player->angle);
	map_element = map_element_at_pos(cub, x, y);
	if (map_element == '0')
	{
		cub->player->x = x;
		cub->player->y = y;
	}
}

void	input_check(t_cubdata *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_Q))
		cub->player->angle += ANGLE_INCREMENT;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_E))
		cub->player->angle -= ANGLE_INCREMENT;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		forward(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		backward(cub);
}
