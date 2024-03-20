/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsobane <hsobane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:32:02 by hsobane           #+#    #+#             */
/*   Updated: 2024/03/19 21:37:42 by hsobane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_data *data, int color)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	while (i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			dst = data->game_bg.addr + (i * data->game_bg.line_len + j * (data->game_bg.bpp / 8));
			*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
}

void	draw_floor(t_data *data, int color)
{
	int		i;
	int		j;
	char	*dst;

	i = HEIGHT / 2;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			dst = data->game_bg.addr + (i * data->game_bg.line_len + j * (data->game_bg.bpp / 8));
			*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
}

int	get_tex_color(t_data *data, t_ray ray, int j)
{
	int		texel_color;
	char	*dst;
	int		texel_x;
	int		texel_y;

	texel_x = (int)ray.offset;
	texel_y = (int)(j * (data->tex[ray.tex_num].height / ray.height));
	dst = data->tex[ray.tex_num].addr + (texel_y * data->tex[ray.tex_num].line_len
			+ texel_x * (data->tex[ray.tex_num].bpp / 8));
	texel_color = *(unsigned int *)dst;
	return (texel_color);
}

int	get_simple_color(t_data *data, t_ray ray, int j)
{
	(void)data;
	(void)j;

	if (ray.side == NORTH)
		return (0x00a4f01d);
	if (ray.side == SOUTH)
		return (0x0076f5e8);
	if (ray.side == EAST)
		return (0x00942cd1);
	if (ray.side == WEST)
		return (0x00cd4594);
	return (0x00000000);
}

void	ft_draw_ray(t_data *data, int i)
{
	t_ray	ray;
	char	*dst;
	int		j;

	ray = data->rays[i];
	j = 0;
	while (j < (int)ray.height)
	{
		if ((int)data->rays[i].top + j < 0)
		{
			j++;
			continue ;
		}
		if ((int)data->rays[i].top + j >= HEIGHT)
			break ;
		if (WIDTH - i < 0)
			break ;
		if (WIDTH - i >= WIDTH)
			break ;
		dst = data->game_bg.addr + ((int)data->rays[i].top + j) * data->game_bg.line_len
			+ (WIDTH - i) * (data->game_bg.bpp / 8);
		*(unsigned int *)dst = get_tex_color(data, ray, j);
		j++;
	}
}

// draw rays in the mean window (game_win)
void	ft_render(t_data *data)
{
	int	i;

	// ceil in light blue, and floor in dark blue
	draw_ceiling(data, 0x0000FFFF);
	draw_floor(data, 0x000000FF);
	i = 0;
	while (i < WIDTH)
	{
		ft_draw_ray(data, i);
		i++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.game_win, data->game_bg.img, 0, 0);
}
