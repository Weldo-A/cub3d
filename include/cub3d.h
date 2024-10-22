/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:19:44 by abernade          #+#    #+#             */
/*   Updated: 2024/10/22 04:18:52 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <MLX42.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> // TO BE DELETED


# define CAMERA_W 540
# define CAMERA_H 360
# define WINDOW_W 1080
# define WINDOW_H 720
# define MMAP_WIDTH 200
# define MMAP_HEIGHT 200
# define MMAP_X 0
# define MMAP_Y (CAMERA_H - MMAP_HEIGHT)
# define MMAP_SQUARE_SIZE 25
# define MMAP_PIXEL_STEP (float)(1 / MMAP_SQUARE_SIZE)

	// Colors //
# define MMAP_COLOR_1 0x2E3B56FF
# define MMAP_COLOR_0 0xFFFFFFFF

// DEBUG SECTION, TO BE DELETED
/*
String equivalent to a simple valid map

111111
100101
101001
1100N1
111111
*/
# define MAP_DEBUG "111111\n100101\n101001\n1100N1\n111111"
# define FLOOR_DEBUG 0x845207FF
# define CEILING_DEBUG 0x2D2D2DFF

typedef enum error_code
{
	MLX_ERR = 1,
	MALLOC_ERR = 2
} error_code_t;

/**
 * @param x x coordinate of the player
 * @param y y coordinate of the player
 * @param angle Orientation of the player in radiant
 */
typedef struct	s_player_data
{
	float	x;
	float	y;
	float	angle;
}	t_player_data;

/**
 * @param map_str String format of the map
 * @param width
 * @param height
 */
typedef struct	s_map
{
	char		*map_str;
	uint32_t	width;
	uint32_t	height;
}	t_map;

/**
 * Cub3d main data stucture
 *
 * @param mlx Main MLX handle
 * @param main_img MLX image of one game frame scaled at window's size
 * @param camera MLX texture in which is rendered the environment
 * @param mmap MLX texture of the minimap
 * @param player Contains infos about the player
 * @param map Contains infos about the map
 * @param floor_color, ceiling_color RGBA values used for the floor and ceiling
 * @param mmap_sqr_size Size in pixel of a square on the minimap texture
 */
typedef struct	s_cubdata
{
	mlx_t			*mlx;
	mlx_image_t		*main_img;
	mlx_texture_t	*camera;
	mlx_texture_t	*mmap;
	t_player_data	*player;
	t_map			*map;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	uint8_t			mmap_sqr_size;

	int				debug; // TO BE DELETED
}	t_cubdata;


//TO BE DELETED
t_cubdata	*debug_data_init(void);


	// Cubdata handles | cubdata.c //
/**
 * @brief Initialize all MLX-related members
 * 
 * @param cubdata Cub3d main data structure
 */
void	cubdata_mlx_init(t_cubdata *cubdata);

/**
 * @brief Free cubdata memory and everything it contains
 *
 * WARNING: Everything related to mlx will be inaccessible
 * and thus must be terminated / freed prior to calling this function
 * 
 * @param cubdata Cub3d main data structure
 */
void	delete_cubdata(t_cubdata *cubdata);


	// Hook functions for mlx | hook.c //
/**
 * @brief Key hook for mlx, called with every keypress
 * 
 * @param keydata Info on key, action, etc
 * @param cubdata Cub3d main data structure
 */
void	key_hook(mlx_key_data_t keydata, void *cubdata);

/**
 * @brief Generic hook for mlx, executed every frame.
 * Also used for continuous key pressing detection like directional inputs
 * 
 * @param cubdata Cub3d main data structure
 */
void	generic_hook(void *cubdata);


	// Rendering | render.c //
/**
 * @brief Render one frame
 * 
 * @param cubdata Cub3d Main data structure
 */
void	render(t_cubdata *cubdata);


	// Error handeling | errors.c //
/**
 * @brief Handle error and exit
 * 
 * @param code Error code
 */
void	error_exit(error_code_t code);

	// Texture utils | texture_utils.c //
/**
 * @brief Creates an initialize an MLX texture structure
 * since MLX doesn't provide a way to create one without loading a png
 * 
 * @param width 
 * @param height 
 * @return mlx_texture_t* 
 */
mlx_texture_t	*new_texture(uint32_t width, uint32_t height);

/**
 * @brief Puts a pixel to a texture
 * 
 * @param tx MLX texture to write to
 * @param x Pixel's x coordinate
 * @param y Pixel's y coordinate
 * @param color Pixel color
 */
void	pixel_to_texture(mlx_texture_t *tx, uint32_t x, uint32_t y, uint32_t color);

/**
 * @brief Copy source texture to destination texture starting
 * at coordinates x y
 * 
 * @param dest Texture to write to
 * @param src Source texture
 * @param x x coordinate on `dest`
 * @param y y coordinate on `dest`
 */
void	merge_textures(mlx_texture_t *dest, mlx_texture_t *src, int x, int y);

/**
 * @brief Puts and scales camera texture to game main image
 * 
 * @param tx Texture containing player's rendered environment
 * @param img Image of the game frame
 */
void	camera_to_image(mlx_texture_t *tx, mlx_image_t *img);

/**
 * @brief Update minimap texture, centered on the player
 * 
 * @param cub Cub3d main data structure
 */
void	update_minimap_texture(t_cubdata *cub);

#endif
