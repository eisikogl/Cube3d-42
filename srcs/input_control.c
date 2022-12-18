/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calion <calion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:55:50 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/16 22:14:17 by calion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	left_arrow_key(t_gamedata *gamedata)
{
	gamedata->player_angle += PI / 100;
	if (gamedata->player_angle > 2 * PI)
	{
		gamedata->player_angle -= 2 * PI;
	}
	gamedata->player_dx = cos(gamedata->player_angle) * 5;
	gamedata->player_dy = sin(gamedata->player_angle) * 5;
	mlx_destroy_image(gamedata->mlx, gamedata->img2d);
	mlx_destroy_image(gamedata->mlx, gamedata->img3dwin);
	drawMap2(gamedata);
}

void	right_arrow_key(t_gamedata *gamedata)
{
	gamedata->player_angle -= PI / 100;
	if (gamedata->player_angle < 0)
	{
		gamedata->player_angle += 2 * PI;
	}
	gamedata->player_dx = cos(gamedata->player_angle) * 5;
	gamedata->player_dy = sin(gamedata->player_angle) * 5;
	mlx_destroy_image(gamedata->mlx, gamedata->img2d);
	mlx_destroy_image(gamedata->mlx, gamedata->img3dwin);
	drawMap2(gamedata);
}

int	key_event(int key, t_gamedata *gamedata)
{
	if (key == 119)
		w_key(gamedata);
	if (key == 97)
		a_key(gamedata);
	if (key == 115)
		s_key(gamedata);
	if (key == 100)
		d_key(gamedata);
	if (key == 65361)
		left_arrow_key(gamedata);
	if (key == 65363)
		right_arrow_key(gamedata);
	if (key == 65307)
	{
	}
	return (0);
}