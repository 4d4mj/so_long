/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:35:54 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/15 19:07:20 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render(t_game *g, t_img *img, t_point p)
{
	mlx_put_image_to_window(g->disp.mlx, g->disp.win, img->img, \
		p.x * img->width, p.y * img->height);
}

void	render_tile(t_game *g, t_point p)
{
	t_img	*img;

	img = &g->walls_sp.frames[0];
	if (at(g, p) == EXIT)
		img = &g->exit_sp.frames[0];
	else if (at(g, p) == FLOOR)
		img = &g->floor_sp.frames[0];
	else if (at(g, p) == PLAYER)
		img = &g->player_sp[RIGHT].frames[0];
	else if (at(g, p) == COLLECTIBLE)
		img = &g->collectibles_sp.frames[0];
	else if (at(g, p) == ENEMY)
		img = &g->enemy_sp[NORMAL].frames[0];
	else if (at(g, p) == WALL)
		img = &g->walls_sp.frames[0];
	else
		return ;
	render(g, img, p);
}

void	render_map(t_game *g)
{
	t_point			p;
	unsigned int	i;

	i = 0;
	while (++i < g->map->cols - 1)
		render(g, &g->walls_sp.frames[0], (t_point){i, 0});
	i = -1;
	while (++i < g->map->cols)
		render(g, &g->walls_sp.frames[0], (t_point){i, g->map->rows - 1});
	i = -1;
	while (++i < g->map->rows - 1)
	{
		render(g, &g->walls_sp.frames[0], (t_point){0, i});
		render(g, &g->walls_sp.frames[0], (t_point){g->map->cols - 1, i});
	}
	p.y = 0;
	while (++p.y < g->map->rows - 1)
	{
		p.x = 0;
		while (++p.x < g->map->cols - 1)
			render_tile(g, p);
	}
}

void	render_counter(t_game *g)
{
	char	*str[2];
	t_point	p;

	p.x = (g->map->cols) * 16 - 10;
	p.y = g->map->rows * PX + 20;
	str[0] = ft_itoa(g->moves);
	str[1] = ft_itoa(++g->moves);
	mlx_string_put(g->disp.mlx, g->disp.win, p.x, p.y, 0x000000, str[0]);
	mlx_string_put(g->disp.mlx, g->disp.win, p.x, p.y, 0xFFFFFF, str[1]);
	ft_free(str[0]);
	ft_free(str[1]);
}

int	render_frame(t_game *g)
{
	animate(g, &g->player, g->player_sp, 1);
	animate(g, g->enemies, g->enemy_sp, g->map->num_enemies);
	animate(g, g->coins, &g->collectibles_sp, g->map->num_collectibles);
	if (g->collected_all)
		animate(g, &g->exit, &g->exit_sp, 1);
	move_enemy(g);
	if (player_can_move(g, &g->player))
	{
		render_counter(g);
		player_controller(g);
		move_player(g);
	}
	return (0);
}
