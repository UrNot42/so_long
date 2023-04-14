/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:29:54 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/14 14:58:17 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Initializes game images by creating image objects and assigning
 * them to corresponding fields of the t_imgs struct.
 *
 * @param ptr A void pointer representing the game window object.
 * @param a A pointer to the t_imgs struct holding the game image data.
 * @return Returns true if all image objects are successfully created and
 * assigned, and false otherwise.
 */
bool	init_images(void *ptr, t_imgs *a)
{
	a->err = !create_image(ptr, &a->drink, "wine_16px.xpm");
	if (!a->err)
		a->err += !create_image(ptr, &a->bt_press, "w_map/button/press.xpm");
	if (!a->err)
		a->err += !create_image(ptr, &a->resume, "w_map/text/resume.xpm");
	if (!a->err)
		a->err += !create_image(ptr, &a->retry, "w_map/text/retry.xpm");
	if (!a->err)
		a->err += !create_image(ptr, &a->leave, "w_map/text/leave.xpm");
	if (!a->err)
		a->err += !create_image(ptr, &a->game_over, "w_map/game_over.xpm");
	if (!a->err)
		a->err += !create_image(ptr, &a->finish, "w_map/finish.xpm");
	return (a->err);
}

/**
 * @brief Initializes other game sprites.
 *
 * This function initializes various other game sprites including the
 * wall_apo, chick, grave, mimic, mimic_op, ghost, bird, enemy, chest,
 * door, button, and stone sprites. The function uses the create_sprite
 * function to create each sprite and assign them to their corresponding
 * variables in the t_imgs struct.
 *
 * @param ptr A void pointer to a mlx structure.
 * @param a A pointer to the t_imgs struct containing the game's images.
 *
 * @return Returns a boolean value indicating whether or not the function
 * completed successfully. Returns true if all sprites were initialized
 * successfully, and false otherwise.
 */
bool	init_other_sprites(void *ptr, t_imgs *a)
{
	if (!a->err)
		a->err += !create_sprite(ptr, &a->chick, "chick/evil_chick_16px", 4);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->grave, "chicks_grave/grave_16px", 2);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->mimic, "mimic/mimic_16px", 9);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->mimic_op, "mimic/mimic_open_16px", 9);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->ghost, "ghost/ghost_16px", 10);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->bird, "bird/bird_16px", 2);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->enemy, "enemy/enemy_16px", 8);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->button, "w_map/button/button", 2);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->stone, "stone/stone_16px", 17);
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
bool	init_sprites(void *ptr, t_imgs *a, bool (*init_asset)(void *, t_imgs*))
{
	if (!a->err)
		a->err += init_asset(ptr, a);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->chest, "chest/chest_16px", 16);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->door, "door/box_16px", 6);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->key, "keys/key_16px", 8);
	if (!a->err)
		a->err += !create_sprite(ptr, &a->player, "player/player_16px", 12);
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
	if (a->err)
		return (a->err);
	return (init_other_sprites(ptr, a));
}

/**
 * @brief Initializes the world images for the game.
 *
 * This function loads various image resources
 * required for rendering the game world,
 * such as panes, level pads, buttons, paths,
 * game over and finish screens, etc.
 *
 * @param prm A pointer to the game parameters structure.
 *
 * @return Returns false if the world images were successfully initialized,
 * true otherwise.
 */
bool	init_world_imgs(t_params *prm)
{
	bool	err;

	err = !create_sprite(prm->mlx.ptr, &prm->world.pane,
			"w_map/pane/mountain", 3);
	if (!err)
		err += !create_sprite(prm->mlx.ptr, &prm->world.pad,
				"w_map/lvl_pad/lvl_pad_", 2);
	if (!err)
		err += !create_sprite(prm->mlx.ptr, &prm->world.heart,
				"w_map/heart_16px", 2);
	if (!err)
		err += !create_image(prm->mlx.ptr, &prm->world.path, "w_map/path.xpm");
	return (err);
}
