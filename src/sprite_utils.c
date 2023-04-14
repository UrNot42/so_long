/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:51:47 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/06 21:39:31 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_sprite(char tile)
{
	if (tile == WALL_TILE
		|| tile == EXIT_TILE
		|| tile == KEY_TILE
		|| tile == CHICKEN_TILE
		|| tile == MIMIC_TILE
		|| is_enemy(tile)
		|| is_tp_pad(tile))
		return (true);
	return (false);
}
