/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 03:51:08 by abernade          #+#    #+#             */
/*   Updated: 2024/10/21 04:20:10 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

mlx_texture_t	*new_texture(uint32_t width, uint32_t height)
{
	mlx_texture_t	*texture;

	texture = malloc(sizeof(mlx_texture_t));
	if (!texture)
		exit(1);
	texture->width = width;
	texture->height = height;
	texture->bytes_per_pixel = 4;
	texture->pixels = malloc(sizeof(uint8_t) * 4 * width * height);
	if (!texture->pixels)
		exit(1);
	ft_bzero(texture->pixels, sizeof(uint8_t) * 4 * width * height);
	return(texture);
}
