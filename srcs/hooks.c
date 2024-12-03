/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 04:15:52 by abernade          #+#    #+#             */
/*   Updated: 2024/12/03 19:45:37 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cubdata	*cubdata;

	cubdata = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(cubdata->mlx);
}

static void	mouse_check(t_cubdata *cub)
{
	static int		changes = 0;
	static int32_t	oldx = 0;
	int32_t			x;
	int32_t			y;

	mlx_get_mouse_pos(cub->mlx, &x, &y);
	(void)y;
	if (changes < 3 && oldx != x)
		changes++;
	else
		cub->player->angle += (x - oldx) * MOUSE_ANGLE_RATIO;
	oldx = x;
	if (cub->player->angle < 0)
		cub->player->angle += 2.0f * M_PI;
	else if (cub->player->angle > 2.0f * M_PI)
		cub->player->angle -= 2.0f * M_PI;
}

void	generic_hook(void	*cubdata)
{
	update_door_list(cubdata);


	static int block = 0;
	if (mlx_is_key_down(((t_cubdata *)cubdata)->mlx, MLX_KEY_P) && !block)
	{
		printf("\nDoor list dump\n");
		t_door	*node;
		int		i = 0;
		node = ((t_cubdata *)cubdata)->active_doors;
		if (!node)
			printf("empty list\n");
		while (node)
		{
			printf("\nNODE %d\tx: %d\ty: %d\tstate: %d\n", i, node->x, node->y, node->state);
			node = node->next;
			i++;
		}
		block = 5;
	}
	if (block)
		block--;
	
	
	input_check(cubdata);
	mouse_check(cubdata);
	update_rays(cubdata);
	render(cubdata);
}
