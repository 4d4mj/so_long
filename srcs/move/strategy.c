/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:36:11 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/14 16:36:12 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	change_strategy(t_game *g, void (*strategy)(), t_status status)
{
	unsigned int	i;

	i = -1;
	g->enemy_strategy = strategy;
	g->enemy_status = status;
	if (status == ENRAGED)
		while (++i < g->map->num_enemies)
			g->enemies[i].e_move_freq = g->enemies[i].e_move_freq / 2;
}

void	random_strategy(t_game *g, t_entity *enemy)
{
	int	offset;

	while (1)
	{
		offset = 1 - (rand() % 3);
		if (rand() % 2)
			enemy->next = (t_point){enemy->pos.x + offset, enemy->pos.y};
		else
			enemy->next = (t_point){enemy->pos.x, enemy->pos.y + offset};
		if (enemy_can_move(g, enemy->next))
			break ;
	}
}

static int	distance(t_point p1, t_point p2)
{
	return (sqrt(pow(((int)p1.x - (int)p2.x), 2) + \
		pow(((int)p1.y - (int)p2.y), 2)));
}

void	chase_strategy(t_game *g, t_entity *enemy)
{
	t_point	dirs[4];
	t_point	chosen;
	int		min_dist;
	int		i;

	i = -1;
	min_dist = INT_MAX;
	if (!enemy_has_possible_moves(g, &enemy->pos))
		return ;
	dirs[0] = (t_point){enemy->pos.x - 1, enemy->pos.y};
	dirs[1] = (t_point){enemy->pos.x, enemy->pos.y - 1};
	dirs[2] = (t_point){enemy->pos.x + 1, enemy->pos.y};
	dirs[3] = (t_point){enemy->pos.x, enemy->pos.y + 1};
	while (++i < 4)
	{
		if (!enemy_can_move(g, dirs[i]))
			continue ;
		if (distance(dirs[i], g->player.pos) < min_dist)
		{
			min_dist = distance(dirs[i], g->player.pos);
			chosen = dirs[i];
		}
	}
	enemy->next = chosen;
}
