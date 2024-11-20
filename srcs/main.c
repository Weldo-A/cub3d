/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weldo <weldo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:36:03 by abernade          #+#    #+#             */
/*   Updated: 2024/11/20 14:03:28 by weldo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int ac, char **av)
{
	(void)ac; (void)av;
	t_cubdata	*cubdata;

	cubdata = debug_data_init();

	cubdata_mlx_init(cubdata);
	if (mlx_image_to_window(cubdata->mlx, cubdata->main_img, 0, 0) == -1)
		error_exit(MLX_ERR);
	mlx_key_hook(cubdata->mlx, &key_hook, cubdata);
	mlx_loop_hook(cubdata->mlx, &generic_hook, cubdata);
	mlx_loop(cubdata->mlx);
	delete_cubdata(cubdata);
	return (0);
}
