/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:13:54 by ncarvalh          #+#    #+#             */
/*   Updated: 2024/07/14 03:39:58 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_img	new_image(t_game *g, t_point dims)
{
	t_img	img;

	img.width = dims.x;
	img.height = dims.y;
	img.img = mlx_new_image(g->disp.mlx, dims.x, dims.y);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, \
		&img.line_len, &img.endian);
	return (img);
}

t_img	new_file_image(t_game *g, char *path)
{
	t_img	img;

	if (path)
		img.img = mlx_xpm_file_to_image(g->disp.mlx, \
			path, &(img.width), &(img.height));
	img.addr = mlx_get_data_addr(img.img, &img.bpp, \
		&img.line_len, &img.endian);
	return (img);
}
