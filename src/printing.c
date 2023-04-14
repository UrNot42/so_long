/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:51:55 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/13 22:22:42 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(t_params *param, bool just_sprites)
{
	draw_map(param, just_sprites);
	print_screen(param);
}

void	print_screen(t_params *param)
{
	mlx_put_image_to_window(param->mlx.ptr, param->mlx.win,
		param->mlx.data->img, 0, 0);
}

void	print_final_screen(t_params *prm, bool win)
{
	int		temp;

	temp = prm->mlx.pxl_size;
	prm->p.drunk = 0;
	prm->col_ofst = 0;
	find_pxl_size(&prm->mlx, (t_coord){48, 32},
		(t_coord){prm->mlx.data->width, prm->mlx.data->height}, 80 - 50 * win);
	if (win)
		draw_image(prm, (prm->mlx.data->width
				- prm->imgs.finish.width * prm->mlx.pxl_size)
			/ (2 * prm->mlx.pxl_size), (prm->mlx.data->height
				- prm->imgs.finish.height * prm->mlx.pxl_size)
			/ (2 * prm->mlx.pxl_size), &prm->imgs.finish);
	else
		draw_image(prm, (prm->mlx.data->width
				- prm->imgs.game_over.width * prm->mlx.pxl_size)
			/ (2 * prm->mlx.pxl_size), (prm->mlx.data->height
				- prm->imgs.game_over.height * prm->mlx.pxl_size)
			/ (2 * prm->mlx.pxl_size), &prm->imgs.game_over);
	prm->mlx.pxl_size = temp;
	print_screen(prm);
}

void	print_data(t_params *param)
{
	ft_printf(BACK BACK BACK YELLOW"Keys: "BLUE"%d"YELLOW"/"BLUE"%d\n"RESET,
		param->p.keys, param->total_keys);
	ft_printf(YELLOW"Moves: "BLUE"%d\n\n"RESET,
		param->p.moves);
}

void	print_moves(t_params *prm, int moves)
{
	char	*string;
	char	*tmp;

	tmp = ft_itoa(moves);
	if (!tmp)
		return ;
	string = ft_strjoin("Moves:", tmp);
	mlx_string_put(prm->mlx.ptr, prm->mlx.win, 3, 20, 0xfffffff, string);
	free(tmp);
	free(string);
}
