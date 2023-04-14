/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:10:35 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/14 00:53:43 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	parse_args(int amount, char **arg, t_params *param)
{
	if (amount < 2 || !arg[1])
		return (help_msg(), error_msg(1), false);
	if (!ft_strncmp(arg[1], "-h\0", 3))
		return (help_msg(), false);
	if (!ft_strncmp(arg[1], "-m\0", 3))
	{
		param->mode = 1;
		param->path = arg[2];
		if (amount > 2)
			return (1);
		return (error_msg(3), false);
	}
	if (!ft_strncmp(arg[1], "-w\0", 3))
	{
		param->mode = 2;
		param->path = arg[2];
		if (amount > 2)
			return (2);
		return (error_msg(4), false);
	}
	return (help_msg(), error_msg(2), false);
}

int	main(int ac, char **av)
{
	t_params	params;

	params = (t_params){0};
	if (!parse_args(ac, av, &params))
		return (EXIT_FAILURE);
	if (params.mode == 1)
		if (!start_map(&params, params.path))
			return (EXIT_FAILURE);
	if (params.mode == 2)
		if (!start_game(&params, &av[2], ac - 2))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
