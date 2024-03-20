/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsobane <hsobane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:32:28 by hsobane           #+#    #+#             */
/*   Updated: 2024/03/19 21:50:47 by hsobane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_hwall(t_data *data, float x, float y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x > data->mlx.width * TILE_SIZE || y < 0 || y > data->mlx.height * TILE_SIZE)
		return (1);
	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_x >= data->mlx.width || map_y < 0 || map_y >= data->mlx.height
		|| (y - 1 >= 0 && data->map[map_y - 1][map_x] == '1'))
		return (1);
	return (data->map[map_y][map_x] == '1');
}

int is_vwall(t_data *data, float x, float y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x > data->mlx.width * TILE_SIZE || y < 0 || y > data->mlx.height * TILE_SIZE)
		return (1);
	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_x >= data->mlx.width || map_y < 0 || map_y >= data->mlx.height
		|| (x - 1 >= 0 && data->map[map_y][map_x - 1] == '1'))
		return (1);
	return (data->map[map_y][map_x] == '1');
}

t_fpoint	ft_h_ray(t_data *data, double x, double y, double dir)
{
	double		x_step;
	double		y_step;
	t_fpoint	h_col;

	if (sin(dir) == 0)
		return ((t_fpoint){-1., -1.});
	h_col.y = (int)(y / TILE_SIZE) * TILE_SIZE;
	if (sin(dir) < 0)
		h_col.y += TILE_SIZE;
	y_step = TILE_SIZE;
	if (sin(dir) > 0)
		y_step *= -1;
	h_col.x = x + (y - h_col.y) / tan(dir);
	// x_step = fabs(TILE_SIZE / tan(dir));
	// if (cos(dir) * sin(dir) > 0)
	// 	x_step *= -1;
	if (cos(dir) > 0)
		x_step = fabs(TILE_SIZE / tan(dir));
	else
	{
		x_step = TILE_SIZE / tan(dir);
		if (sin(dir) < 0)
			x_step *= -1;
	}
	while (!is_hwall(data, h_col.x, h_col.y))
	{
		h_col.x += x_step;
		h_col.y += y_step;
	}
	return (h_col);
}

t_fpoint	ft_v_ray(t_data *data, double x, double y, double dir)
{
	double		x_step;
	double		y_step;
	t_fpoint	v_col;

	if (cos(dir) == 0)
		return ((t_fpoint){-1., -1.});
	v_col.x = (int)(x / TILE_SIZE) * TILE_SIZE;
	if (cos(dir) > 0)
		v_col.x += TILE_SIZE;
	x_step = -TILE_SIZE;
	if (cos(dir) > 0)
		x_step *= -1;
	v_col.y = y + (x - v_col.x) * tan(dir);
	// y_step = fabs(TILE_SIZE * tan(dir));
	// if (cos(dir) * sin(dir) > 0)
	// 	y_step *= -1;
	if (sin(dir) < 0)
		y_step = fabs(TILE_SIZE * tan(dir));
	else
	{
		y_step = TILE_SIZE * tan(dir);
		if (cos(dir) > 0)
			y_step *= -1;
	}
	while (!is_vwall(data, v_col.x, v_col.y))
	{
		v_col.x += x_step;
		v_col.y += y_step;
	}
	return (v_col);
}

double	ft_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

t_side	get_tex_num(t_data *data, t_ray *ray)
{
	(void)data;
	if (ray->og == HORIZ)
	{
		if (sin(ray->angle) > 0)
			return (SOUTH);
		return (NORTH);
	}
	if (cos(ray->angle) > 0)
		return (WEST);
	return (EAST);
}

t_fpoint	set_ray(t_data *data, t_fpoint col, double angle, int i)
{
	t_ray	*ray;

	ray = &data->rays[i];
	ray->angle = angle;
	ray->distance = ft_distance(data->player.x, data->player.y, col.x / TILE_SIZE, col.y / TILE_SIZE);
	ray->distance *= cos(fabs(data->player.dir - angle));
	ray->height = (int)(WIDTH / ray->distance);
	ray->top = (HEIGHT - ray->height) / 2;
	ray->bottom = ray->top + ray->height;
	if (ray->og == HORIZ)
		ray->offset = (int)col.x % TILE_SIZE;
	else if (ray->og == VERT)
		ray->offset = (int)col.y % TILE_SIZE;
	ray->tex_num = get_tex_num(data, ray);
	ray->side = ray->tex_num;
	return (col);
}

t_fpoint	set_vray(t_data *data, t_fpoint col, double angle, int i)
{
	data->rays[i].angle = angle;
	data->rays[i].og = VERT;
	return (set_ray(data, col, angle, i));
}

t_fpoint	set_hray(t_data *data, t_fpoint col, double angle, int i)
{
	data->rays[i].angle = angle;
	data->rays[i].og = HORIZ;
	return (set_ray(data, col, angle, i));
}

t_fpoint	ft_raycast_collision(t_data *data, double angle, int i)
{
	t_fpoint h_col;
	t_fpoint v_col;
	double	x;
	double	y;
	
	x = data->player.x * TILE_SIZE;
	y = data->player.y * TILE_SIZE;
	h_col = ft_h_ray(data, x, y, angle);
	v_col = ft_v_ray(data, x, y, angle);
	if (h_col.x == -1 || h_col.y == -1)
		return (set_vray(data, v_col, angle, i));
	else if (v_col.x == -1 || v_col.y == -1)
		return (set_hray(data, h_col, angle, i));
	if (ft_distance(data->player.x, data->player.y, h_col.x / TILE_SIZE, h_col.y / TILE_SIZE)
		< ft_distance(data->player.x, data->player.y, v_col.x / TILE_SIZE, v_col.y / TILE_SIZE))
		return (set_hray(data, h_col, angle, i));
	return (set_vray(data, v_col, angle, i));
}
