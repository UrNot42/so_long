/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 07:37:48 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/21 12:59:15 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief frees the rest of images
 *
 * @param mlx pointer to the mlx used to free the data
 * @param imgs img structure pointer
 */
void	free_imgs(t_mlx *mlx, t_imgs *imgs)
{
	free_data(mlx, &imgs->bgd);
	free_data(mlx, &imgs->exit_cls);
	free_data(mlx, &imgs->fire);
	free_data(mlx, &imgs->drink);
	free_data(mlx, &imgs->wall_broken);
	free_data(mlx, &imgs->bt_press);
	free_data(mlx, &imgs->retry);
	free_data(mlx, &imgs->leave);
	free_data(mlx, &imgs->resume);
	free_data(mlx, &imgs->finish);
	free_data(mlx, &imgs->game_over);
}

/**
 * @brief Frees the memory of a sprite object, including its images.
 *
 * @param param Pointer to the program parameters.
 * @param to_free Pointer to the sprite object to free.
 * @return void
 */
void	free_sprite(t_params *param, t_sprit *to_free)
{
	int	i;

	if (!to_free)
		return ;
	i = to_free->size - 1;
	while (i >= 0)
	{
		if (to_free->img != NULL)
			free_data(&param->mlx, &to_free->img[i]);
		i--;
	}
	if (to_free->img)
		free(to_free->img);
}

/**
 * @brief Frees the memory of all the sprite objects in an images object.
 *
 * @param param Pointer to the program parameters.
 * @param imgs Pointer to the images object containing the sprite objects.
 * @return void
 */
void	free_sprites(t_params *param, t_imgs *imgs)
{
	free_sprite(param, &imgs->exit);
	free_sprite(param, &imgs->grass);
	free_sprite(param, &imgs->wall);
	free_sprite(param, &imgs->wall_apo);
	free_sprite(param, &imgs->key);
	imgs->player.size *= 4;
	free_sprite(param, &imgs->player);
	free_sprite(param, &imgs->enemy);
	free_sprite(param, &imgs->ghost);
	free_sprite(param, &imgs->bird);
	free_sprite(param, &imgs->mimic);
	free_sprite(param, &imgs->mimic_op);
	free_sprite(param, &imgs->chest);
	free_sprite(param, &imgs->door);
	free_sprite(param, &imgs->chick);
	free_sprite(param, &imgs->grave);
	free_sprite(param, &imgs->a);
	free_sprite(param, &imgs->b);
	free_sprite(param, &imgs->t);
	free_sprite(param, &imgs->x);
	free_sprite(param, &imgs->y);
	free_sprite(param, &imgs->z);
	free_sprite(param, &imgs->button);
	free_sprite(param, &imgs->stone);
}

/**
 * @brief Frees the memory of all the images in a map object.
 *
 * @param param Pointer to the program parameters.
 * @param world Pointer to the map object containing the images.
 * @return void
 */
void	free_world_images(t_params *param, t_map *world)
{
	free_sprite(param, &world->pane);
	free_sprite(param, &world->heart);
	free_sprite(param, &world->pad);
	free_data(&param->mlx, &world->path);
}
