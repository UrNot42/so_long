/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:54:43 by ulevallo          #+#    #+#             */
/*   Updated: 2023/04/14 10:03:41 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* --==--==--==--==--INCLUDES--==--==--==--==-- */

# define XK_MISCELLANY
# define XK_LATIN1
# include <X11/keysymdef.h>
# include <X11/X.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/time.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include "get_next_line/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"

/* --==--==--==--==--DEFINES--==--==--==--==-- */

# define IMG_SIZE 16
# define MAX_LIVES 5
# define RENDER_TIME 120000
# define MAP_EXTENSION ".ber"
# define IMG_FOLDER "images/xpm/"

/* -=-=-=-=-DIRECTION-=-=-=-=- */

enum e_directions
{
	NORTH = 1,
	WEST,
	SOUTH,
	EAST
};

/* -=-=-=-=-GAME_STATES-=-=-=-=- */

enum e_states
{
	INGAME_STATE = 1,
	PAUSED_STATE,
	WORLD_MAP_STATE,
	FINAL_SCREEN_STATE
};

/* -=-=-=-=-TILES-=-=-=-=- */

# define EMPTY_TILE '0'
# define WALL_TILE '1'
# define WALL_TILE_2 '2'
# define EXIT_TILE 'E'
# define KEY_TILE 'C'
# define PLAYER_TILE 'P'
# define CHEST_TILE 'c'
# define OPENED_CHEST_TILE 'O'
# define DOOR_TILE 'D'
# define DOOR_KEY_TILE 'H'
# define OPENED_DOOR_TILE 'd'
# define ENEMY_TILE 'e'
# define DRINK_TILE 'W'
# define MIMIC_TILE 'M'
# define GHOST_TILE 'G'
# define BIRD_TILE 'B'
# define MOVED_GHOST 'g'
# define MOVED_BIRD 'f'
# define CHICKEN_TILE 'K'
# define STONE_SWORD_TILE 'S'
# define STONE_TILE 's'
# define TP_PAD_A_TILE 'a'
# define TP_PAD_B_TILE 'b'
# define TP_PAD_T_TILE 't'
# define TP_PAD_X_TILE 'x'
# define TP_PAD_Y_TILE 'y'
# define TP_PAD_Z_TILE 'z'

/* -=-=-=-=-COLORS-=-=-=-=- */

# define RED     "\033[1;31m"
# define GREEN   "\033[1;32m"
# define YELLOW  "\033[1;33m"
# define BLUE    "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN    "\033[1;36m"
# define RESET   "\033[0;0m"
# define BACK    "\033[F"
# define PREV_LN "\033[A"

/* --==--==--==--==--STRUCTURES--==--==--==--==-- */

typedef struct s_params	t_params;
typedef struct s_mlx	t_mlx;
typedef struct s_data	t_data;
typedef struct s_player	t_player;
typedef struct s_sprit	t_sprit;
typedef struct s_anim	t_anim;
typedef struct s_coord	t_coord;
typedef struct s_imgs	t_imgs;
typedef struct s_map	t_map;

struct	s_coord {
	int	x;
	int	y;
};

struct	s_player {
	t_coord	o;
	int		face;
	int		moves;
	int		keys;
	int		sword;
	int		drunk;
	bool	invis;
	bool	god;
};

struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
};

struct	s_sprit {
	t_data		*img;
	int			frame;
	int			size;
};

struct	s_map {
	bool		active;
	int			player;
	int			dir;
	int			state;
	int			nb_maps;
	int			nb_worlds;
	int			completed;
	int			w_completed;
	int			left_lvl_id;
	int			lives;
	char		***maps;
	char		**worlds;
	t_sprit		pane;
	t_sprit		heart;
	t_sprit		pad;
	t_data		path;
};

struct	s_imgs {
	bool		err;
	bool		open;
	bool		apo;
	t_data		bgd;
	t_data		fire;
	t_data		exit_cls;
	t_data		drink;
	t_data		wall_broken;
	t_sprit		exit;
	t_sprit		stone;
	t_sprit		grass;
	t_sprit		wall;
	t_sprit		key;
	t_sprit		player;
	t_sprit		enemy;
	t_sprit		mimic;
	t_sprit		ghost;
	t_sprit		bird;
	t_sprit		mimic_op;
	t_sprit		chest;
	t_sprit		door;
	t_sprit		a;
	t_sprit		b;
	t_sprit		t;
	t_sprit		x;
	t_sprit		y;
	t_sprit		z;
	t_sprit		chick;
	t_sprit		grave;
	t_sprit		wall_apo;
	t_sprit		button;
	t_data		bt_press;
	t_data		retry;
	t_data		resume;
	t_data		leave;
	t_data		finish;
	t_data		game_over;
};

struct	s_mlx
{
	void		*ptr;
	void		*win;
	char		*name;
	t_data		*data;
	int			pxl_size;
};

struct	s_anim {
	t_coord		pos;
	t_sprit		*sprite;
	int			frame;
};

struct	s_params
{
	t_mlx			mlx;
	t_imgs			imgs;
	t_map			world;
	bool			drawn;
	bool			printed;
	int				state;
	int				button;
	bool			pressed;
	bool			won;
	bool			died;
	t_anim			to_animate[100];
	int				prev_input[11];
	suseconds_t		time;
	suseconds_t		time_prev;
	char			*path;
	char			**map;
	char			**map_save;
	t_coord			size;
	t_player		p;
	int				mv_dir;
	int				total_keys;
	int				mode;
	bool			disco;
	int				hex_a;
	int				hex_r;
	int				hex_g;
	int				hex_b;
	int				col_ofst;
};

/* --==--==--==--==--FUNCTIONS--==--==--==--==-- */

/* -=-=-=-=-PARSING-=-=-=-=- */

int		check_map_size(char **map, t_coord *size);
bool	check_teleporters(char **map);
bool	look_for_tp(char **map, int x, int y, int *key);
bool	look_for_sword(char ***map, int x, int y);
bool	search_sword(char ***map, t_coord *pos);
bool	set_player(t_params *param, char **map);
bool	fill_map(char ***map, int fd);
bool	parse_map(t_params *prm, char **map);
bool	init_map(char *file, char ***map, bool silenced);
void	do_chicken(t_params *param, char **map);
bool	map_is_valid(t_params *param, char **map);

/* -=-=-=-=-GAME-=-=-=-=- */

int		game(t_params *param);
bool	so_long(t_params *param);
bool	start_map(t_params *params, char *file);
bool	start_game(t_params *params, char **files, int nb_worlds);
bool	init_parameters(t_params *param);
void	render_frames(t_params *param);
int		restart_game(t_params *param);
void	print_moves(t_params *param, int moves);
void	add_move(t_params *param);

/* -=-=-=-=-GAME_CLOSING-=-=-=-=- */

int		finish_map(t_params *param, bool win);
void	print_final_screen(t_params *param, bool win);
int		close_game(t_params *param);
void	end_map(t_params *param);
void	back_to_menu(t_params *param);

/* -=-=-=-=-KEYS-=-=-=-=- */

bool	is_left(int key);
bool	is_right(int key);
bool	is_up(int key);
bool	is_down(int key);
bool	is_start(int key);

/* -=-=-=-=-KEY_HOOKS-=-=-=-=- */

int		key_press(int key, t_params *param);
int		key_press_game(int key, t_params *param);
int		key_press_world_map(int key, t_params *param);
int		key_press_pause(int key, t_params *param);
int		key_pause_pressed(int key, t_params *param);

/* -=-=-=-=-MOUSE_HOOKS-=-=-=-=- */

int		mousse_press(int button, int x, int y, t_params *param);
int		mouse_move(int button, int x, int y, t_params *param);
int		mouse_enter(int button, int x, int y, t_params *param);

/* -=-=-=-=-MAP-=-=-=-=- */

void	get_tp(char **map, int *x, int *y);
char	looking_at(char **map, int x, int y, int face);
void	looking_at_coords(int *x, int *y, int face);

/*-=-=-=-=-=-WORLD_MAP-=-=-=-=-=-*/

bool	init_world(t_params *prm);
void	init_world_vars(t_params *param);
bool	init_world_imgs(t_params *prm);
void	display_world_map(t_params *paras);
void	put_pad(t_params *prm, int pos);
void	put_panel(t_params *prm, t_data img, int pos);
void	put_paths(t_params *prm, int left, int right);
void	put_world_map(t_params *prm, t_sprit *sprite, int offset);
void	draw_image(t_params *param, int x, int y, t_data *img);
int		launch_map(t_params *param);

/*-=-=-=-=-=-PAUSE_SCREEN-=-=-=-=-=-*/

void	darken_screen(t_params *param, int factor);
bool	pause_screen(t_params *params);
bool	pause_game(t_params *param);
void	print_buttons(t_params *param, bool pressed);

/*-=-=-=-=-=-GAME_EVENTS-=-=-=-=-=-*/

void	take_key(t_params *param, t_player *p);
void	add_key(t_params *param, t_player *p);
void	open_door(t_params *param, int x, int y);
void	open_chest(t_params *param, int x, int y);
bool	trigger_event(t_params *param);
void	trigger_mimic(t_params *param, int x, int y);
void	god_mode(t_params *param);
void	kill_enemy(t_params *param, int x, int y);
void	kill_chicken(t_params *param);
void	drink_bottle(t_params *param, int x, int y);
int		move_enemies(t_params *prm, char **map);
int		gets_killed(char **map, t_params *prm);
void	pickup_sword(t_params *param, int x, int y);

/* -=-=-=-=-PLAYER-=-=-=-=- */

bool	move_player(t_params *param, t_player *p);
void	change_player_pos(t_coord *pos, int direction);
void	spin_player(t_params *param, t_player *p, int dir);
void	on_tile(t_params *param, t_player *p, char tile);
void	torus(t_coord *pos, t_coord	*size);

/* -=-=-=-=-DRAW_TOOLS-=-=-=-=- */

void	print_screen(t_params *param);
void	print_map(t_params *param, bool just_sprites);
void	find_pxl_size(t_mlx *mlx, t_coord size, t_coord max, int cap);
void	get_color(uint32_t *color, char *img, t_params *prm, int offset);
void	draw_map(t_params *param, bool just_sprites);
void	draw_tile(t_params *param, int x, int y, char tile);
void	draw_player(t_params *param, int x, int y, int face);
void	draw_map_image(t_params *param, int x, int y, t_data *img);
void	draw_bgd(t_params *prm, int x, int y);
void	draw_animations(t_params *param);
void	pixel_put(t_mlx *mlx, int x, int y, uint32_t color);
t_data	*get_img(t_imgs *img, char tile, int offset);
t_data	*get_other_img(t_imgs *img, char tile, int offset);
t_data	*get_img_tp(t_imgs *img, char tile);
bool	is_sprite(char tile);

/* -=-=-=-=-TILES-=-=-=-=- */

int		rand_tile(t_params *param, int x, int y);
bool	is_hard_tile(char tile);
bool	is_empty_tile(char tile);
bool	is_enemy(char tile);
bool	is_wall_tile(char tile);
bool	is_key_tile(char tile);
bool	needs_bgd(char tile);
int		is_tp_pad(char tile);
bool	is_tile(char tile);
int		tile_index(t_params *param, int x, int y);
int		check_around(t_coord pos, t_player p, t_coord size, int exclude);

/* -=-=-=-=-TILES_SEARCHING-=-=-=-=- */

int		look_for_tile(char **map, char tile, t_coord *pos);
void	look_for_key(char ***map, t_coord *pos, int *key, bool sword);
bool	look_for_exit(char **map[2], int x, int y, bool sword);
bool	set_exit(char **nap);

/* -=-=-=-=-UPDATES-=-=-=-=- */

void	update_map(t_params *param, char **map);
void	update_sprites(t_imgs *imgs);
void	next_frame(t_sprit *sprite);

/* -=-=-=-=-ANIMATION-=-=-=-=- */

bool	is_anim(t_anim *anims, int x, int y);
void	add_element(t_anim array[100], t_sprit *sprite, int x, int y);
void	update_anims(t_anim array[100], char **map, t_params *param);
void	lower_anim(t_anim array[100], int up);

/* -=-=-=-=-MLX_TOOLS-=-=-=-=- */

void	start_mlx_loop_hooks(t_params *param);
void	start_mlx_win_hooks(t_params *param);
t_mlx	*init_mlx(t_mlx	*mlx, t_coord *size);
int		ft_close_win(t_params *param);
void	*init_window(t_mlx *mlx, t_coord *size);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
bool	init_display(t_params *param);
bool	make_window_image(t_mlx *mlx, t_coord *size);

/*-=-=-=-=-=-XPM-=-=-=-=-=-*/

bool	create_image(void *ptr, t_data *image, char *path);
bool	create_sprite(void *ptr, t_sprit *sprite, char *path, int frame);
bool	init_sprites(void *ptr, t_imgs *a, bool (*init)(void *, t_imgs*));
bool	init_mc_sprites(void *ptr, t_imgs *a);
bool	init_other_sprites(void *ptr, t_imgs *a);
bool	init_images(void *ptr, t_imgs *a);
bool	init_meadow_assets(void *ptr, t_imgs *a);
bool	init_desert_assets(void *ptr, t_imgs *a);
bool	init_lake_assets(void *ptr, t_imgs *a);

/* -=-=-=-=-FREE-=-=-=-=- */

void	free_double_str(char **a);
void	free_triple_str(char ***a);
char	**copy_double_str(char **dstr);
bool	copy_map(char **map, char ***copy, char ***tab);
void	free_data(t_mlx *mlx, t_data *to_free);
void	free_sprites(t_params *param, t_imgs *imgs);
void	free_sprite(t_params *param, t_sprit *to_free);
void	free_imgs(t_mlx *mlx, t_imgs *imgs);
void	free_world_images(t_params *param, t_map *world);

/* -=-=-=-=-MESSAGES-=-=-=-=- */

void	error_msg(int error);
void	help_msg(void);
void	win_msg(void);
void	death_msg(int error);
void	print_data(t_params *param);

#endif
