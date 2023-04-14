/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:32:00 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/07 11:55:14 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief This function draws a pixel on the screen.
 *
 * @param mlx The mlx object.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel.
 */
void	pixel_put(t_mlx *mlx, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < mlx->pxl_size)
	{
		j = 0;
		while (j < mlx->pxl_size)
		{
			my_mlx_pixel_put(mlx->data, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

/**
 * @brief This function gets the image data for a given tile.
 *
 * @param img The image structure.
 * @param tile The tile character.
 * @return The image data for the tile.
 */
t_data	*get_img_tp(t_imgs *img, char tile)
{
	if (tile == TP_PAD_A_TILE)
		return (&img->a.img[img->a.frame]);
	else if (tile == TP_PAD_B_TILE)
		return (&img->b.img[img->b.frame]);
	else if (tile == TP_PAD_T_TILE)
		return (&img->t.img[img->t.frame]);
	else if (tile == TP_PAD_X_TILE)
		return (&img->x.img[img->x.frame]);
	else if (tile == TP_PAD_Y_TILE)
		return (&img->y.img[img->y.frame]);
	else if (tile == TP_PAD_Z_TILE)
		return (&img->z.img[img->z.frame]);
	return (NULL);
}

/**
 * @brief This function gets the image data for a given tile and offset.
 *
 * @param img The image structure.
 * @param tile The tile character.
 * @param offset The offset.
 * @return The image data for the tile.
 */
t_data	*get_img(t_imgs *img, char tile, int offset)
{
	if (tile == EMPTY_TILE && !img->apo)
		return (&img->grass.img[img->grass.frame]);
	else if (tile == WALL_TILE && !img->apo)
		return (&img->wall.img[(img->wall.frame + offset) % img->wall.size]);
	else if (tile == WALL_TILE_2)
		return (&img->wall_broken);
	else if (tile == EXIT_TILE && !img->open)
		return (&img->exit_cls);
	else if (tile == EXIT_TILE && img->open)
		return (&img->exit.img[img->exit.frame]);
	else if (tile == KEY_TILE)
		return (&img->key.img[img->key.frame]);
	else if (tile == CHEST_TILE || (tile == MIMIC_TILE && img->apo))
		return (&img->chest.img[0]);
	else if (tile == OPENED_CHEST_TILE)
		return (&img->chest.img[img->chest.size - 1]);
	else if (tile == DOOR_TILE || tile == DOOR_KEY_TILE)
		return (&img->door.img[0]);
	else if (tile == OPENED_DOOR_TILE)
		return (&img->door.img[img->door.size - 1]);
	else if (tile == ENEMY_TILE)
		return (&img->enemy.img[(img->enemy.frame + offset) % img->enemy.size]);
	else if (is_tp_pad(tile))
		return (get_img_tp(img, tile));
	return (get_other_img(img, tile, offset));
}

/**
 * @brief Get the appropriate image data structure
 *	 based on the given tile and offset for non-standard tiles.
 *
 * @param img The image data structure.
 * @param tile The tile type.
 * @param offset The offset to use for the image.
 *
 * @return The image data structure of the given tile
 *	 type and offset for non-standard tiles.
 */
t_data	*get_other_img(t_imgs *img, char tile, int offset)
{
	if (tile == CHICKEN_TILE && !img->apo)
		return (&img->chick.img[img->chick.frame]);
	else if (tile == CHICKEN_TILE && img->apo)
		return (&img->grave.img[img->grave.frame]);
	else if (tile == WALL_TILE && img->apo)
		return (&img->wall_apo.img[(img->wall_apo.frame + offset)
				% img->wall_apo.size]);
	else if (tile == EMPTY_TILE && img->apo)
		return (&img->fire);
	else if (tile == DRINK_TILE)
		return (&img->drink);
	else if (tile == MIMIC_TILE && !img->apo)
		return (&img->mimic.img[(img->mimic.frame + offset) % img->mimic.size]);
	else if (tile == BIRD_TILE)
		return (&img->bird.img[(img->bird.frame + offset) % img->bird.size]);
	else if (tile == GHOST_TILE)
		return (&img->ghost.img[(img->ghost.frame + offset) % img->ghost.size]);
	else if (tile == STONE_SWORD_TILE)
		return (&img->stone.img[0]);
	else if (tile == STONE_TILE)
		return (&img->stone.img[img->stone.size - 1]);
	return (NULL);
}
