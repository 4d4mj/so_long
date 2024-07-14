/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:32:18 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/14 16:32:19 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_graphics(t_game *g)
{
	g->disp.mlx = mlx_init();
	if (!g->disp.mlx)
		message(g, "Failed allocation on mlx pointer\n");
	g->disp.win = mlx_new_window(g->disp.mlx, 32 * (g->map->cols), \
		32 * g->map->rows + 32, "so_long");
	if (!g->disp.win)
		message(g, "Failed allocation on window pointer\n");
	g->disp.dims = (t_point){32 * (g->map->cols - 1), 32 * g->map->rows};
}

static void	init_player(t_game *g)
{
	g->player.frame_freq = CALLS_PER_FRAME;
	g->player.animate_speed = ANIMATE_CALLS;
	g->player.type = PLAYER;
}

static void	init_enemies(t_game *g)
{
	int		i;
	t_point	p;

	i = 0;
	p = (t_point){-1, -1};
	g->enemies = ft_calloc(g->map->num_enemies, sizeof(t_entity));
	if (!g->enemies)
		message(g, "Failed allocation on coins entity array\n");
	g->enemy_strategy = &random_strategy;
	while (++p.y < g->map->rows)
	{
		p.x = -1;
		while (++p.x < g->map->cols)
		{
			if (at(g, p) != ENEMY)
				continue ;
			g->enemies[i].frame = rand() % NUM_ENEMY_FRAMES;
			g->enemies[i].frame_freq = CALLS_PER_FRAME;
			g->enemies[i].e_move_freq = rand () % MOVE_CALLS + MOVE_CALLS;
			g->enemies[i].animate_speed = ANIMATE_CALLS;
			g->enemies[i].type = ENEMY;
			g->enemies[i].pos = p;
			g->enemies[i++].next = p;
		}
	}
}

static void	init_coins(t_game *g)
{
	int		i;
	t_point	p;

	i = 0;
	p = (t_point){-1, -1};
	g->coins = ft_calloc(g->map->num_collectibles, sizeof(t_entity));
	if (!g->coins)
		message(g, "Failed allocation on coins entity array\n");
	while (++p.y < g->map->rows)
	{
		p.x = -1;
		while (++p.x < g->map->cols)
		{
			if (at(g, p) != COLLECTIBLE)
				continue ;
			g->coins[i].frame = rand() % NUM_COIN_FRAMES;
			g->coins[i].frame_freq = CALLS_PER_FRAME;
			g->coins[i].animate_speed = ANIMATE_CALLS;
			g->coins[i].type = COLLECTIBLE;
			g->coins[i++].pos = p;
		}
	}
}
void	init(char *filename)
{
	t_game	g;

	ft_bzero(&g, sizeof(t_game));
	ft_bzero(&g.player, sizeof(t_entity));
	read_map(&g, filename);
	validate_map(&g);
	init_graphics(&g);
	init_player(&g);
	init_enemies(&g);
	init_coins(&g);
	load_sprites(&g);
	render_map(&g);
	mlx_hook(g.disp.win, ON_KEYPRESS, KEYPRESS_MASK, move_handler, &g);
	mlx_hook(g.disp.win, ON_CLOSE, CLOSE_MASK, quit, &g);
	mlx_loop_hook(g.disp.mlx, render_frame, &g);
	mlx_loop(g.disp.mlx);
}
