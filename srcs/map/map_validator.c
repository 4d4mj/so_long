/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:06:17 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/15 01:38:22 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	is_map_rectangular(t_map *map)
{
	unsigned int	i;
	unsigned int	first_len;

	i = 0;
	first_len = ft_strlen(map->bytes[0]);
	while (i < map->rows)
		if (ft_strlen(map->bytes[i++]) != first_len)
			return (false);
	map->cols = first_len;
	return (true);
}

static bool	is_map_bounded(t_map *map)
{
	unsigned int	i;

	i = -1;
	while (++i < map->rows)
		if (map->bytes[i][0] != WALL || map->bytes[i][map->cols - 1] != WALL)
			return (false);
	i = -1;
	while (++i < map->cols)
		if (map->bytes[0][i] != WALL || map->bytes[map->rows - 1][i] != WALL)
			return (false);
	return (true);
}

static bool	has_valid_entities(t_game *g)
{
	t_point	p;

	p.y = -1;
	while (++p.y < g->map->rows)
	{
		p.x = -1;
		while (++p.x < g->map->cols)
		{
			if (at(g, p) == PLAYER && ++g->map->num_players)
				g->player.pos = p;
			else if (at(g, p) == EXIT && ++g->map->num_exits)
				g->exit.pos = p;
			else if (at(g, p) == COLLECTIBLE)
				g->map->num_collectibles++;
			else if (at(g, p) == ENEMY)
				g->map->num_enemies++;
			else if (!ft_strchr(ENTITIES, at(g, p)))
				return (false);
		}
	}
	return (g->map->num_players == 1 && g->map->num_exits == 1
		&& g->map->num_collectibles >= 1);
}

static bool	has_valid_path(t_game *g)
{
	char			**dup;
	bool			is_valid;
	unsigned int	i;

	i = -1;
	dup = ft_new_matrix(g->map->rows, g->map->cols + 1, sizeof(char));
	if (!dup)
		message(g, "Failed allocation on duplicate map\n");
	while (++i < g->map->rows)
		ft_memcpy(dup[i], g->map->bytes[i], g->map->cols);
	is_valid = flood_fill(g->map, g->player.pos, dup);
	destroy_matrix(dup, g->map->rows);
	return (is_valid);
}

void	validate_map(t_game *g)
{
	if (g->map->rows == 0)
		message(g, "Map is empty.\n");
	if (!is_map_rectangular(g->map))
		message(g, "Map is not rectangular.\n");
	if (!is_map_bounded(g->map))
		message(g, "Map is not bounded by walls.\n");
	if (!has_valid_entities(g))
		message(g, "Map has invalid entities.\n");
	if (!has_valid_path(g))
		message(g, "Map has not a traversable path to end the level.\n");
}
