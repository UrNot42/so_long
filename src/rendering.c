/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 06:49:30 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/07 12:54:59 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	next_frame(t_sprit *sprite)
{
	sprite->frame = (sprite->frame + 1) % sprite->size;
}

void	update_sprites(t_imgs *imgs)
{
	next_frame(&imgs->key);
	if (imgs->open)
		next_frame(&imgs->exit);
	next_frame(&imgs->enemy);
	next_frame(&imgs->mimic);
	next_frame(&imgs->ghost);
	next_frame(&imgs->a);
	next_frame(&imgs->b);
	next_frame(&imgs->t);
	next_frame(&imgs->x);
	next_frame(&imgs->y);
	next_frame(&imgs->z);
	next_frame(&imgs->player);
	if (imgs->apo)
	{
		next_frame(&imgs->wall_apo);
		next_frame(&imgs->grave);
	}
	else
	{
		next_frame(&imgs->chick);
		next_frame(&imgs->wall);
	}
}

void	update_map(t_params *prm, char **map)
{
	draw_map(prm, false);
	if (prm->to_animate[0].sprite)
		draw_animations(prm);
	draw_tile(prm, prm->p.o.x, prm->p.o.y, map[prm->p.o.y][prm->p.o.x]);
	draw_player(prm, prm->p.o.x, prm->p.o.y, prm->p.face);
	prm->drawn = true;
	prm->printed = false;
}

void	render_frames(t_params *param)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	param->time = time.tv_usec;
	if ((param->time - param->time_prev) < 0)
	{
		move_enemies(param, param->map);
		param->time_prev = 0;
	}
	if ((param->time - param->time_prev) > RENDER_TIME)
	{
		param->drawn = false;
		param->time_prev = param->time;
	}
	if (!param->drawn)
	{
		update_map(param, param->map);
		update_sprites(&param->imgs);
		update_anims(param->to_animate, param->map, param);
	}
	if (!param->printed)
	{
		(print_screen(param), print_moves(param, param->p.moves));
		param->printed = true;
	}
}
