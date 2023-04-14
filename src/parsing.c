/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 02:55:57 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/14 01:06:28 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	fill_map(char ***map, int fd)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	*map = NULL;
	buffer = get_next_line(fd);
	if (!buffer)
		return (false);
	while (buffer)
	{
		(*map) = ft_realloc(*map,
				sizeof(char *) * (i + 2), sizeof(char *) * i);
		if (!(*map))
			return (free_double_str(*map), false);
		(*map)[i] = buffer;
		(*map)[i][ft_strlen(buffer) - 1] = 0;
		j = -1;
		while ((*map)[i][++j])
			if (!is_tile((*map)[i][j]))
				return (free_double_str(*map), false);
		i++;
		buffer = get_next_line(fd);
	}
	return (true);
}

bool	init_map(char *file, char ***map, bool silenced)
{
	int	fd;
	int	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(&file[len - 4], ".ber", 4))
		return (error_msg(6), false);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return ((void)(silenced || (error_msg(6), 0)), false);
	if (!fill_map(map, fd) || !check_map_size(*map, &(t_coord){0, 0}))
		return (close(fd), (void)(silenced || (error_msg(7), 0)),
			free_double_str(*map), false);
	close(fd);
	return (true);
}

bool	parse_map(t_params *prm, char **map)
{
	if (!check_map_size(map, &prm->size)
		|| look_for_tile(map, STONE_SWORD_TILE, NULL) > 2)
		return (error_msg(7), false);
	prm->total_keys = look_for_tile(map, KEY_TILE, NULL)
		+ look_for_tile(map, CHEST_TILE, NULL)
		+ look_for_tile(map, DOOR_KEY_TILE, NULL);
	prm->map_save = copy_double_str(map);
	if (!prm->map_save)
	{
		free_double_str(map);
		error_msg(5);
		return (false);
	}
	if (prm->size.x && check_teleporters(map) && map_is_valid(prm, map))
	{
		do_chicken(prm, map);
		prm->map = map;
		return (true);
	}
	free_double_str(map);
	error_msg(7);
	return (false);
}

bool	map_is_valid(t_params *param, char **map)
{
	int		found_keys;
	char	**map_copy;
	char	**maps[2];

	found_keys = 0;
	maps[1] = map;
	if (!set_exit(map))
		return (false);
	if (!set_player(param, map))
		return (false);
	if (!copy_map(map, &map_copy, maps))
		return (false);
	param->p.sword = search_sword(maps, &param->p.o);
	if (!look_for_exit(maps, param->p.o.x, param->p.o.y, param->p.sword))
		return (error_msg(9), false);
	free_double_str(map_copy);
	if (!copy_map(map, &map_copy, maps))
		return (false);
	look_for_key(maps, &param->p.o, &found_keys, param->p.sword);
	free_double_str(map_copy);
	if (param->total_keys != found_keys || !param->total_keys)
		return (error_msg(10), false);
	return (true);
}

void	do_chicken(t_params *param, char **map)
{
	t_coord			pos;
	t_coord			rnd;
	unsigned int	i;
	unsigned int	rd;
	struct timeval	time;

	gettimeofday(&time, NULL);
	rd = (unsigned long)&param * time.tv_usec;
	if (look_for_tile(map, CHICKEN_TILE, NULL)
		|| look_for_tile(map, EMPTY_TILE, &pos) < 2
		|| 100 < ((rand_r(&rd) + 500) % 1000))
		return ;
	i = -1;
	while (++i < 100)
	{
		rnd.x = rand_r(&rd) % param->size.x;
		rnd.y = rand_r(&rd) % param->size.y;
		if (map[rnd.y][rnd.x] == EMPTY_TILE
			&& (rnd.x != param->p.o.x) && (rnd.y != param->p.o.y))
		{
			map[rnd.y][rnd.x] = CHICKEN_TILE;
			return ;
		}
	}
	map[pos.y][pos.x] = CHICKEN_TILE;
}
