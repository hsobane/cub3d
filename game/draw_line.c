/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsobane <hsobane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:35:55 by hsobane           #+#    #+#             */
/*   Updated: 2024/03/19 23:35:17 by hsobane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// bresenham algorithm
void	draw_line(t_data *data, t_line line, int color)
{
	int dx;
	int dy;
	int dx1;
	int dy1;
	int px;
	int py;
	int xe;
	int ye;
	int x;
	int y;

	dx = (line.end.x - line.start.x);
	dy = (line.end.y - line.start.y);
	dx1 = abs(dx);
	dy1 = abs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = line.start.x;
			y = line.start.y;
			xe = line.end.x;
		}
		else
		{
			x = line.end.x;
			y = line.end.y;
			xe = line.start.x;
		}
		mlx_pixel_put(data->mlx.mlx, data->mlx.mini_win, x, y, color);
		while (x < xe)
		{
			x++;
			if (px < 0)
				px += 2 * dy1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
					y++;
				else
					y--;
				px += 2 * (dy1 - dx1);
			}
			mlx_pixel_put(data->mlx.mlx, data->mlx.mini_win, x, y, color);
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = line.start.x;
			y = line.start.y;
			ye = line.end.y;
		}
		else
		{
			x = line.end.x;
			y = line.end.y;
			ye = line.start.y;
		}
		mlx_pixel_put(data->mlx.mlx, data->mlx.mini_win, x, y, color);
		while (y < ye)
		{
			y++;
			if (py <= 0)
				py += 2 * dx1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
					x++;
				else
					x--;
				py += 2 * (dx1 - dy1);
			}
			mlx_pixel_put(data->mlx.mlx, data->mlx.mini_win, x, y, color);
		}
	}
}

void	put_line_to_img(t_data *data, t_line line)
{
	int dx;
	int dy;
	int dx1;
	int dy1;
	int px;
	int py;
	int xe;
	int ye;
	int x;
	int y;
	int	*img;
	int	i;
	int	j;

	img = (int *)mlx_get_data_addr(data->map_img, &i, &j, &dx1);
	dx = (line.end.x - line.start.x);
	dy = (line.end.y - line.start.y);
	dx1 = abs(dx);
	dy1 = abs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = line.start.x;
			y = line.start.y;
			xe = line.end.x;
		}
		else
		{
			x = line.end.x;
			y = line.end.y;
			xe = line.start.x;
		}
		img[y * data->mlx.width * TILE_SIZE + x] = 0x00FF00;
		while (x < xe)
		{
			x++;
			if (px < 0)
				px += 2 * dy1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
					y++;
				else
					y--;
				px += 2 * (dy1 - dx1);
			}
			img[y * data->mlx.width * TILE_SIZE + x] = 0x00FF00;
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = line.start.x;
			y = line.start.y;
			ye = line.end.y;
		}
		else
		{
			x = line.end.x;
			y = line.end.y;
			ye = line.start.y;
		}
			img[y * data->mlx.width * TILE_SIZE + x] = 0x00FF00;
		while (y < ye)
		{
			y++;
			if (py <= 0)
				py += 2 * dx1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
					x++;
				else
					x--;
				py += 2 * (dx1 - dy1);
			}
			img[y * data->mlx.width * TILE_SIZE + x] = 0x00FF00;
		}
	}
}

void draw_square(t_data *data, t_point center, int width, int color)
{
	int i;
	int j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < width)
		{
			mlx_pixel_put(data->mlx.mlx, data->mlx.mini_win, center.x - width / 2 + i, center.y - width / 2 + j, color);
			j++;
		}
		i++;
	}
}


void swap_points(t_point *p1, t_point *p2)
{
	t_point temp;

	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

double ft_slope(t_line line)
{
	int dx;
	int dy;

	dx = line.end.x - line.start.x;
	dy = line.end.y - line.start.y;
	if (dx == 0)
		return (INT_MAX);
	return ((double)dy / dx);
}

void ft_flip(t_line *line)
{
	int	temp;

	temp = line->start.x;
	line->start.x = line->start.y;
	line->start.y = temp;
	temp = line->end.x;
	line->end.x = line->end.y;
	line->end.y = temp;
}

void draw_ray_direction(t_data *data, t_point start, double angle, int color)
{
	t_line line;

	line.start = start;
	line.end.x = start.x + 1000 * cos(angle);
	line.end.y = start.y + 1000 * sin(angle);
	draw_line(data, line, color);
}

double ft_rad(double angle)
{
	return (angle * PI / 180);
}

// void draw_fov(t_data *data, t_point start, int color)
// {
// 	double angle;
// 	t_point end;

// 	angle = data->player.dir - ft_rad(FOV / 2);
// 	while (angle < data->player.dir + ft_rad(FOV / 2))
// 	{
// 		end.x = start.x + 250 * cos(angle);
// 		end.y = start.y + 250 * sin(angle);
// 		draw_line(data, (t_line){start, end}, color);
// 		angle += ft_rad(1);
// 	}
// }


// int main()
// {
// 	t_data data;

// 	data.player.dir = PI / 4;
// 	data.player.x = 250;
// 	data.player.y = 250;
	
// 	signal(SIGUSR1, sig_handler);
// 	data.mlx.mlx = mlx_init();
// 	data.mlx.mini_win = mlx_new_window(data.mlx.mlx, 500, 500, "draw_line");
// 	mlx_key_hook(data.mlx.mini_win, ft_close, &data);
// 	mlx_hook(data.mlx.mini_win, 17, 0, ft_key, &data);
// 	draw_fov(&data, (t_point){250, 250}, 0x00FF00);
// 	mlx_loop(data.mlx.mlx);
// }