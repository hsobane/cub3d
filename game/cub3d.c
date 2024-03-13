/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsobane <hsobane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:48:58 by hsobane           #+#    #+#             */
/*   Updated: 2024/03/13 16:22:37 by hsobane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	width = 14;
int	height = 12;

char *map[] = {
	"11111111111111",
	"10000000000001",
	"10000000000001",
	"10000000000001",
	"10000000000001",
	"10000000000001",
	"10000000000N01",
	"10000000000001",
	"10000000000001",
	"10000000000001",
	"10000000000001",
	"11111111111111",
};

int ft_close(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

static void ft_move(t_data *data)
{
	if (data->key == K_W)
	{
		data->player.x += cos(data->player.dir) * SPEED;
		data->player.y += sin(data->player.dir) * SPEED;
	}
	else if (data->key == K_S)
	{
		data->player.x -= cos(data->player.dir) * SPEED;
		data->player.y -= sin(data->player.dir) * SPEED;
	}
	else if (data->key == K_A)
	{
		data->player.x += cos(data->player.dir - PI / 2) * SPEED;
		data->player.y += sin(data->player.dir - PI / 2) * SPEED;
	}
	else if (data->key == K_D)
	{
		data->player.x += cos(data->player.dir + PI / 2) * SPEED;
		data->player.y += sin(data->player.dir + PI / 2) * SPEED;
	}
	else if (data->key == K_LEFT)
		data->player.dir -= PI / 8;
	else if (data->key == K_RIGHT)
		data->player.dir += PI / 8;
	if (data->player.dir > TWO_PI || data->player.dir < -TWO_PI)
		data->player.dir = 0;
	if (data->player.x < 0)
		data->player.x = 0;
	if (data->player.y < 0)
		data->player.y = 0;
	if (data->player.x > width - 1)
		data->player.x = width - 1;
	if (data->player.y > height - 1)	
		data->player.y = height - 1;
	data->key = 0;
}

int key_hook(int keycode, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keycode == ESC)
		ft_close(data);
	else if (keycode == W)
		data->key = K_W;
	else if (keycode == A)
		data->key = K_A;
	else if (keycode == S)
		data->key = K_S;
	else if (keycode == D)
		data->key = K_D;
	else if (keycode == LEFT)
		data->key = K_LEFT;
	else if (keycode == RIGHT)
		data->key = K_RIGHT;
	ft_move(data);
	return (0);
}

void put_cell(t_mlx mlx, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(mlx.mlx, mlx.win, x * TILE_SIZE + i, y * TILE_SIZE + j, color);
			j++;
		}
		i++;
	}
}

void draw_player(t_mlx mlx, t_player player)
{
	int i;
	int j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_pixel_put(mlx.mlx, mlx.win, player.x * TILE_SIZE + i, player.y * TILE_SIZE + j, 0xFF0000);
			j++;
		}
		i++;
	}
	mlx_do_sync(mlx.mlx);
}

void draw_line(t_data *data, t_line *line)
{
	int dx;
	int dy;
	int d;
	int i;
	int y;
	

	dx = abs(line->end.x - line->start.x);
	dy = abs(line->end.y - line->start.y);
	y = fmin(line->start.y, line->end.y);
	d = 2 * dy - dx;
	i = 0;
	while (i < dx)
	{
		mlx_pixel_put(data->mlx.mlx, data->mlx.win, line->start.x + i, y, 0x0000FF);
		if (d > 0)
		{
			// d > 0 means we need to move up or down
			y++;
			d -= 2 * dx;
		}
		// 
		d += 2 * dy;
		i++;
	}
	
}

double ft_cos(double angle)
{
	if (cos(angle) < 0)
		return (sin(angle));
	return (cos(angle));
}

double ft_sin(double angle)
{
	if (sin(angle) < 0)
		return (cos(angle));
	return (sin(angle));
}

int game_loop(void *param)
{
	t_data *data;
	data = (t_data *)param;
	
		
	// mlx_clear_window(data->mlx.mlx, data->mlx.win);
	// draw the map as a grid, 1 is a wall, 0 is empty space. "NWSE" are the player directions (North, West, South, East)
	// the player is represented by a red dot in the middle of the grid
	// the grid is 10x10, each cell is 64x64 pixels
	// the whole cell should be colored in grey if it's a wall, and white if it's empty

	// draw the player as a red dot of 10x10 pixels
	
	int i;
	int j;
	
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] == '1')
				put_cell(data->mlx, j, i, 0x808080);
			else
				put_cell(data->mlx, j, i, 0xFFFFFF);
			j++;
		}
		i++;
	}
	draw_player(data->mlx, data->player);
	t_line line;
	line = (t_line){(t_point){data->player.x * TILE_SIZE, data->player.y * TILE_SIZE},
		(t_point){data->player.x * TILE_SIZE + 100 * ft_cos(data->player.dir), data->player.y * TILE_SIZE + 100 * ft_sin(data->player.dir)}};
	draw_line(data, &line);
	usleep(1000000 / FPS);
	return (0);
}

int main(int argc, char const *argv[])
{
	t_data data;

	(void)argc;
	(void)argv;
	data.player.x = 5;
	data.player.y = 5;
	data.player.dir = 0;
	data.player.plane = PI / 4;
	
	data.mlx.mlx = mlx_init();
	data.mlx.win = mlx_new_window(data.mlx.mlx, TILE_SIZE * width, TILE_SIZE * height, "Cub3D");
	mlx_key_hook(data.mlx.win, key_hook, &data);
	mlx_hook(data.mlx.win, 17, 0, ft_close, &data);
	mlx_loop_hook(data.mlx.mlx, game_loop, &data);
	mlx_loop(data.mlx.mlx);
	return (0);
}
