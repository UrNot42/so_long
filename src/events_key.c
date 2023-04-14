/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 00:01:01 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/07 05:52:52 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	open_exit(t_params *param, t_player *p)
{
	t_coord	exit;

	look_for_tile(param->map, EXIT_TILE, &exit);
	param->imgs.open = true;
	draw_tile(param, exit.x, exit.y, EXIT_TILE);
	if (p->o.x == exit.x && p->o.y == exit.y)
		(win_msg(), finish_map(param, true));
}

/**
 * @brief Adds a key to the player's inventory and checks
 *	 if all keys are collected to open the exit.
 *
 * @param param game parameters struct.
 * @param p player struct.
 */

void	add_key(t_params *param, t_player *p)
{
	p->keys++;
	print_data(param);
	if (p->keys >= param->total_keys)
		open_exit(param, &param->p);
}

/**
 * @brief Takes a key at the player's position,
 *	 adds it to the player's inventory, and updates the game map.
 *
 * @param param Pointer to the game parameters struct.
 * @param p Pointer to the player struct.
 */
void	take_key(t_params *param, t_player *p)
{
	add_key(param, &param->p);
	param->map[p->o.y][p->o.x] = EMPTY_TILE;
	draw_bgd(param, p->o.x, p->o.y);
}

/**
 * @brief Opens the chest at the given position,
 *	 adds a key to the player's inventory,
 *	 and adds the chest image element to the animation queue.
 *
 * @param param Pointer to the game parameters struct.
 * @param x The x-coordinate of the position to open the chest.
 * @param y The y-coordinate of the position to open the chest.
 */
void	open_chest(t_params *param, int x, int y)
{
	add_key(param, &param->p);
	param->map[y][x] = OPENED_CHEST_TILE;
	add_element(param->to_animate, &param->imgs.chest, x, y);
}
