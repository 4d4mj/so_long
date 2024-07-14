/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:06:16 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/14 15:36:15 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/includes/libft.h"
# include "../mlx/mlx.h"

# include <math.h>
# include <time.h>
# include <stdbool.h>

# define ENTITIES			"01CEPM"
# define NOT_USED			'N'

// Sprite counters
# define NUM_WALLS			31
# define NUM_PLAYER_FRAMES	7
# define NUM_COIN_FRAMES	15
# define NUM_ENEMY_FRAMES	8
# define NUM_EXIT_FRAMES	1
# define NUM_FLOOR_FRAMES	1

// sprite animation refresh frequency
# define ANIMATE_CALLS		250
# define CALLS_PER_FRAME	40
# define MOVE_CALLS			50000

// image paths
# define PLAYER_RIGHT_PATH	"images/player/right/player_"
# define PLAYER_LEFT_PATH	"images/player/left/player_"
# define ENEMY_CALM_PATH	"images/enemies/calm/enemy_"
# define ENEMY_RAGE_PATH	"images/enemies/rage/enemy_"
# define COLLECTIBLE_PATH	"images/collectible/collectible_"
# define WALL_PATH			"images/walls/wall_"
# define EXIT_PATH			"images/exit/exit_"
# define FLOOR_PATH			"images/floor/floor_"

// sprite type
typedef enum e_type
{
	COLLECTIBLE = 'C',
	FLOOR = '0',
	WALL = '1',
	EXIT = 'E',
	ENEMY = 'M',
	PLAYER = 'P',
}			t_type;

// sprite direction
typedef enum e_direction
{
	RIGHT,
	LEFT,
	UP,
	DOWN
}			t_direction;

// sprite movement keys
typedef enum e_key
{
	ESC = 65307,
	K_UP = 65362,
	K_LEFT = 65361,
	K_DOWN = 65364,
	K_RIGHT = 65363
}	t_key;

// enemy status
typedef enum e_status
{
	NORMAL,
	ENRAGED,
}	t_status;

// event codes
typedef enum e_event
{
	ON_KEYPRESS = 2,
	ON_CLOSE = 17,
}				t_event;

// event masks
typedef enum e_mask
{
	KEYPRESS_MASK,
	CLOSE_MASK,
}			t_mask;

// wall types
typedef enum e_wall
{
	WALL_U,
	WALL_L,
	WALL_R,
	CORNER_L,
	CORNER_R,
	WALL_D,
	BARRIER_L,
	BARRIER_R,
	PIPE_H,
	PIPE_V,
	EDGE_U,
	EDGE_D,
	EDGE_L,
	EDGE_R,
	BOUNDED,
	BOUNDLESS,
	CORNER_DL,
	CORNER_DR,
	CORNER_UL_2,
	CORNER_UR_2,
	CORNER_DL_2,
	CORNER_DR_2,
	BOUNDLESS_2,
	BARRIER_L_2,
	BARRIER_R_2,
	BARRIER_U_2,
	BARRIER_D_2,
	CORNER_BDL,
	CORNER_BDR,
	CORNER_BUL,
	CORNER_BUR,
}				t_wall;

typedef struct s_point
{
	unsigned int	x;
	unsigned int	y;
}				t_point;

typedef struct s_map
{
	char			**bytes;
	unsigned int	cols;
	unsigned int	rows;
	unsigned int	num_collectibles;
	unsigned int	num_exits;
	unsigned int	num_players;
	unsigned int	num_enemies;
}				t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_sprite
{
	t_img	*frames;
	int		nframes;
}				t_sprite;

typedef struct s_display
{
	void	*mlx;
	void	*win;
	t_point	dims;
}				t_display;

typedef struct s_entity
{
	int			frame;
	int			frame_freq;
	int			curr_freq;
	int			e_move_counter;
	int			e_move_freq;
	int			animate_speed;
	int			curr_speed;
	t_type		type;
	t_direction	dir;
	t_point		pos;
	t_point		next;
}				t_entity;

typedef struct s_game
{
	t_map			*map;
	t_display		disp;
	t_sprite		*player_sp;
	t_sprite		*enemy_sp;
	t_sprite		floor_sp;
	t_sprite		walls_sp;
	t_sprite		exit_sp;
	t_sprite		collectibles_sp;
	t_entity		player;
	t_entity		*enemies;
	t_entity		*coins;
	t_status		enemy_status;
	void			(*enemy_strategy)();
	unsigned int	collected;
	unsigned int	moves;
}					t_game;

void		animate(t_game *g, t_entity *ent, t_sprite *frames, int n);

//map
bool		flood_fill(t_map *map, t_point curr, char **maze);
bool		diags(int **mat, t_point *p, char *diagonals);
bool		sides(int **mat, t_point *p, char *diagonals);
void		fill_bin_matrix(t_game *g, int **mat);
void		*ft_new_matrix(int rows, int cols, size_t size);

//destroy
void		destroy_game(t_game *game);
void		destroy_matrix(void *matrix, size_t rows);

// init
void		init_game(char *filename);

// image
t_img		new_image(t_game *g, t_point dims);
t_img		new_file_image(t_game *g, char *path);
void		load_xpm(t_game *g, t_sprite *s, char *prefix, int n);
void		load_static_entites_frames(t_game *g);
void		load_enemies_frames(t_game *g);
void		load_player_frames(t_game *g);
void		load_sprites(t_game *g);

// main
int			quit(t_game *game);
void		validate_map(t_game *g);

// enemy
bool		enemy_can_move(t_game *g, t_point p);
bool		enemy_has_possible_moves(t_game *g, t_point *pos);
void		move_enemies(t_game *g);

// player movement
int			move_handler(int keycode, t_game *g);
bool		player_can_move(t_game *g, t_entity *e);
void		move_player(t_game *game);
void		player_controller(t_game *g);

// read map
void		read_map(t_game *game, char *filename);
t_type		at(t_game *g, t_point p);
void		set(t_game *g, t_point p, t_type type);

// render
void		render(t_game *g, t_img *img, t_point p);
void		render_tile(t_game *g, t_point p);
void		render_map(t_game *g);
void		render_counter(t_game *g);
int			render_frame(t_game *g);

// render walls
t_wall		pick_wall_sprite_3(t_point *p, int **mat);
t_wall		pick_wall_sprite_2(t_point *p, int **mat);
t_wall		pick_wall_sprite(t_point p, int **mat);
void		render_inner_walls(t_game *g);
void		render_outter_walls(t_game *g);

// strategy
void		change_strategy(t_game *g, void (*strategy)(), t_status status);
void		random_strategy(t_game *g, t_entity *enemy);
void		chase_strategy(t_game *g, t_entity *enemy);

// utils
void		message(t_game *game, char *text);
int			ft_tochar(int c);
int			ft_tonum(int c);
bool		is_same_point(t_point p1, t_point p2);
void		ft_free(void *ptr);

#endif
