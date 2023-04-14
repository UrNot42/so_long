/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:08:58 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/13 23:39:13 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int key, t_params *param)
{
	if (param->state == INGAME_STATE)
		return (key_press_game(key, param));
	if (param->state == PAUSED_STATE)
		return (key_press_pause(key, param));
	if (param->state == WORLD_MAP_STATE)
		return (key_press_world_map(key, param));
	if (param->state == FINAL_SCREEN_STATE && key == 'r')
		restart_game(param);
	if (param->state == FINAL_SCREEN_STATE && key != 0 && !param->world.active)
		close_game(param);
	if (param->state == FINAL_SCREEN_STATE && key != 0 && param->world.active)
		end_map(param);
	return (EXIT_SUCCESS);
}

bool	add_input(int new, int key[11])
{
	int	i;

	i = 10;
	while (i > 0)
	{
		key[i] = key[i - 1];
		i--;
	}
	key[0] = new;
	if (is_up(key[10]) && is_up(key[9]) && is_down(key[8])
		&& is_down(key[7]) && is_left(key[6]) && is_right(key[5])
		&& is_left(key[4]) && is_right(key[3]) && key[2] == 'b'
		&& key[1] == 'a' && is_start(key[0]))
		return (true);
	return (false);
}

int	key_press_world_map(int key, t_params *param)
{
	if (key == XK_Escape || key == 'q')
		close_game(param);
	else if (is_left(key) || is_right(key) || is_down(key))
	{
		param->drawn = false;
		if (((is_left(key)) && param->world.left_lvl_id > -2)
			|| (is_right(key) && (param->world.left_lvl_id
					< param->world.completed) && (param->world.left_lvl_id
					< param->world.nb_maps - 1)))
			param->world.left_lvl_id += 1 * is_right(key) - 1 * is_left(key);
		if (param->world.left_lvl_id <= 0)
			param->world.player = param->world.left_lvl_id * -1;
		param->world.dir = is_down(key) * SOUTH
			| is_right(key) * EAST | is_left(key) * WEST;
		param->world.state = param->world.left_lvl_id
			- (param->world.left_lvl_id < 0) * -param->world.player;
	}
	if (is_start(key))
		return (launch_map(param));
	return (EXIT_SUCCESS);
}

int	key_press_game(int key, t_params *param)
{
	if (key == XK_Escape)
		pause_game(param);
	else if (add_input(key, param->prev_input))
		god_mode(param);
	if (is_left(key))
		param->mv_dir = WEST;
	else if (is_right(key))
		param->mv_dir = EAST;
	else if (is_up(key))
		param->mv_dir = NORTH;
	else if (is_down(key))
		param->mv_dir = SOUTH;
	if (param->mv_dir && move_player(param, &param->p))
		add_move(param);
	if (is_start(key))
		trigger_event(param);
	if (key == 'i')
		param->p.invis = (param->p.invis + 1) % 2;
	else if (key == 'q' || key == 'e')
		spin_player(param, &param->p, key == 'e');
	else if (key == 'o' && param->p.drunk > 0)
		param->p.drunk--;
	param->mv_dir = 0;
	return (EXIT_SUCCESS);
}

int	key_press_pause(int key, t_params *param)
{
	bool	up_down;

	up_down = param->mlx.data->height * 2 > param->mlx.data->width;
	if (key == XK_Escape)
		param->state = INGAME_STATE;
	else if (add_input(key, param->prev_input))
		god_mode(param);
	if (!up_down && is_left(key) && param->button > 1)
		param->button = (param->button - 1) * -1;
	else if (!up_down && is_right(key) && param->button < 3)
		param->button = (param->button + 1) * -1;
	else if (up_down && is_up(key) && param->button > 1)
		param->button = (param->button - 1) * -1;
	else if (up_down && is_down(key) && param->button < 3)
		param->button = (param->button + 1) * -1;
	up_down = param->world.active;
	if ((is_start(key) && param->button == 1) || key == 'p')
		param->state = INGAME_STATE;
	if (((is_start(key) && param->button == 3) || key == 'q') && !up_down)
		close_game(param);
	if (((is_start(key) && param->button == 3) || key == 'q') && up_down)
		back_to_menu(param);
	if ((is_start(key) && param->button == 2) || key == 'r')
		restart_game(param);
	return (EXIT_SUCCESS);
}
