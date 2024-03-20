/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsobane <hsobane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:48:58 by hsobane           #+#    #+#             */
/*   Updated: 2024/03/20 02:34:31 by hsobane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	width = 14;
int	height = 12;

char *map[] = {
	"11111111111111",
	"10000000000001",
	"10001000010001",
	"1000000E000001",
	"10010000000001",
	"11111111111111",
	NULL,
};

int ft_close(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

bool ft_check_hcol(t_data *data, double angle)
{
	t_fpoint h_col;
	double offset;
	double dist;
	
	offset = 10.;
	h_col = ft_h_ray(data, data->player.x * TILE_SIZE, data->player.y * TILE_SIZE, angle);
	if (h_col.x == -1)
		return (true);
	dist = ft_distance(data->player.x * TILE_SIZE, data->player.y * TILE_SIZE, h_col.x, h_col.y);
	if (dist > offset)
		return (true);
	return (false);
}

bool ft_check_vcol(t_data *data, double angle)
{
	t_fpoint v_col;
	double offset;
	double dist;
	
	offset = 10.;
	v_col = ft_v_ray(data, data->player.x * TILE_SIZE, data->player.y * TILE_SIZE, angle);
	if (v_col.x == -1)
		return (true);
	dist = ft_distance(data->player.x * TILE_SIZE, data->player.y * TILE_SIZE, v_col.x, v_col.y);
	if (dist > offset)
		return (true);
	return (false);
}

void	ft_move_x_y(t_data *data, double x, double y, double offset)
{
	double	xp;
	double	yp;

	xp = data->player.x + x * SPEED;
	yp = data->player.y + y * SPEED;
	if (ft_check_hcol(data, data->player.dir + offset))
		data->player.y = yp;
	if (ft_check_vcol(data, data->player.dir + offset))
		data->player.x = xp;
}

void move_player(t_data *data)
{
	if (data->key == K_W)
		ft_move_x_y(data, cos(data->player.dir), -sin(data->player.dir), 0);
	else if (data->key == K_S)
		ft_move_x_y(data, -cos(data->player.dir), sin(data->player.dir), -PI);
	else if (data->key == K_A)
		ft_move_x_y(data, cos(data->player.dir + PI / 2), -sin(data->player.dir + PI / 2), PI / 2);
	else if (data->key == K_D)
		ft_move_x_y(data, cos(data->player.dir - PI / 2), -sin(data->player.dir - PI / 2), -PI / 2);
}

static void ft_move(t_data *data)
{
	move_player(data);
	if (data->arrow_key == K_LEFT)
		data->player.dir += PI / 64;
	else if (data->arrow_key == K_RIGHT)
		data->player.dir -= PI / 64;
	if (data->player.dir < 0)
		data->player.dir += TWO_PI;
	else if (data->player.dir > TWO_PI)
		data->player.dir -= TWO_PI;
	data->arrow_key = NULL_KEY;
	data->moved = true;
}

int key_hook_press(int keycode, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keycode == ESC)
		ft_close(data);
	data->moved = true;
	if (keycode == W)
		data->key = K_W;
	else if (keycode == A)
		data->key = K_A;
	else if (keycode == S)
		data->key = K_S;
	else if (keycode == D)
		data->key = K_D;
	if (keycode == LEFT)
		data->arrow_key = K_LEFT;
	else if (keycode == RIGHT)
		data->arrow_key = K_RIGHT;
	ft_move(data);
	return (0);
}

int key_hook_release(int keycode, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keycode == W || keycode == A || keycode == S || keycode == D)
		data->key = NULL_KEY;
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
			mlx_pixel_put(mlx.mlx, mlx.mini_win, x * TILE_SIZE + i, y * TILE_SIZE + j, color);
			j++;
		}
		i++;
	}
}

void draw_player(t_data *data, t_player player)
{
	draw_square(data, (t_point){player.x * TILE_SIZE, player.y * TILE_SIZE}, 10, 0xFF0000);
}

void	draw_map(t_data *data)
{
	int i;
	int j;
	int k;
	int color;
	int *img;
	
	data->map_img = mlx_new_image(data->mlx.mlx, data->mlx.width * TILE_SIZE, data->mlx.height * TILE_SIZE);
	img = (int *)mlx_get_data_addr(data->map_img, &i, &j, &color);
	i = 0;
	while (i < data->mlx.height * TILE_SIZE)
	{
		j = 0;
		while (j < data->mlx.width && i % TILE_SIZE != 0)
		{
			k = 0;
			while (k < TILE_SIZE - 1)
			{
				if (data->map[i / TILE_SIZE][j] == '1')
					img[i * data->mlx.width * TILE_SIZE + j * TILE_SIZE + k] = 0x808080;
				else
					img[i * data->mlx.width * TILE_SIZE + j * TILE_SIZE + k] = 0xFFFFFF;
				k++;
			}
			j++;
		}
		i++;
	}
}

int game_loop(void *param)
{
	t_data *data;
	data = (t_data *)param;

	if (data->moved == false && data->key == NULL_KEY)
		return (0);
	ft_move(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mini_win, data->map_img, 0, 0);
	draw_player(data, data->player);
	double angle = data->player.dir - ft_rad(30);
	int	i = 0;
	while (i < WIDTH)
	{
		t_fpoint col = ft_raycast_collision(data, angle, i);
		draw_line(data, (t_line){(t_point){data->player.x * TILE_SIZE, data->player.y * TILE_SIZE},
			(t_point){col.x, col.y}}, 0x00FF00);
		angle += ft_rad(60. / WIDTH);
		i++;
	}
	ft_render(data);
	data->moved = false;
	return (0);
}

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_maxlen(char **map)
{
	int i;
	int max;

	i = 0;
	max = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

int	ft_argslen(char **map)
{
	int i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	ft_player_pos(t_player *player, char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
			{
				player->x = j;
				player->y = i;
				if (map[i][j] == 'N')
					player->dir = -PI / 2;
				else if (map[i][j] == 'S')
					player->dir = PI / 2;
				else if (map[i][j] == 'W')
					player->dir = PI;
				else if (map[i][j] == 'E')
					player->dir = 0;
				return ;
			}
			j++;
		}
		i++;
	}
	printf("Error\nNo player position found\n");
	exit(1);
}

void	init_game_img(t_data *data)
{
	data->game_bg.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	data->game_bg.addr = mlx_get_data_addr(data->game_bg.img, &data->game_bg.bpp,
		&data->game_bg.line_len, &data->game_bg.endian);
}

void	init_textures(t_data *data)
{
	// int i;

	// i = 0;
	// while (i < 5)
	// {
	// 	data->tex[i].img = mlx_xpm_file_to_image(data->mlx.mlx, data->tex_path[i],
	// 		&data->tex[i].width, &data->tex[i].height);
	// 	data->tex[i].addr = mlx_get_data_addr(data->tex[i].img, &data->tex[i].bpp,
	// 		&data->tex[i].line_len, &data->tex[i].endian);
	// 	i++;
	// }
	data->tex[0].img = mlx_xpm_file_to_image(data->mlx.mlx, "texture/haru_north.xpm",
		&data->tex[0].width, &data->tex[0].height);
	data->tex[0].addr = mlx_get_data_addr(data->tex[0].img, &data->tex[0].bpp,
		&data->tex[0].line_len, &data->tex[0].endian);
	data->tex[1].img = mlx_xpm_file_to_image(data->mlx.mlx, "texture/haru_south.xpm",
		&data->tex[1].width, &data->tex[1].height);
	data->tex[1].addr = mlx_get_data_addr(data->tex[1].img, &data->tex[1].bpp,
		&data->tex[1].line_len, &data->tex[1].endian);
	data->tex[2].img = mlx_xpm_file_to_image(data->mlx.mlx, "texture/odeok_east.xpm",
		&data->tex[2].width, &data->tex[2].height);
	data->tex[2].addr = mlx_get_data_addr(data->tex[2].img, &data->tex[2].bpp,
		&data->tex[2].line_len, &data->tex[2].endian);
	data->tex[3].img = mlx_xpm_file_to_image(data->mlx.mlx, "texture/odeok_west.xpm",
		&data->tex[3].width, &data->tex[3].height);
	data->tex[3].addr = mlx_get_data_addr(data->tex[3].img, &data->tex[3].bpp,
		&data->tex[3].line_len, &data->tex[3].endian);
}

int main(int argc, char const *argv[])
{
	t_data data;

	(void)argc;
	(void)argv;
	ft_player_pos(&data.player, map);
	data.player.plane = PI / 4;
	data.moved = true;
	data.mlx.width = ft_maxlen(map);
	data.mlx.height = ft_argslen(map);
	data.map = map;
	data.mlx.mlx = mlx_init();
	data.mlx.mini_win = mlx_new_window(data.mlx.mlx, TILE_SIZE * data.mlx.width,
		TILE_SIZE * data.mlx.height, "MiniMap");
	data.mlx.game_win = mlx_new_window(data.mlx.mlx, WIDTH, HEIGHT, "Cub3D");
	init_game_img(&data);
	init_textures(&data);
	draw_map(&data);
	mlx_hook(data.mlx.mini_win, 17, 1L << 17, ft_close, &data);
	mlx_hook(data.mlx.game_win, 17, 1L << 17, ft_close, &data);
	mlx_hook(data.mlx.mini_win, 2, 1L << 0, key_hook_press, &data);
	mlx_hook(data.mlx.game_win, 2, 1L << 0, key_hook_press, &data);
	mlx_hook(data.mlx.mini_win, 3, 1L << 1, key_hook_release, &data);
	mlx_hook(data.mlx.game_win, 3, 1L << 1, key_hook_release, &data);
	mlx_loop_hook(data.mlx.mlx, game_loop, &data);
	mlx_loop(data.mlx.mlx);
	return (0);
}
