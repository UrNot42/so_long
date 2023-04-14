/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 04:00:54 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/05 12:38:43 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_wall_tile(char tile)
{
	if (tile == WALL_TILE
		|| tile == WALL_TILE_2
		|| tile == MIMIC_TILE
		|| tile == CHEST_TILE
		|| tile == STONE_SWORD_TILE
		|| tile == STONE_TILE
		|| tile == OPENED_CHEST_TILE)
		return (true);
	return (false);
}

bool	is_hard_tile(char tile)
{
	if (is_wall_tile(tile)
		|| tile == DOOR_KEY_TILE
		|| tile == DOOR_TILE)
		return (true);
	return (false);
}

int	is_tp_pad(char tile)
{
	if (tile == TP_PAD_A_TILE)
		return (1);
	if (tile == TP_PAD_B_TILE)
		return (2);
	if (tile == TP_PAD_T_TILE)
		return (3);
	if (tile == TP_PAD_X_TILE)
		return (4);
	if (tile == TP_PAD_Y_TILE)
		return (5);
	if (tile == TP_PAD_Z_TILE)
		return (6);
	return (0);
}

bool	is_empty_tile(char tile)
{
	if (tile == EMPTY_TILE
		|| tile == KEY_TILE
		|| tile == EXIT_TILE
		|| tile == PLAYER_TILE
		|| tile == DOOR_TILE
		|| tile == OPENED_DOOR_TILE
		|| tile == ENEMY_TILE
		|| tile == BIRD_TILE
		|| tile == GHOST_TILE
		|| tile == DRINK_TILE
		|| tile == CHICKEN_TILE
		|| is_tp_pad(tile))
		return (true);
	return (false);
}

bool	is_tile(char tile)
{
	if (is_hard_tile(tile)
		|| is_empty_tile(tile))
		return (true);
	return (false);
}
