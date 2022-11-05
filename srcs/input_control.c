/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calion <calion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:55:50 by eisikogl          #+#    #+#             */
/*   Updated: 2022/11/06 00:20:52 by calion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int key_event(int key, t_gamedata *gamedata)
{
    if (key == 119) //linux:119 W
    {
		gamedata->player_y += gamedata->player_dx;
        gamedata->player_x += gamedata->player_dy;
        drawPlayer(gamedata);
    }
	if (key == 97) //linux:97 A
    {
		gamedata->player_x -= gamedata->player_dx;
        drawPlayer(gamedata);
    }
	if (key == 115) //linux:115 S
    {
		gamedata->player_y += gamedata->player_dx;
        gamedata->player_x += gamedata->player_dy;
        drawPlayer(gamedata);
    }
	if (key == 100) //linux:100 D
	{
        gamedata->player_x += gamedata->player_dx;
        drawPlayer(gamedata);
    }	
    if (key == 65361) //linux:65361 leftarrow
	{
        gamedata->player_angle -= 0.1;
        if(gamedata->player_angle < 0)
        {
            gamedata->player_angle += 2 * PI;
            gamedata->player_dx = cos(gamedata->player_angle) * 5;
            gamedata->player_dy = sin(gamedata->player_angle) * 5;
        }
        drawPlayer(gamedata);
    }
	if (key == 65363) //linux:65363 rightarrow
	{
        gamedata->player_angle += 0.1;
        if(gamedata->player_angle > 2 * PI)
        {
            gamedata->player_angle = 0;
            gamedata->player_dx = cos(gamedata->player_angle) * 5;
            gamedata->player_dy = sin(gamedata->player_angle) * 5;
        }
        drawPlayer(gamedata);
    }
	if (key == 65307) //linux:65307 ESC
		//exit_game(gamedata);
	return (0);
}
