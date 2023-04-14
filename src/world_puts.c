/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_puts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:46:27 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/14 10:57:09 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_pad(t_params *prm, int pos)
{
	if (pos + prm->world.left_lvl_id >= 0
		&& pos + prm->world.left_lvl_id < prm->world.nb_maps)
		draw_image(prm, 8 + pos * 32, 35, &prm->world.pad.img[
			(prm->world.completed - prm->world.left_lvl_id) > pos]);
}

void	put_panel(t_params *prm, t_data img, int pos)
{
	draw_image(prm, pos * 32, 0, &img);
}

void	put_paths(t_params *prm, int left, int right)
{
	int	pos;

	if (left < 0)
		left = 0;
	if (!left)
		draw_image(prm, left++, 35, &prm->world.path);
	pos = left;
	while (((pos - 1) + prm->world.left_lvl_id < (pos - 1) + prm->world.nb_maps)
		&& (pos - 1) < right && pos < 4)
	{
		draw_image(prm, 24 + 32 * (pos - 1), 35, &prm->world.path);
		pos++;
	}
}

void	put_hearts(t_params *prm)
{
	int	pos;
	int	tmp;

	pos = 0;
	tmp = prm->mlx.pxl_size;
	prm->mlx.pxl_size = 6;
	while (pos < MAX_LIVES)
	{
		draw_image(prm, pos * 18 + 2, 2,
			&prm->world.heart.img[!((prm->world.lives - pos) > 0)]);
		pos++;
	}
	prm->mlx.pxl_size = tmp;
}

void	put_world_map(t_params *prm, t_sprit *sprite, int offset)
{
	if (offset < 0)
		offset += 300;
	put_panel(prm, sprite->img[offset % sprite->size], 0);
	put_panel(prm, sprite->img[(offset + 1) % sprite->size], 1);
	put_panel(prm, sprite->img[(offset + 2) % sprite->size], 2);
	put_paths(prm, (prm->world.left_lvl_id * -1) + 1, prm->world.nb_maps
		- prm->world.left_lvl_id - 1);
	put_pad(prm, 0);
	put_pad(prm, 1);
	put_pad(prm, 2);
	put_hearts(prm);
}
