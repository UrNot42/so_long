/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_searching.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 05:43:32 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/07 07:27:50 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	look_for_tile(char **map, char tile, t_coord *pos)
{
	int	i;
	int	j;
	int	found;

	found = 0;
	i = 0;
	while (map[i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == tile)
			{
				if (pos)
					pos->x = j;
				if (pos)
					pos->y = i;
				found++;
			}
		}
		i++;
	}
	return (found);
}

bool	look_for_exit(char **map[2], int x, int y, bool sword)
{
	if (map[0][y][x] == EXIT_TILE)
		return (true);
	if (is_tp_pad(map[1][y][x]))
		get_tp(map[1], &x, &y);
	if ((!sword && is_enemy(map[0][y][x])) || (map[0][y][x]
		!= DOOR_TILE && map[0][y][x] != DOOR_KEY_TILE
			&& is_hard_tile(map[0][y][x])))
		return (false);
	map[0][y][x] = WALL_TILE;
	if (look_for_exit(map, x, y - 1, sword))
		return (true);
	else if (look_for_exit(map, x, y + 1, sword))
		return (true);
	else if (look_for_exit(map, x - 1, y, sword))
		return (true);
	else if (look_for_exit(map, x + 1, y, sword))
		return (true);
	return (false);
}

void	look_for_key(char ***map, t_coord *pos, int *key, bool sword)
{
	if (is_tp_pad(map[1][pos->y][pos->x]))
		get_tp(map[1], &pos->x, &pos->y);
	if (is_key_tile(map[0][pos->y][pos->x]))
	{
		(*key)++;
		if (map[0][pos->y][pos->x] == CHEST_TILE)
			map[0][pos->y][pos->x] = WALL_TILE;
	}
	if ((!sword && is_enemy(map[0][pos->y][pos->x])) || (map[0][pos->y][pos->x]
		!= DOOR_TILE && map[0][pos->y][pos->x] != DOOR_KEY_TILE
			&& is_hard_tile(map[0][pos->y][pos->x])))
		return ;
	map[0][pos->y][pos->x] = WALL_TILE;
	look_for_key(map, &(t_coord){pos->x, pos->y - 1}, key, sword);
	look_for_key(map, &(t_coord){pos->x, pos->y + 1}, key, sword);
	look_for_key(map, &(t_coord){pos->x - 1, pos->y}, key, sword);
	look_for_key(map, &(t_coord){pos->x + 1, pos->y}, key, sword);
}

bool	set_exit(char **nap)
{
	int	found;

	found = look_for_tile(nap, EXIT_TILE, NULL);
	if (found > 1)
		return (error_msg(8), false);
	if (found <= 0)
		return (error_msg(9), false);
	return (true);
}

bool	set_player(t_params *param, char **map)
{
	int		found;
	t_coord	player;

	found = look_for_tile(map, PLAYER_TILE, &player);
	if (found > 1)
		return (ft_printf(RED"Error:\n\t"BLUE"More than one player\n"RESET),
			false);
	if (found <= 0)
		return (ft_printf(RED"Error:\n\t"BLUE"No player found\n"RESET), false);
	param->p.o.x = player.x;
	param->p.o.y = player.y;
	return (map[param->p.o.y][param->p.o.x] = EMPTY_TILE, true);
}
