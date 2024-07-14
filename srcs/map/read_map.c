/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:06:41 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/14 16:06:41 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_type	at(t_game *g, t_point p)
{
	return (g->map->bytes[p.y][p.x]);
}

void	set(t_game *g, t_point p, t_type type)
{
	g->map->bytes[p.y][p.x] = type;
}

static t_map	*map_new(unsigned int cols, unsigned int rows)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->bytes = ft_calloc(rows + 1, sizeof(char *));
	if (!map->bytes)
	{
		ft_free(map);
		return (NULL);
	}
	map->cols = cols;
	map->rows = rows;
	return (map);
}

static int	get_num_lines(t_game *game, char *filename)
{
	int		fd;
	int		lines;
	char	*tmp;

	lines = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		message(game, "Couldn't open requested file.\n");
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		lines++;
		ft_free(tmp);
	}
	close(fd);
	return (lines);
}

void	read_map(t_game *game, char *filename)
{
	int				fd;
	char			*tmp;
	unsigned int	i;

	i = 0;
	game->map = map_new(0, get_num_lines(game, filename));
	if (!game->map)
		message(game, "Allocation error on game->map\n");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		message(game, "Couldn't open requested file.\n");
	while (i < game->map->rows)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			message(game, "Allocation failed on map lines.\n");
		game->map->bytes[i] = ft_strtrim(tmp, "\n");
		if (!game->map->bytes[i++])
			message(game, "Allocation failed on map lines 2.\n");
		ft_free(tmp);
	}
	close(fd);
}
