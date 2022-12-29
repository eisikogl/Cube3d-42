/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:42:20 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/29 17:10:41 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	init_textures(t_gamedata *gamedata)
{
	int	x;
	int	i;

	x = 64;
	gamedata->texture_active_img[0] = mlx_xpm_file_to_image(gamedata->mlx, \
	gamedata->no_path, &x, &x);
	gamedata->texture_active_img[1] = mlx_xpm_file_to_image(gamedata->mlx, \
	gamedata->so_path, &x, &x);
	gamedata->texture_active_img[2] = mlx_xpm_file_to_image(gamedata->mlx, \
	gamedata->we_path, &x, &x);
	gamedata->texture_active_img[3] = mlx_xpm_file_to_image(gamedata->mlx, \
	gamedata->ea_path, &x, &x);
	i = 0;
	while (i < 4)
	{
		gamedata->texture_addr[i] = \
		mlx_get_data_addr(gamedata->texture_active_img[i], \
		&gamedata->texture_bits_per_pixel, &gamedata->texture_length, \
		&gamedata->texture_endian);
		i++;
	}
}

void	init_2dwindow(t_gamedata *gamedata)
{
	gamedata->mapx = get_line_len(gamedata);
	gamedata->mapy = get_height(gamedata);
	gamedata->img2d = mlx_new_image(gamedata->mlx, gamedata->mapx * 16, \
	512);
	gamedata->addr = mlx_get_data_addr(gamedata->img2d, \
	&gamedata->bits_per_pixel, &gamedata->line_length, &gamedata->endian);
}

void	init_3dwindow(t_gamedata *gamedata)
{
	int	mapy;

	if ((gamedata->mapy * 16) > 512)
		mapy = 512 + (gamedata->mapy * 16) - 512 ;
	else
		mapy = 512;

	gamedata->mlx_3dwindow = mlx_new_window(gamedata->mlx, \
	1024 + gamedata->mapx * 16, mapy, "3D");
	gamedata->window_height = 512;
	gamedata->window_width = 1024;
	gamedata->img3dwin = mlx_new_image(gamedata->mlx, gamedata->window_width, \
	gamedata->window_height);
	gamedata->addr3d = mlx_get_data_addr(gamedata->img3dwin, \
	&gamedata->bits_per_pixel3d, &gamedata->line_length3d, &gamedata->endian3d);
}

void	init_floor_ceiling(t_gamedata *gamedata)
{
	gamedata->trgb_floor = create_trgb(0, gamedata->f_color[0], \
	gamedata->f_color[1], gamedata->f_color[2]);
	gamedata->trgb_ceiling = create_trgb(0, gamedata->c_color[0], \
	gamedata->c_color[1], gamedata->c_color[2]);
}

int	main(int argc, char **argv)
{
	t_gamedata	*gamedata;

	gamedata = malloc(sizeof(t_gamedata));
	// if (argc != 2)
	// 	printf("add map \n");
	gamedata->map = ft_calloc(1, sizeof(char *));
	if (!gamedata->map)
		return (0);
	gamedata->map_h = 0;
	gamedata->map_w = 0;
	gamedata->map[0] = NULL;
	gamedata->mlx = mlx_init();
	if (!ft_check_file_extension(argv[1]) || !ft_parse_file(argv[1], gamedata))
	{
		ft_free_cub(gamedata);
		free(gamedata->mlx);
		return (2);
	}
	init_2dwindow(gamedata);
	init_3dwindow(gamedata);
	init_textures(gamedata);
	init_floor_ceiling(gamedata);
	drawMap(gamedata);
	mlx_hook(gamedata->mlx_3dwindow, 2, 1L << 0, key_event, gamedata);
	mlx_hook(gamedata->mlx_3dwindow, 17, 1L << 17, exit_game, gamedata);
	mlx_loop(gamedata->mlx);
	return (0);
}
