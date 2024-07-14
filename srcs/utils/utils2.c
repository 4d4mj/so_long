/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:23:36 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/14 15:23:36 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	quit(t_game *game)
{
	destroy_game(game);
	exit(EXIT_SUCCESS);
}

void	*ft_new_matrix(int rows, int cols, size_t size)
{
	void	**mat;
	int		i;

	i = -1;
	mat = ft_calloc(rows, sizeof(void *));
	if (!mat)
		return (NULL);
	while (++i < rows)
	{
		mat[i] = ft_calloc(cols, size);
		if (!mat[i])
		{
			destroy_matrix(mat, rows);
			return (NULL);
		}
	}
	return (mat);
}

t_img	new_image(t_game *g, char *path)
{
	t_img	img;

	if (path)
		img.img = mlx_xpm_file_to_image(g->disp.mlx, \
			path, &(img.width), &(img.height));
	img.addr = mlx_get_data_addr(img.img, &img.bpp, \
		&img.line_len, &img.endian);
	return (img);
}

void	animate(t_game *g, t_entity *ent, t_sprite *frames, int n)
{
	int	i;
	int	frame_set;

	i = -1;
	while (++i < n)
	{
		if (++ent[i].curr_speed % ent[i].animate_speed != 0)
			continue ;
		if (is_same_point(ent[i].pos, (t_point){-1, -1}))
			continue ;
		if (++ent[i].curr_freq % ent[i].frame_freq == 0)
			ent[i].frame = (ent[i].frame + 1) % frames->nframes;
		render(g, &g->floor_sp.frames[0], ent[i].pos);
		if (ent[i].type == ENEMY)
			frame_set = g->enemy_status;
		else
			frame_set = ent[i].dir;
		render(g, &frames[frame_set].frames[ent[i].frame], ent[i].pos);
	}
}

bool	flood_fill(t_map *map, t_point curr, char **maze)
{
	static unsigned int	collected = 0;
	static bool			found_exit = false;

	if (maze[curr.y][curr.x] == WALL || maze[curr.y][curr.x] == ENEMY)
		return (false);
	else if (maze[curr.y][curr.x] == COLLECTIBLE)
		collected++;
	else if (maze[curr.y][curr.x] == EXIT)
		found_exit = true;
	maze[curr.y][curr.x] = WALL;
	flood_fill(map, (t_point){curr.x + 1, curr.y}, maze);
	flood_fill(map, (t_point){curr.x - 1, curr.y}, maze);
	flood_fill(map, (t_point){curr.x, curr.y + 1}, maze);
	flood_fill(map, (t_point){curr.x, curr.y - 1}, maze);
	return (collected == map->num_collectibles && found_exit);
}
