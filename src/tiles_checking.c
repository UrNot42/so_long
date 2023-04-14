/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:48:25 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/06 16:09:58 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	looking_at_coords(int *x, int *y, int face)
{
	if (face == SOUTH)
		(*y)++;
	if (face == NORTH)
		(*y)--;
	if (face == WEST)
		(*x)--;
	if (face == EAST)
		(*x)++;
}

int	tile_index(t_params *param, int x, int y)
{
	return (y * param->size.x + x);
}

int	rand_tile(t_params *param, int x, int y)
{
	unsigned int	seed;

	seed = (unsigned int)tile_index(param, x, y);
	return (rand_r(&seed));
}

bool	needs_bgd(char tile)
{
	if (tile == EMPTY_TILE
		|| tile == KEY_TILE
		|| tile == WALL_TILE_2
		|| tile == CHICKEN_TILE
		|| tile == STONE_TILE
		|| tile == EXIT_TILE)
		return (false);
	return (true);
}
