/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:19:44 by abernade          #+#    #+#             */
/*   Updated: 2024/11/07 12:09:44 by abernade         ###   ########.fr       */
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
#include <sys/time.h> // TO BE DELETED

# define M_3PI_2 M_PI + M_PI_2
# define M_2PI_3 2.09439510239319526264f

# define CAMERA_W 540
# define CAMERA_H 360
# define WINDOW_W 1080
# define WINDOW_H 720
# define MMAP_WIDTH 130
# define MMAP_HEIGHT 130
# define MMAP_X 0
# define MMAP_Y (CAMERA_H - MMAP_HEIGHT)
# define MMAP_SQUARE_SIZE 25
# define MMAP_PIXEL_STEP (float)(1 / (float)MMAP_SQUARE_SIZE)

	// Colors //
# define MMAP_COLOR_1 0x2E3B56FF
# define MMAP_COLOR_0 0xFFFFFFFF

	// Player movement //
# define ANGLE_INCREMENT 0.08f
# define POS_INCREMENT 0.02f
# define WALL_THICKNESS 0.3f // unused ?

	// Texture names and paths //
# define NORTH_TEXTURE "NO"
# define SOUTH_TEXTURE "SO" 
# define WEST_TEXTURE "WE"
# define EAST_TEXTURE "EA"
# define MMAP_PLAYER_ICON "MMAP_PLAYER_ICON"
# define MMAP_PLAYER_PATH "assets/circle1.png"

// DEBUG SECTION, TO BE DELETED
/*
String equivalent to a simple valid map

111111111
100101011
101001001
11000N011
111111111
*/
# define MAP_DEBUG "11111111110010101110100100111000N011111111111"
# define FLOOR_DEBUG 0x845207FF
# define CEILING_DEBUG 0x2D2D2DFF

typedef enum error_code
{
	MLX_ERR = 1,
	MALLOC_ERR,
	ASSET_NAME_ERR,
	ASSET_NOT_FOUND,
	ASSET_DELETE_ERR
}	error_code_t;

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
 * @param name String of the name of the asset, serves as identifier
 * @param tx Texture in which the asset will be loaded
 * @param next Next node of the list
 */
typedef struct	s_asset
{
	char			*name;
	mlx_texture_t	*tx;
	struct s_asset	*next;
}	t_asset;

typedef struct	s_ray
{
	float	angle;
	float	origin_x;
	float	origin_y;
	float	tmpx;
	float	tmpy;
} t_ray;

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
	t_asset			*asset_list;
	t_player_data	*player;
	t_map			*map;
	t_ray			rays[CAMERA_W];
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
 * @brief Copy source texture to destination texture at coordinates x y
 *
 * WARNING: Does not support partial transparency.
 * The destination value will simply be overridden, 
 * unless source pixel's alpha channel is strictly zero,
 * in which case the pixel will be ignored.
 *
 * @param dest Texture to write to
 * @param src Source texture
 * @param x x coordinate on `dest`
 * @param y y coordinate on `dest`
 */
void	merge_textures(mlx_texture_t *dest, mlx_texture_t *src, int x, int y);

/**
 * @brief Puts and scales a texture to an mlx image
 * 
 * @param tx Texture
 * @param img Image
 */
void	texture_to_image(mlx_texture_t *tx, mlx_image_t *img);

/**
 * @brief Update minimap texture, centered on the player
 * 
 * @param cub Cub3d main data structure
 */
void	update_minimap_texture(t_cubdata *cub);



	// Input functions | inputs.c //
/**
 * @brief Execute functions depending on keys being pressed
 * 
 * @param cubdata Cub3d main data structure
 */
void	input_check(t_cubdata *cubdata);



	// Asset handles | asset_handles.c //
/**
 * @brief Load a png asset into a texture and store it in a list
 * 
 * @param assets Pointer to a linked list of existing assets
 * @param path Path to a PNG file
 * @param name Name of the asset that will serves as identifier and sould be unique
 */
void	load_asset(t_asset **assets, const char *path, const char *name);

/**
 * @brief Delete an asset from the list
 * 
 * @param lst Pointer to a linked list of existing assets
 * @param name Name of the asset to delete
 */
void	delete_asset(t_asset **lst, char *name);

/**
 * @brief Delete all assets, sets the first node of the list to NULL
 * 
 * @param lst Pointer to a linked list of existing assets
 */
void	delete_all_assets(t_asset **lst);

/**
 * @brief Check if an asset with the specified name already exists
 * 
 * @param assets Linked list of existing assets
 * @param name Name of the asset
 * @return Boolean
 */
bool	asset_exists(t_asset *assets, const char *name);

/**
 * @brief Get an asset texture
 * 
 * @param assets Linked list of existing assets
 * @param name Name of the asset
 * @return const mlx_texture_t* 
 */
mlx_texture_t	*get_asset(t_asset *assets, char *name);


	// Various utils | utils.c //
/**
 * @brief Get a character on the map given x and y coordinates
 * 
 * @param cubdata Cub3d main data structure
 * @param x x coordinate
 * @param y y coordinate
 * @return The character on the map corresponding the x and y coordinate
 */
char	map_element_at_pos(t_cubdata *cubdata, float x, float y);

/**
 * @brief man 3 strcmp
 * 
 * @param s1 
 * @param s2 
 * @return int 
 */
int	ft_strcmp(const char *s1, const char *s2);

/**
 * @brief Get the color of a texture pixel at x, y coordinates
 *
 * @param tx MLX texture to get a color from
 * @param x x coordinate
 * @param y y coordinate
 * @return uint32_t 
 */
uint32_t	get_color(const mlx_texture_t *tx, int x, int y);

#endif
