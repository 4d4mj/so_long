/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:15:50 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/15 19:07:13 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_handler(int keycode, t_game *g)
{
	if (keycode == ESC)
		quit(g);
	else if (keycode == K_UP)
		g->player.next = (t_point){g->player.pos.x, g->player.pos.y - 1};
	else if (keycode == K_LEFT)
	{
		g->player.next = (t_point){g->player.pos.x - 1, g->player.pos.y};
		g->player.dir = LEFT;
	}
	else if (keycode == K_DOWN)
		g->player.next = (t_point){g->player.pos.x, g->player.pos.y + 1};
	else if (keycode == K_RIGHT)
	{
		g->player.next = (t_point){g->player.pos.x + 1, g->player.pos.y};
		g->player.dir = RIGHT;
	}
	return (keycode);
}

bool	player_can_move(t_game *g, t_entity *e)
{
	return (!is_same_point(e->pos, e->next) && at(g, e->next) != WALL);
}

void	move_player(t_game *g)
{
	static t_type	previous = FLOOR;

	set(g, g->player.pos, previous);
	previous = at(g, g->player.next);
	if (at(g, g->player.next) == COLLECTIBLE)
		previous = FLOOR;
	render_tile(g, g->player.pos);
	set(g, g->player.next, PLAYER);
	g->player.pos = g->player.next;
}

static void	collect_collectibles(t_game *g, t_point *p)
{
	unsigned int	i;

	i = -1;
	while (++i < g->map->num_collectibles)
	{
		if (!is_same_point(g->coins[i].pos, *p))
			continue ;
		g->coins[i].pos = (t_point){-1, -1};
		break ;
	}
	g->collected++;
	if (g->collected == g->map->num_collectibles)
		g->collected_all = true;
}

void	player_controller(t_game *g)
{
	if (at(g, g->player.next) == COLLECTIBLE)
		collect_collectibles(g, &g->player.next);
	else if (at(g, g->player.next) == ENEMY)
		display_game_over(g, GAME_LOSE);
	if (g->collected == g->map->num_collectibles)
	{
		if (at(g, g->player.next) == EXIT)
			display_game_over(g, GAME_WIN);
		if (g->enemy_status != ENRAGED)
			change_strategy(g, &chase_strategy, ENRAGED);
	}
}
