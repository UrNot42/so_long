/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 03:25:36 by ulevallo          #+#    #+#             */
/*   Updated: 2023/03/27 03:27:11 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_key_tile(char tile)
{
	if (tile == KEY_TILE
		|| tile == CHEST_TILE
		|| tile == DOOR_KEY_TILE)
		return (true);
	return (false);
}

bool	is_enemy(char tile)
{
	if (tile == ENEMY_TILE
		|| tile == BIRD_TILE
		|| tile == GHOST_TILE)
		return (true);
	return (false);
}
