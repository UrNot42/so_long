/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:02:28 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/07 08:02:30 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// - (rand() % (param->time / 10000 + 1) * param->imgs.apo))
// - (cos(param->time / 10000 + 1) * param->disco))

/**
 * @brief Get the color from an image.
 *
 * @param color 32-bit integer value that will store the extracted color.
 * @param img string that contains pixel values stored in packs of 4 this way:
 *	[(0xbb), (0xgg), (0xrr), (0xaa), ...] .each hex value representing
 *	blue, green red and alpha
 * @param prm parameters structure.
 * @param offset specifies the offset from the start of the image data.
 */
void	get_color(uint32_t *color, char *img, t_params *prm, int offset)
{
	*color = (unsigned char)(img[offset] - prm->col_ofst) << prm->hex_b
		| (unsigned char)(img[offset + 1] - prm->col_ofst) << prm->hex_g
		| (unsigned char)(img[offset + 2] - prm->col_ofst) << prm->hex_r
		| (unsigned char)img[offset + 3] << prm->hex_a;
}

/**
 * @brief Find the pixel size for an image.
 *
 * @param mlx pointer to the MLX structure.
 * @param size coordinate structure that specifies the size of the image.
 * @param max coordinate structure that specifies the maximum size of the image.
 * @param cap specifies the maximum pixel size for the image.
 */
void	find_pxl_size(t_mlx *mlx, t_coord size, t_coord max, int cap)
{
	mlx->pxl_size = 1;
	while (((mlx->pxl_size + 1) * size.x < max.x)
		&& ((mlx->pxl_size + 1) * size.y < max.y)
		&& mlx->pxl_size < cap)
	{
		mlx->pxl_size++;
	}
}
