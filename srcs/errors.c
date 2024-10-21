/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:29:32 by abernade          #+#    #+#             */
/*   Updated: 2024/10/21 01:36:32 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	mlx_error_exit(int exitcode)
{
	write(2, mlx_strerror(mlx_errno), ft_strlen(mlx_strerror(mlx_errno)));
	exit(exitcode);
}

void	error_exit(error_code_t code)
{
	if (code == MLX_ERR)
		mlx_error_exit(code);
	
}
