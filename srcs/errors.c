/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:29:32 by abernade          #+#    #+#             */
/*   Updated: 2024/11/05 16:46:19 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	print_err_msg(const char *str)
{
	write(2, str, ft_strlen(str));
}

void	error_exit(error_code_t code)
{
	if (code == MLX_ERR)
		print_err_msg(mlx_strerror(mlx_errno));
	else if (code == ASSET_NAME_ERR)
		print_err_msg("Error: Asset name already in use\n");
	else if (code == ASSET_NOT_FOUND)
		print_err_msg("Error: Asset not found\n");
	else if (code == ASSET_DELETE_ERR)
		print_err_msg("Error: Could not delete asset\n");
	exit(code);
}
