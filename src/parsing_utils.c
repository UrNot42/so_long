/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:37:43 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/14 09:52:06 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map_size(char **map, t_coord *size)
{
	int	i;
	int	j;

	size->x = (int)ft_strlen(map[0]);
	if (size->x < 2)
		return (0);
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != size->x
			|| !is_wall_tile(map[i][0]) || !is_wall_tile(map[i][size->x - 1]))
			return (0);
		j = -1;
		while (++j < size->x - 1)
			if (!is_tile(map[i][j])
				|| (((i == 0 || !map[i + 1]) && !is_hard_tile(map[i][j]))))
				return (0);
		i++;
	}
	size->y = i;
	return (size->y >= 3);
}

bool	check_teleporters(char **map)
{
	int	tp[6];
	int	i;
	int	j;

	i = 0;
	while (i < 6)
		tp[i++] = 0;
	i = 0;
	while (map[i])
	{
		j = -1;
		while (map[i][++j])
			if (is_tp_pad(map[i][j]))
				tp[is_tp_pad(map[i][j]) - 1]++;
		++i;
	}
	i = -1;
	while (++i < 6)
		if (tp[i] && tp[i] != 2)
			return (error_msg(11), false);
	return (true);
}

bool	search_sword(char ***map, t_coord *pos)
{
	char	**map_copy;
	char	**tmp;
	bool	sword;

	map_copy = copy_double_str(map[0]);
	if (!map_copy)
		return (error_msg(5), false);
	tmp = map[0];
	map[0] = map_copy;
	sword = look_for_sword(map, pos->x, pos->y);
	free_double_str(map[0]);
	map[0] = tmp;
	return (sword);
}

/**
 * @brief checks if a sword is pickable without touching any enemies
 *
 *
 * @param map the 2d array where we look for the word tile
 * @param x x pos where the search starts
 * @param y y pos where the search starts
 * @return true
 * @return false
 */
bool	look_for_sword(char ***map, int x, int y)
{
	if (map[0][y][x] == STONE_SWORD_TILE)
		return (true);
	if (is_tp_pad(map[1][y][x]))
		get_tp(map[1], &x, &y);
	if (is_enemy(map[0][y][x]) || (map[0][y][x] != DOOR_TILE
		&& map[0][y][x] != DOOR_KEY_TILE
			&& is_hard_tile(map[0][y][x])))
		return (false);
	map[0][y][x] = WALL_TILE;
	if (look_for_sword(map, x, y - 1))
		return (true);
	else if (look_for_sword(map, x, y + 1))
		return (true);
	else if (look_for_sword(map, x - 1, y))
		return (true);
	else if (look_for_sword(map, x + 1, y))
		return (true);
	return (false);
}
