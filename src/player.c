/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:49:31 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/12 18:05:16 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	move_player(t_params *param, t_player *p)
{
	param->mv_dir = (((param->mv_dir + 2 * param->p.drunk) - 1) % 4) + 1;
	if (!p->god && param->imgs.apo
		&& looking_at(param->map, p->o.x, p->o.y, param->mv_dir) == WALL_TILE)
		return (death_msg(4), finish_map(param, false), draw_map_image(param,
				p->o.x, p->o.y, &param->imgs.wall_apo.img[0]), false);
	if (!p->god && param->p.face == param->mv_dir
		&& is_hard_tile(looking_at(param->map, p->o.x, p->o.y, p->face)))
		return (false);
	param->p.face = param->mv_dir;
	draw_tile(param, p->o.x, p->o.y, param->map[p->o.y][p->o.x]);
	if (!p->god && is_hard_tile(
			looking_at(param->map, p->o.x, p->o.y, p->face)))
		return (draw_player(param, p->o.x, p->o.y, p->face),
			print_screen(param), false);
	change_player_pos(&param->p.o, param->mv_dir);
	torus(&param->p.o, &param->size);
	print_data(param);
	on_tile(param, p, param->map[p->o.y][p->o.x]);
	draw_player(param, p->o.x, p->o.y, p->face);
	print_screen(param);
	return (true);
}

/**
 * @brief Draws the player sprite on the screen.
 *
 * @param param Pointer to the program parameters.
 * @param x X-coordinate of the player's position.
 * @param y Y-coordinate of the player's position.
 * @param face Direction the player is facing.
 * @return void
 */
void	draw_player(t_params *param, int x, int y, int face)
{
	int	offset;

	offset = 0;
	if (param->p.invis)
		return ;
	if (face == SOUTH)
		offset = 0;
	if (face == EAST)
		offset = param->imgs.player.size;
	if (face == WEST)
		offset = param->imgs.player.size * 2;
	if (face == NORTH)
		offset = param->imgs.player.size * 3;
	offset += param->imgs.player.frame;
	draw_map_image(param, x, y,
		&param->imgs.player.img[offset]);
}

void	add_move(t_params *param)
{
	param->p.moves++;
	print_moves(param, param->p.moves);
}
