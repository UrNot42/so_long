/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:18:37 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/03 22:51:31 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	replace_moved_enemies(char **map, t_params *prm)
{
	t_coord	i;

	i.y = -1;
	while (++i.y < prm->size.y)
	{
		i.x = -1;
		while (++i.x < prm->size.x)
		{
			if (map[i.y][i.x] == MOVED_GHOST)
				map[i.y][i.x] = GHOST_TILE;
			if (map[i.y][i.x] == MOVED_BIRD)
				map[i.y][i.x] = BIRD_TILE;
		}
	}
	if (gets_killed(map, prm))
		return ;
}

int	check_around(t_coord pos, t_player p, t_coord size, int exclude)
{
	int		dir;

	if (pos.x < 0 || pos.y < 0 || pos.x >= size.x || pos.y >= size.y)
		return (0);
	dir = 0;
	dir |= SOUTH * (pos.y + 1 == p.o.y && pos.x == p.o.x
			&& exclude != SOUTH);
	dir |= NORTH * (pos.y - 1 == p.o.y && pos.x == p.o.x
			&& exclude != NORTH);
	dir |= EAST * (pos.y == p.o.y && pos.x + 1 == p.o.x
			&& exclude != EAST);
	dir |= WEST * (pos.y == p.o.y && pos.x - 1 == p.o.x
			&& exclude != WEST);
	return (dir);
}

int	move_ghost(t_coord i, t_params *prm, int call, int ldir)
{
	t_coord	pos;
	int		dir;

	if (call > 8 || is_hard_tile(prm->map[i.y][i.x]))
		return (0);
	dir = check_around(i, prm->p, prm->size, ldir);
	if (!dir)
	{
		dir |= SOUTH * move_ghost((t_coord){i.x, i.y + 1}, prm, call + 1,
				NORTH * !call + ldir) * !dir * (ldir != SOUTH);
		dir |= NORTH * move_ghost((t_coord){i.x, i.y - 1}, prm, call + 1,
				SOUTH * !call + ldir) * !dir * (ldir != NORTH);
		dir |= WEST * move_ghost((t_coord){i.x - 1, i.y}, prm, call + 1,
				EAST * !call + ldir) * !dir * (ldir != WEST);
		dir |= EAST * move_ghost((t_coord){i.x + 1, i.y}, prm, call + 1,
				WEST * !call + ldir) * !dir * (ldir != EAST);
	}
	if (!call && dir && looking_at(prm->map, i.x, i.y, dir) == EMPTY_TILE)
	{
		pos = (t_coord){i.x, i.y};
		prm->map[i.y][i.x] = EMPTY_TILE;
		looking_at_coords(&pos.x, &pos.y, dir);
		prm->map[pos.y][pos.x] = MOVED_GHOST;
	}
	return (!!dir);
}

int	move_bird(char **map, t_coord i)
{
	t_coord	pos;
	int		rnd;

	rnd = rand() % 5;
	if (rnd < 4 && looking_at(map, i.x, i.y, rnd + 1) == EMPTY_TILE)
	{
		pos.x = i.x;
		pos.y = i.y;
		map[i.y][i.x] = EMPTY_TILE;
		looking_at_coords(&pos.x, &pos.y, rnd + 1);
		map[pos.y][pos.x] = MOVED_BIRD;
	}
	return (0);
}

int	move_enemies(t_params *prm, char **map)
{
	t_coord	i;

	i.y = -1;
	while (++i.y < prm->size.y)
	{
		i.x = -1;
		while (++i.x < prm->size.x)
		{
			if (map[i.y][i.x] == BIRD_TILE)
				move_bird(map, i);
			if (map[i.y][i.x] == GHOST_TILE)
				move_ghost(i, prm, 0, 0);
		}
	}
	replace_moved_enemies(map, prm);
	return (0);
}
