/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:17:52 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/14 16:40:13 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_inner_walls(t_game *g)
{
	t_point	p;

	p.y = 1;
	while (p.y < g->map->rows - 1)
	{
		p.x = 1;
		while (p.x < g->map->cols - 1)
		{
			if (at(g, p) == WALL)
				render(g, &g->walls_sp.frames[0], p);
			p.x++;
		}
		p.y++;
	}
}

static void	render_outter_walls(t_game *g)
{
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
}

void	render_walls(t_game *g)
{
	render_outter_walls(g);
	render_inner_walls(g);
}
