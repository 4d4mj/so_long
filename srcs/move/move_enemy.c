/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:11:22 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/14 23:22:09 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	enemy_can_move(t_game *g, t_point p)
{
	return (at(g, p) == FLOOR || at(g, p) == PLAYER);
}

bool	enemy_has_possible_moves(t_game *g, t_point *pos)
{
	bool	can_move;

	can_move = false;
	can_move |= enemy_can_move(g, (t_point){pos->x + 1, pos->y});
	can_move |= enemy_can_move(g, (t_point){pos->x - 1, pos->y});
	can_move |= enemy_can_move(g, (t_point){pos->x, pos->y + 1});
	can_move |= enemy_can_move(g, (t_point){pos->x, pos->y - 1});
	return (can_move);
}

void	move_enemy(t_game *g)
{
	unsigned int	i;

	i = -1;
	while (++i < g->map->num_enemies)
	{
		if (++g->enemies[i].e_move_counter % g->enemies[i].e_move_freq != 0)
			continue ;
		if (!enemy_has_possible_moves(g, &g->enemies[i].pos))
			continue ;
		(*g->enemy_strategy)(g, &g->enemies[i]);
		if (at(g, g->enemies[i].next) == PLAYER)
			display_game_over(g, GAME_LOSE);
		set(g, g->enemies[i].pos, FLOOR);
		render(g, &g->floor_sp.frames[0], g->enemies[i].pos);
		set(g, g->enemies[i].next, ENEMY);
		g->enemies[i].pos = g->enemies[i].next;
	}
}
