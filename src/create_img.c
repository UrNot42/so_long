/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 11:55:39 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/13 04:22:59 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Creates an image from a given XPM file path and initializes
 * its properties.
 *
 * This function creates an image from a given XPM file path, initializes its
 * properties such as its width, height, bits per pixel, line length and endian.
 * It also sets the image's address to the data address obtained from
 * mlx_get_data_addr function.
 *
 * @param ptr A pointer to the mlx instance.
 * @param image A pointer to the image data structure to be initialized.
 * @param tmp The file path to the XPM file relative to the IMG_FOLDER.
 *
 * @return Returns true if the image was successfully created and initialized,
 * false otherwise.
 */
bool	create_image(void *ptr, t_data *image, char *tmp)
{
	char	*path;

	path = ft_strjoin(IMG_FOLDER, tmp);
	if (!path)
		return (false);
	image->img = mlx_xpm_file_to_image(ptr, path,
			&image->width, &image->height);
	if (!image->img)
		return (free(path), image->img = NULL, false);
	free(path);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return (true);
}

/**
 * @brief Create a sprite object with multiple image frames.
 *
 * @param ptr A void pointer to the game object.
 * @param sprite A pointer to the sprite object to be created.
 * @param path A string containing the file path to the image files.
 * @param frame An integer representing the number of image
 * frames in the sprite object.
 *
 * @return Returns a boolean value indicating whether the sprite object
 * was successfully created or not.
 */
bool	create_sprite(void *ptr, t_sprit *sprite, char *path, int frame)
{
	int		i;
	char	*file[2];

	sprite->img = ft_calloc(frame, sizeof(t_data));
	if (!sprite->img)
		return (false);
	i = 0;
	sprite->size = frame;
	sprite->frame = 0;
	while (i < frame)
	{
		file[0] = ft_itoa(i);
		if (!file[0])
			return (false);
		file[1] = ft_strjoin(path, file[0]);
		if (!file[1])
			return (false);
		(free(file[0]), file[0] = ft_strjoin(file[1], ".xpm"));
		if (!file[0] || !create_image(ptr, &sprite->img[i], file[0]))
			return (error_msg(5), free(file[0]), free(file[1]), false);
		(free(file[0]), free(file[1]), i++);
	}
	return (true);
}
