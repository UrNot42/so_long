/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:56:56 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/07 12:32:18 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// takes the states modified by key_hook_pause and gives out the correct actions
bool	pause_screen(t_params *param)
{
	if (param->button < 0)
	{
		param->button *= -1;
		print_buttons(param, param->pressed);
		print_screen(param);
	}
	return (true);
}

void	darken_screen(t_params *param, int factor)
{
	int			i;
	int			j;
	uint32_t	color;
	t_data		*img;

	i = 0;
	img = param->mlx.data;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			color = (unsigned char)img->addr[(i * img->width * 4) + j * 4]
				/ factor
				| (unsigned char)img->addr[(i * img->width * 4) + (j * 4) + 1]
				/ factor << 8
				| (unsigned char)img->addr[(i * img->width * 4) + (j * 4) + 2]
				/ factor << 16;
			my_mlx_pixel_put(param->mlx.data, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_button(t_params *param, t_data *button, t_data *text, t_coord *pos)
{
	t_coord	div;
	t_coord	size;

	div.x = (1 + pos->x * 2);
	div.y = (1 + pos->y * 2);
	size.x = param->mlx.data->width - (button->width * param->mlx.pxl_size);
	size.y = param->mlx.data->height - (button->height * param->mlx.pxl_size);
	draw_image(param, (size.x * div.x) / (6 * param->mlx.pxl_size),
		(size.y * div.y) / (6 * param->mlx.pxl_size), button);
	size.x = param->mlx.data->width - (text->width * param->mlx.pxl_size);
	size.y = param->mlx.data->height - (text->height * param->mlx.pxl_size);
	draw_image(param, (size.x * div.x) / (6 * param->mlx.pxl_size),
		(size.y * div.y) / (6 * param->mlx.pxl_size), text);
}

void	draw_pressed_button(t_params *param, bool height)
{
	if (param->button == 1)
		draw_button(param, &param->imgs.bt_press, &param->imgs.resume,
			&(t_coord){!!height, !height});
	if (param->button == 2)
		draw_button(param, &param->imgs.bt_press, &param->imgs.retry,
			&(t_coord){1, 1});
	if (param->button == 3)
		draw_button(param, &param->imgs.bt_press, &param->imgs.retry,
			&(t_coord){1 + 1 * !height, 1 + height});
}

void	print_buttons(t_params *param, bool pressed)
{
	int		temp;
	int		tmp_offset;
	bool	height;

	height = param->mlx.data->height * 2 > param->mlx.data->width;
	temp = param->mlx.pxl_size;
	tmp_offset = param->col_ofst;
	param->col_ofst = 0;
	find_pxl_size(&param->mlx, (t_coord){48, 32},
		(t_coord){param->mlx.data->width, param->mlx.data->height}, 6);
	draw_button(param, &param->imgs.button.img[param->button == 1],
		&param->imgs.resume, &(t_coord){!!height, !height});
	draw_button(param, &param->imgs.button.img[param->button == 2],
		&param->imgs.retry, &(t_coord){1, 1});
	draw_button(param, &param->imgs.button.img[param->button == 3],
		&param->imgs.leave, &(t_coord){1 + 1 * !height, 1 + height});
	if (pressed)
		draw_pressed_button(param, height);
	param->mlx.pxl_size = temp;
	param->col_ofst = tmp_offset;
}
