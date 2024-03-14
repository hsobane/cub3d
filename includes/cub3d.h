/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsobane <hsobane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:51:14 by hsobane           #+#    #+#             */
/*   Updated: 2024/03/14 12:08:45 by hsobane          ###   ########.fr       */
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
# include "parser.h"

# define TILE_SIZE 25
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
# define SPEED 0.1

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_line
{
	t_point	start;
	t_point	end;
}				t_line;

// linux keycodes
typedef enum e_key
{
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
	void	*win;
}				t_mlx;

typedef struct s_data
{
	t_mlx		mlx;
	t_player	player;
	t_key       key;
}				t_data;

void	draw_fov(t_data *data, t_point start, int color);
void	draw_line(t_data *data, t_line line, int color);


#endif