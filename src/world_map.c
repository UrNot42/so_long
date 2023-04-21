/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:48:31 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/21 12:24:16 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*construct_path(const char *folder, int map_id)
{
	char	*id_str;
	char	*full_name;
	char	*path;

	id_str = ft_itoa(map_id);
	if (!id_str)
		return (NULL);
	full_name = ft_strjoin(id_str, MAP_EXTENSION);
	free(id_str);
	if (!full_name)
		return (NULL);
	path = ft_strjoin(folder, full_name);
	free(full_name);
	return (path);
}

bool	init_world_maps(const char *folder, t_map *world)
{
	int		count;
	char	*path;
	char	***maps;

	count = 0;
	maps = ft_calloc(2, sizeof(char **));
	path = construct_path(folder, 1);
	while (maps && path && init_map(path, &maps[count], 1))
	{
		count++;
		maps = ft_realloc(maps, sizeof(char **) * (count + 1),
				sizeof(char **) * (count));
		if (maps)
			maps[count] = 0;
		ft_printf(GREEN"found: "CYAN"%s\n"RESET, path);
		free(path);
		path = construct_path(folder, count + 1);
	}
	(free(path), world->nb_maps = count);
	world->maps = maps;
	return (count > 0 && world->maps);
}

bool	restart_world(t_params *prm, char *world)
{
	free_triple_str(prm->world.maps);
	if (!init_world_maps(world, &prm->world))
		return (false);
	prm->world.completed = 0;
	prm->world.left_lvl_id = 0;
	prm->world.player = 0;
	if (prm->world.lives < MAX_LIVES)
		prm->world.lives++;
	prm->world.state = 0;
	prm->world.dir = SOUTH;
	return (true);
}

void	display_world_map(t_params *prm)
{
	int	offset;

	if (!prm->drawn)
	{
		put_world_map(prm, &prm->world.pane, prm->world.left_lvl_id);
		offset = 0;
		if (prm->world.dir == EAST)
			offset = prm->imgs.player.size;
		if (prm->world.dir == WEST)
			offset = prm->imgs.player.size * 2;
		draw_image(prm, 8 + 32 * prm->world.player, 38 - 16,
			&prm->imgs.player.img[prm->imgs.player.size + offset - 1]);
		(print_screen(prm), prm->drawn = true);
	}
	if (!prm->world.lives || prm->world.completed == prm->world.nb_maps)
	{
		(darken_screen(prm, 3), print_final_screen(prm, !!prm->world.lives));
		if (!prm->world.lives
			|| prm->world.w_completed == prm->world.nb_worlds)
			close_game(prm);
		else if (++prm->world.w_completed < prm->world.nb_worlds
			&& restart_world(prm, prm->world.worlds[prm->world.w_completed]))
			return ;
	}
}

bool	start_game(t_params *param, char **worlds, int nb_worlds)
{
	if (init_world(param))
		return (close_game(param), false);
	param->world.worlds = worlds;
	param->world.nb_worlds = nb_worlds;
	param->world.w_completed = 0;
	param->state = WORLD_MAP_STATE;
	if (!init_world_maps(worlds[0], &param->world))
		return (close_game(param), false);
	start_mlx_loop_hooks(param);
	return (true);
}
