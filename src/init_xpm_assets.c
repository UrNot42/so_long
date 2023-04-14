/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_xpm_assets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:07:35 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/09 19:44:11 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	init_meadow_assets(void *ptr, t_imgs *a)
{
	if (!a->err)
		a->err = !create_image(ptr, &a->bgd, "grass/grass_16px0.xpm");
	if (!a->err)
		a->err += !create_image(ptr, &a->exit_cls, "exit/exit_cls_16px.xpm");
	if (!a->err)
		a->err += !create_image(ptr, &a->fire, "fire_ground_16px.xpm");
	if (!a->err)
		a->err += !create_image(ptr, &a->wall_broken, "broken_tree_16px.xpm");
	if (!a->err)
		a->err += !create_sprite(ptr, &a->wall_apo, "apo_tree/tree_16px", 3);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->grass, "grass/grass_16px", 7);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->wall, "tree/tree_16px", 15);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->exit, "exit/exit_16px", 5);
	return (a->err);
}

bool	init_desert_assets(void *ptr, t_imgs *a)
{
	if (!a->err)
		a->err = !create_image(ptr, &a->bgd, "desert/sand_16px0.xpm");
	if (!a->err)
		a->err += !create_image(ptr, &a->fire, "desert/red_sand.xpm");
	if (!a->err)
		a->err += !create_image(ptr,
				&a->wall_broken, "desert/cacti_broken_16px.xpm");
	if (!a->err)
		a->err += !create_image(ptr, &a->exit_cls, "none.xpm");
	if (!a->err)
		a->err += !create_sprite(ptr, &a->exit, "desert/pyramid", 1);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->grass, "desert/sand_16px", 1);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->wall, "desert/cacti_16px", 1);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->wall_apo, "desert/fire_16px", 4);
	return (a->err);
}

bool	init_lake_assets(void *ptr, t_imgs *a)
{
	if (!a->err)
		a->err = !create_image(ptr, &a->bgd, "lake/waterpx0.xpm");
	if (!a->err)
		a->err += !create_image(ptr, &a->fire, "lake/blood.xpm");
	if (!a->err)
		a->err += !create_image(ptr,
				&a->wall_broken, "lake/broken_tree.xpm");
	if (!a->err)
		a->err += !create_image(ptr, &a->exit_cls, "none.xpm");
	if (!a->err)
		a->err += !create_sprite(ptr, &a->exit, "lake/token", 3);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->grass, "lake/waterpx", 3);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->wall, "lake/tree_16px", 2);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->wall_apo, "lake/fire_tree_16px", 2);
	return (a->err);
}

bool	init_minecraft_assets(void *ptr, t_imgs *a)
{
	if (!a->err)
		a->err = !create_image(ptr, &a->bgd, "mc/grass0.xpm");
	if (!a->err)
		a->err += !create_image(ptr, &a->fire, "mc/netherack.xpm");
	if (!a->err)
		a->err += !create_image(ptr, &a->wall_broken, "mc/broken_tree.xpm");
	if (!a->err)
		a->err += !create_image(ptr, &a->exit_cls, "mc/portal_cls.xpm");
	if (!a->err)
		a->err += !create_sprite(ptr, &a->exit, "mc/portal", 4);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->grass, "mc/grass", 1);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->wall, "mc/tree", 1);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->wall_apo, "mc/fire/", 32);
	return (a->err);
}

/**
 * @brief Initializes the sprites for the game.
 * This function initializes all the sprites needed
 * for the game by calling the create_sprite() function for each sprite.
 *
 * @param ptr Pointer to the game data structure.
 * @param a Pointer to the t_imgs data structure that holds the sprites.
 * @return Returns a boolean value indicating if the function succeeded or not.
 * True if successful, false if there was an error.
*/
bool	init_mc_sprites(void *ptr, t_imgs *a)
{
	if (!a->err)
		a->err += !create_sprite(ptr, &a->chest, "mc/chest/chest", 13);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->key, "mc/diamond", 12);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->door, "mc/mc_door", 2);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->player, "pacman/pacman_16px", 16);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->a, "tp_pad/a/tp_a_16px", 8);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->b, "tp_pad/b/tp_b_16px", 8);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->t, "tp_pad/t/tp_t_16px", 8);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->x, "tp_pad/x/tp_x_16px", 8);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->y, "tp_pad/y/tp_y_16px", 8);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->z, "tp_pad/z/tp_z_16px", 8);
	if (!a->err)
		a->err += init_minecraft_assets(ptr, a);
	if (a->err)
		return (a->err);
	return (init_other_sprites(ptr, a));
}
