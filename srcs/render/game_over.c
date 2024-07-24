/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:08:11 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/15 00:18:44 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	handle_keypress(int keycode, t_game *g)
{
	if (keycode == ENTER || keycode == ESC)
		quit(g);
	return (0);
}

static void	blackout_screen(t_game *g)
{
	int	x;
	int	y;
	int	width;
	int	height;

	y = 0;
	width = g->map->cols * PX;
	height = g->map->rows * PX + PX;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			mlx_pixel_put(g->disp.mlx, g->disp.win, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	display_game_over(t_game *g, char *s)
{
	int	text_x;
	int	text_y;

	text_x = (g->map->cols * PX) / 2 - 20;
	text_y = (g->map->rows * PX + 20) / 2;
	blackout_screen(g);
	mlx_loop_hook(g->disp.mlx, NULL, NULL);
	mlx_string_put(g->disp.mlx, g->disp.win, text_x, text_y, 0xFFFFFF, s);
	mlx_key_hook(g->disp.win, handle_keypress, g);
	mlx_loop(g->disp.mlx);
}
