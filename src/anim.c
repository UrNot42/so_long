/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:06:22 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/05 13:49:08 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief tell if the evaluated tile is being animated or not
 *
 * @param anims the list of all animations
 * @param x coord x of the tile we are checking
 * @param y coord y of the tile we are checking
 * @return true when the tile is found to be animated
 * @return false when no animation is found at the coords
 */
bool	is_anim(t_anim *anims, int x, int y)
{
	int	i;

	i = 0;
	while (anims[i].sprite)
	{
		if (anims[i].pos.x == x
			&& anims[i].pos.y == y)
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief prints all the animations inside the
 *	to_animate element on the main image
 *
 * @param param contains the mlx pointer (for the screen)
 *	and the list of all going animations
 */
void	draw_animations(t_params *param)
{
	int		i;
	t_sprit	*temp;
	t_coord	pos;

	i = 0;
	while (param->to_animate[i].sprite)
	{
		pos = param->to_animate[i].pos;
		temp = param->to_animate[i].sprite;
		draw_bgd(param, pos.x, pos.y);
		draw_map_image(param, pos.x, pos.y,
			&temp->img[param->to_animate[i].frame]);
		i++;
	}
}

/**
 * @brief looks at the animation array and moves every element
 *	down inside said array by one from the up elemnt
 *
 * @param array contains all the animations
 * @param up the element from which you move the rest of the pile down
 */
void	lower_anim(t_anim array[100], int up)
{
	array[up].sprite = NULL;
	array[up].frame = 0;
	while ((up + 1) < 100 && array[up + 1].sprite)
	{
		array[up] = array[up + 1];
		array[up + 1].sprite = NULL;
		up++;
	}
}

/**
 * @brief updates the frames of every animation running in the array
	and runs the correct event when the animations are ending
 *
 * @param array contains all the animations
 * @param map the map containing all the tiles that can change with events
 * @param prm global parameter containing imgs the player and the size of the map
 */
void	update_anims(t_anim array[100], char **map, t_params *prm)
{
	int		i;
	char	tile;

	i = -1;
	while (array[++i].sprite)
	{
		array[i].frame++;
		if (array[i].frame >= array[i].sprite->size)
		{
			tile = map[array[i].pos.y][array[i].pos.x];
			if (tile == DOOR_TILE || tile == DOOR_KEY_TILE)
				map[array[i].pos.y][array[i].pos.x] = OPENED_DOOR_TILE * (tile
						== DOOR_TILE) + KEY_TILE * (tile == DOOR_KEY_TILE);
			if (tile == MIMIC_TILE && !prm->p.god
				&& check_around(array[i].pos, prm->p, prm->size, 0))
				(death_msg(MIMIC_TILE), finish_map(prm, false),
					draw_map_image(prm, array[i].pos.x, array[i].pos.y,
						&prm->imgs.mimic_op.img[prm->imgs.mimic_op.size - 1]));
			if (tile == MIMIC_TILE && (prm->imgs.apo || prm->p.god))
				map[array[i].pos.y][array[i].pos.x] = OPENED_CHEST_TILE;
			if (tile == STONE_SWORD_TILE)
				pickup_sword(prm, array[i].pos.x, array[i].pos.y);
			lower_anim(array, i--);
		}
	}
}

/**
 * @brief adds an element to be animated
 *	inside the array that contains the animations on top of the existing pile
 *
 * @param array list where the animations are stored
 * @param sprite address containing the images of the animations
 * @param x coord of the tile to be animated
 * @param y coord of the tile to be animated
 */
void	add_element(t_anim array[100], t_sprit *sprite, int x, int y)
{
	int	i;

	i = 0;
	while (i < 100)
	{
		if (!array[i].sprite)
		{
			if ((i + 1) < 100)
				array[i + 1].sprite = NULL;
			array[i].sprite = sprite;
			array[i].frame = 0;
			array[i].pos.x = x;
			array[i].pos.y = y;
			return ;
		}
		i++;
	}
}
