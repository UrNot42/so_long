/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_win_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 08:08:33 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/14 02:40:35 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*init_window(t_mlx *mlx, t_coord *size)
{
	if (!make_window_image(mlx, size))
		return (mlx_destroy_display(mlx->ptr), NULL);
	if (mlx->win)
		free(mlx->win);
	mlx->win = mlx_new_window(mlx->ptr, mlx->data->width, mlx->data->height,
			mlx->name);
	if (!mlx->win)
		return (mlx_destroy_display(mlx->ptr), free(mlx->data), NULL);
	return (mlx->win);
}

void	start_mlx_win_hooks(t_params *param)
{
	mlx_hook(param->mlx.win, KeyPress, KeyPressMask, key_press, param);
	mlx_hook(param->mlx.win, DestroyNotify, 0, close_game, param);
}
// mlx_hook(param->mlx.win, ButtonPress, ButtonPressMask, mousse_press, param);
// mlx_hook(param->mlx.win, ButtonRelease, ButtonReleaseMask,
// 	mouse_enter, param);
// mlx_hook(param->mlx.win, MotionNotify, ButtonMotionMask,
// 	mouse_move, param);
// mlx_hook(param->mlx.win, KeyRelease, KeyReleaseMask,
// key_pause_pressed, param);

int	ft_close_win(t_params *param)
{
	if (param->mlx.ptr && param->mlx.data && param->mlx.data->img)
		mlx_destroy_image(param->mlx.ptr, param->mlx.data->img);
	if (param->mlx.data)
		free(param->mlx.data);
	if (!param->mlx.ptr || !param->mlx.win)
		return (EXIT_FAILURE);
	mlx_clear_window(param->mlx.ptr, param->mlx.win);
	mlx_destroy_window(param->mlx.ptr, param->mlx.win);
	return (EXIT_SUCCESS);
}

bool	make_window_image(t_mlx *mlx, t_coord *size)
{
	t_coord	max;

	mlx->data = malloc(sizeof(t_data));
	if (!mlx->data)
		return (false);
	mlx_get_screen_size(mlx->ptr, &max.x, &max.y);
	find_pxl_size(mlx, (t_coord){IMG_SIZE * size->x, IMG_SIZE * size->y},
		max, 4000);
	mlx->data->width = size->x * IMG_SIZE * mlx->pxl_size;
	mlx->data->height = size->y * IMG_SIZE * mlx->pxl_size;
	mlx->data->img = mlx_new_image(mlx->ptr,
			mlx->data->width, mlx->data->height);
	if (!mlx->data->img)
		return (false);
	mlx->data->addr = mlx_get_data_addr(mlx->data->img,
			&mlx->data->bits_per_pixel, &mlx->data->line_length,
			&mlx->data->endian);
	return (true);
}
