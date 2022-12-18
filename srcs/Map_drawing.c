/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calion <calion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:42:20 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/16 23:40:09 by calion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	starting_pos(t_gamedata *gamedata,char orient)
{
	if (orient == 'N')
		gamedata->player_angle = PI / 2;
	else if (orient == 'S')
		gamedata->player_angle = P3;
	else if (orient == 'E')
		gamedata->player_angle = 0;
	else if (orient == 'W')
		gamedata->player_angle = PI;

	gamedata->player_dx = cos(gamedata->player_angle) * 5;
	gamedata->player_dy = sin(gamedata->player_angle) * 5;
	pixelPlayer(gamedata);
}

void	drawMap(t_gamedata *call_map)
{
	int		i;
	int		j;
	int		x;
	int		y;
	char	orient;

	y = 0;
	i = 0;
	render_floor(call_map, call_map->trgb_floor);
	render_ceiling(call_map, call_map->trgb_ceiling);
	render_bg_map(call_map, call_map->trgb_floor);
	while (call_map->map_split[i] != NULL)
	{
		j = 0;
		x = 0;
		while (call_map->map_split[i][j] != '\0')
		{
			if (call_map->map_split[i][j] == '1')
			{
				render_rect(call_map, x, y);
			}
			if (call_map->map_split[i][j] == 'N' || call_map->map_split[i][j] == 'S' || call_map->map_split[i][j] == 'W' || call_map->map_split[i][j] == 'E') //angles for S W E
			{
				call_map->player_x = x;
				call_map->player_y = y;
				orient = call_map->map_split[i][j];
				starting_pos(call_map, orient);
			}
			x += 16;
			j++;
		}
		y += 16;
		i++;
	}
	mlx_put_image_to_window(call_map->mlx, call_map->mlx_window, call_map->img2d, 0, 0);
	mlx_put_image_to_window(call_map->mlx, call_map->mlx_3dwindow, call_map->img3dwin, 0, 0);
}

void	drawMap2(t_gamedata *call_map)
{
	int	i;
	int	j;
	int	x;
	int	y;

	y = 0;
	i = 0;
	call_map->img2d = mlx_new_image(call_map->mlx, call_map->mapX * 16, call_map->mapY * 16);
	call_map->img3dwin = mlx_new_image(call_map->mlx, 1024, 512);
	render_floor(call_map, call_map->trgb_floor);
	render_ceiling(call_map, call_map->trgb_ceiling);
	render_bg_map(call_map, call_map->trgb_floor);
	while (call_map->map_split[i] != NULL)
	{
		j = 0;
		x = 0;
		while (call_map->map_split[i][j] != '\0')
		{
			if (call_map->map_split[i][j] == '1')
			{
				render_rect(call_map, x, y);
				x += 16;
			}
			else
			{
				x += 16;
			}
			j++;
		}
		y += 16;
		i++;
	}
	pixelPlayer(call_map);
	mlx_put_image_to_window(call_map->mlx, call_map->mlx_window, call_map->img2d, 0, 0);
	mlx_put_image_to_window(call_map->mlx, call_map->mlx_3dwindow, call_map->img3dwin, 0, 0);
}

