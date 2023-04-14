/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:29:57 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/12 18:04:27 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_msg(int error)
{
	ft_printf(RED"Error:\n\t"BLUE);
	if (error == 1)
		ft_printf("Insuficient arguments: need a name or a file\n"RESET);
	else if (error == 2)
		ft_printf("Something went wrong: please send existing files\n"RESET);
	else if (error == 3)
		ft_printf("Incorrect usage: ./so_long -m [insert map name here]\n"RESET);
	else if (error == 4)
		ft_printf("Incorrect usage: ./so_long -w [insert map folder]\n"RESET);
	else if (error == 5)
		ft_printf("Error while initializing game variables\n"RESET);
	else if (error == 6)
		ft_printf("Invalid map provided\n"RESET);
	else if (error == 7)
		ft_printf("Invalid map size\n"RESET);
	else if (error == 8)
		ft_printf("Map parsing: more than one exit\n\n"RESET);
	else if (error == 9)
		ft_printf("Map parsing: no exit found\n"RESET);
	else if (error == 10)
		ft_printf("Map parsing: inaccessible keys\n"RESET);
	else if (error == 11)
		ft_printf("Map parsing: invalid teleporters\n"RESET);
	else
		ft_printf("Something bad happened, call the programmer\n"RESET);
}

void	win_msg(void)
{
	ft_printf(YELLOW BACK"You "GREEN"won!\n"RESET);
}

void	death_msg(int code)
{
	ft_printf(YELLOW BACK"You "RED"died "YELLOW);
	if (code == 1)
		ft_printf("on Time\n"RESET);
	else if (code == 2)
		ft_printf("when ya got "RED"stepped on "YELLOW"by a "RED"Pigeon\n"RESET);
	else if (code == 3)
		ft_printf("when you got "RED"stepped on "YELLOW"by a "RED"Ghost\n"RESET);
	else if (code == BIRD_TILE)
		ft_printf("from a "RED"Pigeon\n"RESET);
	else if (code == GHOST_TILE)
		ft_printf("from a "RED"Ghost\n"RESET);
	else if (code == ENEMY_TILE)
		ft_printf("from a "RED"Bramble "YELLOW"in the woods\n"RESET);
	else if (code == MIMIC_TILE)
		ft_printf("from the "RED"Monster "YELLOW"in the "RED"chest\n"RESET);
	else if (code == WALL_TILE)
		ft_printf("by suffocating in a "RED"Wall\n"RESET);
	else if (code == WALL_TILE_2)
		ft_printf("hurt by the broken "RED"Wall\n"RESET);
	else if (code == CHEST_TILE || code == OPENED_CHEST_TILE)
		ft_printf("by suffocating inside a "RED"Chest\n"RESET);
	else if (code == 4)
		ft_printf("when you lit on "RED"Fire\n"RESET);
	else if (code == 5)
		ft_printf("from "RED"alcoholism\n"RESET);
}

void	help_msg(void)
{
	ft_printf(GREEN"=======================so__long=======================\n");
	ft_printf("| This is the help message                           |\n");
	ft_printf("| for you to use this Program correctly:             |\n");
	ft_printf("======================================================\n");
	ft_printf("| -Run a single map:                                 |\n");
	ft_printf("|      ./so_long -m path/map_name                    |\n");
	ft_printf("|                                                    |\n");
	ft_printf("| -Run a world folder:                               |\n");
	ft_printf("|      ./so_long -w path_of_folder/prefix            |\n");
	ft_printf("|  [ Inside the folder, map are expected to be       |\n");
	ft_printf("|    numbered: name1.ber, name2.ber... ]             |\n");
	ft_printf("|                                                    |\n");
	ft_printf("| -Display help message:                             |\n");
	ft_printf("|      ./so_long -h                                  |\n");
	ft_printf("|                                                    |\n");
	ft_printf("|                                      -by ulevallo- |\n");
	ft_printf("======================================================\n\n"RESET);
}
