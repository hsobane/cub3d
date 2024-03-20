/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsobane <hsobane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:51:14 by hsobane           #+#    #+#             */
/*   Updated: 2024/03/20 02:28:30 by hsobane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <mlx.h>
# include <signal.h>
# include <stdbool.h>
# include "parser.h"

# define TILE_SIZE 64
# define RAYS 60
# define FOV 60
# define PI 3.14159265358979323846
# define TWO_PI 6.28318530717958647692
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307
# define FPS 30
# define SPEED 0.04
# define WIDTH 1024
# define HEIGHT 768

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_fpoint
{
	double	x;
	double	y;
}				t_fpoint;

typedef struct s_line
{
	t_point	start;
	t_point	end;
}				t_line;

// linux keycodes
typedef enum e_key
{
	NULL_KEY = 0,
	K_W = 119,
	K_A = 97,
	K_S = 115,
	K_D = 100,
	K_LEFT = 65361,
	K_RIGHT = 65363,
	K_ESC = 65307
}				t_key;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir;
	double	plane;
}				t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*mini_win;
	void	*game_win;
	int		width;
	int		height;
}				t_mlx;

typedef enum e_orientation
{
	VERT,
	HORIZ
}				t_orientation;

typedef enum e_side
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	SPRITE
}			t_side;

typedef struct s_ray
{
	t_fpoint		col;
	double			height;
	double			angle;
	double			distance;
	double			top;
	double			bottom;
	double			offset;
	t_orientation	og;
	t_side			side;
	int				tex_num;
}				t_ray;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_data
{
	t_mlx		mlx;
	t_player	player;
	t_key       key;
	t_key		arrow_key;
	char		**map;
	void		*map_img;
	t_img		game_bg;
	t_img		tex[5];
	t_ray		rays[WIDTH];
	bool		moved;
}				t_data;

void		draw_fov(t_data *data, t_point start, int color);
void		draw_line(t_data *data, t_line line, int color);
t_fpoint	ft_raycast_collision(t_data *data, double angle, int i);

void		put_line_to_img(t_data *data, t_line line);
void		draw_square(t_data *data, t_point center, int width, int color);
double		ft_rad(double angle);
double		ft_distance(float x1, float y1, float x2, float y2);

void	ft_render(t_data *data);

t_fpoint	ft_h_ray(t_data *data, double x, double y, double dir);
t_fpoint	ft_v_ray(t_data *data, double x, double y, double dir);

#endif