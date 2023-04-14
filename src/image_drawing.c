/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 04:15:31 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/07 08:03:06 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief draw an image on the screen at a certain position
 * scaling it by the pxl_size factor
 *
 * @param prm a pointer to the game structure
 * @param x pos x of the top left corner of where we start to draw
 * @param y pos y of the top left corner of where we start to draw
 * @param img said image to be printed on the screen
 */
void	draw_image(t_params *prm, int x, int y, t_data *img)
{
	int			i;
	int			j;
	uint32_t	color;

	i = -1;
	color = 0x0;
	while (++i < img->height)
	{
		j = -1;
		while (++j < img->width)
		{
			get_color(&color, img->addr, prm, (i * img->width * 4) + j * 4);
			if (color >> 24 != 0xff && (x + j) * prm->mlx.pxl_size
				< prm->mlx.data->width && (y + i) * prm->mlx.pxl_size
				< prm->mlx.data->height)
				pixel_put(&prm->mlx, (x + j) * prm->mlx.pxl_size,
					(y + i) * prm->mlx.pxl_size, color);
		}
	}
}

/**
 * @brief Draws the map on the screen.
 *
 * @param param Pointer to the program parameters.
 * @param just_sprites A flag indicating whether to draw only sprites or not.
 * @return void
 */
void	draw_map(t_params *param, bool just_sprites)
{
	int		i;
	int		j;

	i = 0;
	while (i < param->size.y)
	{
		j = 0;
		while (j < param->size.x)
		{
			if (!just_sprites || is_sprite(param->map[i][j]))
				draw_tile(param, j, i, param->map[i][j]);
			j++;
		}
		i++;
	}
	draw_player(param, param->p.o.x, param->p.o.y, param->p.face);
}

/**
 * @brief Draws the background image on the screen.
 *
 * @param prm Pointer to the program parameters.
 * @param x X-coordinate of the tile to draw the background on.
 * @param y Y-coordinate of the tile to draw the background on.
 * @return void
 */
void	draw_bgd(t_params *prm, int x, int y)
{
	if (prm->imgs.apo)
		draw_map_image(prm, x, y, &prm->imgs.fire);
	else
		draw_map_image(prm, x, y, &prm->imgs.bgd);
}

/**
 * @brief Draws a tile on the screen.
 *
 * @param prm Pointer to the program parameters.
 * @param x X-coordinate of the tile to draw.
 * @param y Y-coordinate of the tile to draw.
 * @param tile The type of tile to draw.
 * @return void
 */
void	draw_tile(t_params *prm, int x, int y, char tile)
{
	if (needs_bgd(tile))
		draw_bgd(prm, x, y);
	else
	{
		prm->imgs.grass.frame = rand_tile(prm, x, y) % (prm->imgs.grass.size);
		draw_map_image(prm, x, y,
			get_img(&prm->imgs, EMPTY_TILE, rand_tile(prm, x, y)));
	}
	draw_map_image(prm, x, y, get_img(&prm->imgs, tile, rand_tile(prm, x, y)));
}

/**
 * @brief Draws an image on the screen at a specific location.
 *
 * @param param Pointer to the program parameters.
 * @param x X-coordinate of the image's position.
 * @param y Y-coordinate of the image's position.
 * @param img Pointer to the image to draw.
 * @return void
 */
void	draw_map_image(t_params *param, int x, int y, t_data *img)
{
	param->col_ofst = rand() % (param->p.drunk * 10 + 1);
	draw_image(param, x * img->width, y * img->height, img);
}
