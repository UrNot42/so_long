/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:57:05 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/05 08:18:23 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	change_player_pos(t_coord *pos, int direction)
{
	if (direction == NORTH)
		pos->y--;
	if (direction == SOUTH)
		pos->y++;
	if (direction == WEST)
		pos->x--;
	if (direction == EAST)
		pos->x++;
}

void	torus(t_coord *pos, t_coord	*size)
{
	if (pos->x > size->x - 1)
		pos->x = 0;
	if (pos->x < 0)
		pos->x = size->x - 1;
	if (pos->y > size->y - 1)
		pos->y = 0;
	if (pos->y < 0)
		pos->y = size->y - 1;
}

char	looking_at(char **map, int x, int y, int face)
{
	looking_at_coords(&x, &y, face);
	return (map[y][x]);
}

void	get_tp(char **map, int *x, int *y)
{
	int		i;
	int		j;
	char	tile;

	tile = map[*y][*x];
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == tile && (i != *y || j != *x))
			{
				*y = i;
				*x = j;
				return ;
			}
			j++;
		}
		i++;
	}
}
