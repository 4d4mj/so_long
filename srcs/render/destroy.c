/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 02:10:02 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/14 23:14:14 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_matrix(void *matrix, size_t rows)
{
	size_t	i;

	i = 0;
	if (!matrix)
		return ;
	while (i < rows)
		ft_free(((char **)matrix)[i++]);
	ft_free(matrix);
}

static void	destroy_sprite(t_game *g, t_sprite *sp)
{
	int	i;

	i = 0;
	if (!sp || !sp->frames)
		return ;
	while (i < sp->nframes)
		if (sp->frames[i].img)
			mlx_destroy_image(g->disp.mlx, sp->frames[i++].img);
	ft_free(sp->frames);
}

static void	destroy_map(t_map *map)
{
	if (!map)
		return ;
	destroy_matrix(map->bytes, map->rows);
	ft_free(map);
}

static void	destroy_all_sprites(t_game *g)
{
	int	k;

	k = -1;
	destroy_sprite(g, &g->walls_sp);
	destroy_sprite(g, &g->exit_sp);
	destroy_sprite(g, &g->floor_sp);
	destroy_sprite(g, &g->collectibles_sp);
	while (++k < 2)
	{
		if (g->player_sp)
			destroy_sprite(g, &g->player_sp[k]);
		if (g->enemy_sp)
			destroy_sprite(g, &g->enemy_sp[k]);
	}
	ft_free(g->player_sp);
	ft_free(g->enemy_sp);
}

void	destroy_game(t_game *game)
{
	if (!game)
		return ;
	ft_free(game->coins);
	ft_free(game->enemies);
	destroy_all_sprites(game);
	if (game->disp.win)
		mlx_destroy_window(game->disp.mlx, game->disp.win);
	if (game->disp.mlx)
		mlx_destroy_display(game->disp.mlx);
	if (game->map)
		destroy_map(game->map);
	ft_free(game->disp.mlx);
}
