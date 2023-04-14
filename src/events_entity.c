/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 00:12:22 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/05 11:26:23 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Trigger the mimic animation.
 *
 * @param param A pointer to the parameters structure.
 * @param x The x-coordinate of the mimic.
 * @param y The y-coordinate of the mimic.
 */
void	trigger_mimic(t_params *param, int x, int y)
{
	add_element(param->to_animate, &param->imgs.mimic_op, x, y);
}

/**
 * @brief Kill an enemy at the specified coordinates.
 *
 * @param param A pointer to the parameters structure.
 * @param x The x-coordinate of the enemy.
 * @param y The y-coordinate of the enemy.
 */
void	kill_enemy(t_params *param, int x, int y)
{
	param->map[y][x] = EMPTY_TILE;
	draw_tile(param, x, y, EMPTY_TILE);
	print_screen(param);
}

/**
 * @brief Kill the chicken and update the map.
 *
 * @param param A pointer to the parameters structure.
 */
void	kill_chicken(t_params *param)
{
	param->imgs.apo = true;
	print_map(param, false);
	param->time = 0;
	update_map(param, param->map);
}
