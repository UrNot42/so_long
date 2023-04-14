/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:10:51 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/07 10:01:58 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Handles events when the player steps on a tile.
 *
 * @param prm Pointer to the game parameters struct.
 * @param p Pointer to the player struct.
 * @param tile Character representing the type of tile the player stepped on.
 */
void	on_tile(t_params *prm, t_player *p, char tile)
{
	if (is_tp_pad(tile))
		get_tp(prm->map, &p->o.x, &p->o.y);
	if (!p->god && is_enemy(tile))
		(death_msg(tile), (finish_map(prm, false)));
	if (!p->god && (tile == WALL_TILE || tile == CHEST_TILE
			|| tile == OPENED_CHEST_TILE || tile == MIMIC_TILE
			|| tile == WALL_TILE_2))
		(death_msg(tile), finish_map(prm, false), draw_map_image(prm,
				prm->p.o.x, prm->p.o.y, get_img(&prm->imgs,
					prm->map[prm->p.o.y][prm->p.o.x], 0)));
	if (!prm->imgs.apo && tile == CHICKEN_TILE)
		kill_chicken(prm);
	if (tile == KEY_TILE)
		take_key(prm, p);
	if (tile == DRINK_TILE)
		drink_bottle(prm, p->o.x, p->o.y);
	if (tile == EXIT_TILE && prm->imgs.open)
		(win_msg(), finish_map(prm, true));
}

/**
 * @brief Enables or disables the god mode
 * 	and starts the events coresponding to the player's tile
 *
 * @param param Pointer to the game parameters struct.
 */
void	god_mode(t_params *param)
{
	param->p.god = (param->p.god + 1) % 2;
	on_tile(param, &param->p, param->map[param->p.o.y][param->p.o.x]);
}

/**
 * @brief rotates the player clockwise or counter clockwise
 *
 * @param prm pointer to the game variables structure
 * @param p player structure
 * @param dir spining direction
 */
void	spin_player(t_params *prm, t_player *p, int dir)
{
	p->face = ((p->face + 2 * dir) % 4) + 1;
	draw_tile(prm, prm->p.o.x, prm->p.o.y,
		prm->map[prm->p.o.y][prm->p.o.x]);
	draw_player(prm, p->o.x, p->o.y, p->face);
	print_screen(prm);
}

/**
 * @brief Increment the player's drunk level
 *	and remove the bottle from the game map.
 *
 * @param param A pointer to the game's parameters struct.
 * @param x The x-coordinate of the bottle's position in the game map.
 * @param y The y-coordinate of the bottle's position in the game map.
*/
void	drink_bottle(t_params *param, int x, int y)
{
	param->p.drunk++;
	param->map[y][x] = EMPTY_TILE;
}
