/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:19:22 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/12 20:40:27 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Frees a triple string and all its elements.
 *
 * @param a triple string to free.
 */
void	free_triple_str(char ***a)
{
	size_t	i;

	i = -1;
	while (a[++i])
		free_double_str(a[i]);
	if (a)
		free(a);
}

/**
 * @brief Frees a double string and all its elements.
 *
 * @param a Double string to free.
 */
void	free_double_str(char **a)
{
	size_t	i;

	i = 0;
	if (!a)
		return ;
	while (a[i])
		free(a[i++]);
	if (a)
		free(a);
}

/**
 * @brief Copies a map and stores the copy in a new array.
 *
 * @param map Map to copy.
 * @param copy Pointer to a double string to store the copy in.
 * @param tab Pointer to an array to store the copy in.
 * @return True if the copy is successful, false otherwise.
 */
bool	copy_map(char **map, char ***copy, char ***tab)
{
	*copy = copy_double_str(map);
	if (!copy)
		return (ft_printf("error : malloc failed\n"), false);
	tab[0] = *copy;
	return (true);
}

/**
 * @brief Copies a double string.
 *
 * @param dstr Double string to copy.
 * @return Copied double string on success, NULL on allocation failure.
 */
char	**copy_double_str(char **dstr)
{
	char	**new_dstr;
	int		len;
	int		i;

	len = 0;
	while (dstr[len])
		len++;
	i = 0;
	new_dstr = ft_calloc(len + 1, sizeof(char *));
	if (!new_dstr)
		return (NULL);
	while (dstr[i])
	{
		new_dstr[i] = ft_strdup(dstr[i]);
		if (!new_dstr[i])
			return (free_double_str(new_dstr), NULL);
		i++;
	}
	return (new_dstr);
}

/**
 * @brief Frees the image data associated with the given t_data structure.
 *
 * @param mlx Pointer to the mlx data structure.
 * @param to_free Pointer to the t_data structure whose
 * 	 image data is to be freed.
 */
void	free_data(t_mlx *mlx, t_data *to_free)
{
	if (to_free && mlx->ptr
		&& to_free->img)
		mlx_destroy_image(mlx->ptr, to_free->img);
}
