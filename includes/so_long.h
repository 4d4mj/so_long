/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:06:16 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/15 19:03:49 by ajabado          ###   ########.fr       */
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
# define PX 32

# define GAME_WIN "You Win!"
# define GAME_LOSE "You Lose."

// Sprite counters
# define NUM_WALLS			1
# define NUM_PLAYER_FRAMES	10
# define NUM_COIN_FRAMES	6
# define NUM_ENEMY_FRAMES	8
# define NUM_EXIT_FRAMES	10
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
	ENTER = 65293,
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

// 2D pointer
typedef struct s_point
{
	unsigned int	x;
	unsigned int	y;
}				t_point;

// map structure
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

// image structure
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

// sprite frames
typedef struct s_sprite
{
	t_img	*frames;
	int		nframes;
}				t_sprite;

// display structure
typedef struct s_display
{
	void	*mlx;
	void	*win;
	t_point	dims;
}				t_display;

// entity structure
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

// game structure
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
	t_entity		exit;
	t_status		enemy_status;
	bool			collected_all;
	void			(*enemy_strategy)();
	unsigned int	collected;
	unsigned int	moves;
}					t_game;

//map
void		validate_map(t_game *g);
void		read_map(t_game *game, char *filename);

//destroy
void		destroy_game(t_game *game);
void		destroy_matrix(void *matrix, size_t rows);

// init
void		init(char *filename);
void		load_sprites(t_game *g);

// enemy
void		move_enemy(t_game *g);
bool		enemy_can_move(t_game *g, t_point p);
bool		enemy_has_possible_moves(t_game *g, t_point *pos);
void		chase_strategy(t_game *g, t_entity *enemy);
void		random_strategy(t_game *g, t_entity *enemy);
void		change_strategy(t_game *g, void (*strategy)(), t_status status);

// player movement
int			move_handler(int keycode, t_game *g);
bool		player_can_move(t_game *g, t_entity *e);
void		move_player(t_game *game);
void		player_controller(t_game *g);

// render
void		render(t_game *g, t_img *img, t_point p);
void		render_tile(t_game *g, t_point p);
void		render_map(t_game *g);
void		render_counter(t_game *g);
int			render_frame(t_game *g);

// utils
int			ft_tonum(int c);
int			ft_tochar(int c);
int			quit(t_game *game);
void		ft_free(void *ptr);
t_type		at(t_game *g, t_point p);
t_img		new_image(t_game *g, char *path);
void		message(t_game *game, char *text);
void		set(t_game *g, t_point p, t_type type);
bool		is_same_point(t_point p1, t_point p2);
void		*ft_new_matrix(int rows, int cols, size_t size);
bool		flood_fill(t_map *map, t_point curr, char **maze);
void		animate(t_game *g, t_entity *ent, t_sprite *frames, int n);
void		display_game_over(t_game *g, char *s);

#endif
