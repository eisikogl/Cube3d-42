/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calion <calion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:42:20 by eisikogl          #+#    #+#             */
/*   Updated: 2022/11/17 07:48:14 by calion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include "../assets/bricksx64.ppm"

// The map must be composed of only 6 possible characters: 0 for an empty space
// 1 for a wall, and N,S,E or W for the player’s start position and spawning
// orientation.


void	my_mlx_pixel_put(t_gamedata *gamedata, int x, int y, int color)
{
	char	*dst;

	dst = gamedata->addr + (y * gamedata->line_length + x * (gamedata->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put3d(t_gamedata *gamedata, int x, int y, int color)
{
	char	*dst3d;

	dst3d = gamedata->addr3d + (y * gamedata->line_length3d + x * (gamedata->bits_per_pixel3d / 8));
	*(unsigned int*)dst3d = color;
}


void drawLine(t_gamedata *gamedata, int beginX, int beginY,int endX,int endY,int color)
{
    float deltaX = endX - beginX;
    float deltaY = endY - beginY;

    int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

    deltaX /= pixels; // 1
    deltaY /= pixels; // 0
    double pixelX = beginX;
    double pixelY = beginY;
    while (pixels)
    {
		if(pixelX < gamedata->mapX * 16 && pixelY < gamedata->mapY*16 && pixelX>0 && pixelY>0)
		{
			my_mlx_pixel_put(gamedata, pixelX, pixelY, color);
			pixelX += deltaX;
			pixelY += deltaY;
		}
		--pixels;
    }
}

void drawLine3d(t_gamedata *gamedata, int beginX, int beginY,int endX,int endY,int color)
{
    float deltaX = endX - beginX;
    float deltaY = endY - beginY;

    int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

    deltaX /= pixels; // 1
    deltaY /= pixels; // 0
    double pixelX = beginX;
    double pixelY = beginY;
    while (pixels)
    {
		
		my_mlx_pixel_put3d(gamedata, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
    }
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void drawLine3d_texture(t_gamedata *gamedata, float beginX, float beginY,float shade,float texture_x,float lineHeight)
{
	int y=0;
	int color;
	float texture_step = 64.0 / (float)lineHeight;
	float texture_offset = 0;
	if(lineHeight > 512)
	{
		texture_offset = (lineHeight - 512)/2.0;
		lineHeight = 512;
	}
	float WallOffsetY = 256-lineHeight/2;
	float texture_y = texture_offset * texture_step;
	
    while(y<lineHeight)
    {
		float r = brick_wall[(int)(texture_y)*64*3+(int)(texture_x)*3];
        float g = brick_wall[(int)(texture_y)*64*3+1+(int)(texture_x)*3+1];
        float b = brick_wall[(int)(texture_y)*64*3+2+(int)(texture_x)*3+2];
		//printf("%f\n",c);
        // if(c == 1.0)
		//     color = create_trgb(0,100*shade,255*shade,255*shade);
        // if(c == 0)
		//     color = create_trgb(0,0,0,0);
        color = create_trgb(0,r*shade,g*shade,b*shade);
		my_mlx_pixel_put3d(gamedata, beginX, y+WallOffsetY, color);
		texture_y += texture_step;
		y++;
    }
}

float dist(float beginX,float beginY,float endX,float endY,float angle)
{
	float deltaX = endX - beginX;
    float deltaY = endY - beginY;
	return sqrt((deltaX  * deltaX) + (deltaY * deltaY));
}

int render_rect(t_gamedata *gamedata,int x,int y)
{
	int	i;
	int j;

	i = y;
	while (i < y + 16)
	{
		j = x;
		while (j < x + 16)
		{
			my_mlx_pixel_put(gamedata, j++, i, 0x00000000);
		}
		++i;
	}
	i = y+1;
	while (i < y + 15)
	{
		j = x+1;
		while (j < x + 15)
		{
			my_mlx_pixel_put(gamedata, j++, i, 0x00FF0000);
		}
		++i;
	}
	return (0);
}


void DrawCube(t_gamedata *gamedata,float beginX,float beginY,float endX,float endY,int color,int cubewith)
{    
    int j;
    int i = 0;
    /*player rectangle*/
    while (i < endY + cubewith)
	{
		j = 0;
		while (j < endX)
        {
			mlx_pixel_put(gamedata->mlx,gamedata->mlx_3dwindow, beginX + j, beginY + i, color);
            j++;
        }
		++i;
	}
   
}



void	render_floor(t_gamedata *gamedata, int color)
{
	int	i;
	int	j;

	i = gamedata->window_height / 2;
	while (i < gamedata->window_height)
	{
		j = 0;
		while (j < gamedata->window_width)
		{
			my_mlx_pixel_put3d(gamedata, j++, i, color);
		}
		++i;
	}
}

void	render_ceiling(t_gamedata *gamedata, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < gamedata->window_height / 2)
	{
		j = 0;
		while (j < gamedata->window_width)
		{
			my_mlx_pixel_put3d(gamedata, j++, i, color);
		}
		++i;
	}
}

void	render_bg_map(t_gamedata *gamedata, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < gamedata->mapY*16)
	{
		j = 0;
		while (j < gamedata->mapX*16)
		{
			my_mlx_pixel_put(gamedata, j++, i, color);
		}
		++i;
	}
}

void drawRays(t_gamedata *gamedata)
{
    int r,map_x,map_y,map_pos,dof;
    float ray_x,ray_y,ray_angle,x_offset,y_offset,distT;
    //ray_x = ray_y / tan(ray_angle);
    //ray_y = ((map_height * 16) - player_y) / 16;
    //S(int)playery
	mlx_clear_window(gamedata->mlx,gamedata->mlx_3dwindow);
    float texture_y=0;
    r = 0;
    ray_angle = gamedata->player_angle - Dgre*30 ;
	if(ray_angle <0)
	{
		ray_angle += 2*PI;
	}
	if(ray_angle > 2*PI)
	{
		ray_angle -= 2*PI;
	}
    int raysize = 8192;
	while(r<raysize)
	{
        dof = 0;
		/*find shortest line*/
		float distHori = 1000000,horiX= gamedata->player_x,horiY = gamedata->player_y;
   		/*Horizontal Line check*/
        float aTan = tan(ray_angle);
        if(ray_angle < PI) // looking up quadrant 2
        {
           ray_y = ((int)(gamedata->player_y / 16) * 16) - 0.0001 ;
           ray_x = ((gamedata->player_y - ray_y) / aTan) + gamedata->player_x;
           y_offset = -16;
           x_offset = -(y_offset / aTan);
        }
        if(ray_angle > PI) //looking down quadrant 3
        {
            ray_y = ((int)(gamedata->player_y / 16) * 16) + 16;
            ray_x = ((gamedata->player_y - ray_y) / aTan) + gamedata->player_x;
            y_offset = 16;
            x_offset = -(y_offset / aTan);
        }

        if(ray_angle == 0 || ray_angle == PI )
        {
            ray_x = gamedata->player_x;
            ray_y = gamedata->player_y;
            dof = gamedata->mapY;
        }
        while(dof < gamedata->mapY)
        {
            /*find position in array*/
             map_x = ((int)(ray_x) / 16);
             map_y = ((int)(ray_y) / 16);
            //  printf("im map_X : %d \n",map_x);
            //  printf("im map_Y : %d \n",map_y);
            // map_pos = map_y * gamedata->mapX + map_x;

            if(map_x < gamedata->mapX && map_y < gamedata->mapY && map_x >= 0 && map_y >= 0 && gamedata->map_split[map_y][map_x] == '1')
            {
				horiX = ray_x;
				horiY = ray_y;
				distHori = dist(gamedata->player_x,gamedata->player_y,horiX,horiY,ray_angle);
                dof = gamedata->mapY;
            }
            else
            {
                ray_x += x_offset;
                ray_y += y_offset;
            	dof += 1;
            }
       }
	//    drawLine(gamedata,gamedata->player_x + 2,gamedata->player_y+2,
    //    ray_x ,ray_y,0x0000FF00);

    /*Vertical Line check*/
    
        dof = 0;
		float distVerti= 1000000,vertiX= gamedata->player_x,vertiY = gamedata->player_y;
        float nTan = tan(ray_angle);
        if(ray_angle > P2 && ray_angle < P3) // looking left
        {
            ray_x = (((int)gamedata->player_x/16) * 16) - 0.0001;
            ray_y = (gamedata->player_x - ray_x) * nTan + gamedata->player_y;
            x_offset = -16;
            y_offset = -x_offset * nTan;
        }
        if(ray_angle < P2 || ray_angle > P3) //looking right
        {
            ray_x = (((int)gamedata->player_x / 16) * 16)+16;
            ray_y = (gamedata->player_x - ray_x) * nTan + gamedata->player_y;
            x_offset = 16;
            y_offset = -x_offset * nTan;
        }
  		if(ray_angle == 0 || ray_angle == PI)
        {
            ray_x = gamedata->player_x;
            ray_y = gamedata->player_y;
            dof = gamedata->mapX;
        }

        while(dof < gamedata->mapX)
        {
            /*find position in array*/
             map_x = (int)(ray_x) / 16;
             map_y = (int)(ray_y) / 16;
            //  printf("im map_X : %d \n",map_x);
            //  printf("im map_Y : %d \n",map_y);
            // map_pos = map_y * gamedata->mapX + map_x;

            if(map_x < gamedata->mapX && map_y < gamedata->mapY && map_x >= 0 && map_y >= 0 && gamedata->map_split[map_y][map_x] == '1')
            {
				vertiX = ray_x;
				vertiY = ray_y;
				distVerti = dist(gamedata->player_x,gamedata->player_y,vertiX,vertiY,ray_angle);
				dof = gamedata->mapX;
            }
            else 
            {
                ray_x += x_offset;
                ray_y += y_offset;
            	dof += 1;
            }
       }
	   int color;
	   float shade = 1;
		if(distVerti < distHori)
		{
			ray_x = vertiX;
			ray_y = vertiY;
			distT = distVerti;
			shade = 0.5;
		}
		if(distHori < distVerti)
		{
			ray_x = horiX;
			ray_y = horiY;
			distT = distHori;
			shade = 1;
		}
        drawLine(gamedata,gamedata->player_x + 2,gamedata->player_y+2,
        ray_x ,ray_y,0x0000FF00);

      

	/*3d SCENE*/
	float ca = gamedata->player_angle - ray_angle;
	if(ca < 0)
	{
		ca += 2*PI;
	}
	if(ca > 2*PI)
	{
		ca-=2*PI;
	}
	distT = distT*cos(ca);
	int mapsize = gamedata->mapY * gamedata->mapY;
	float lineHeight = (16 * 512) / distT;
	float WallOffsetY = 256-lineHeight/2;
	float WallOffsetX = 1024/2;
    float sceensize = 1024 / raysize;
	float texture_x;
	if(shade == 1)
	{
		/*south*/
		texture_x = (int)(ray_x*2.0) % 64;
		/*north*/
		if(ray_angle>180)
		{
			texture_x = 63-texture_x;
		}
	}
	else
	{
		
		/*east*/
		texture_x = (int)(ray_y*2.0) % 64;
		/*west*/
		if(ray_angle>90 && ray_angle < 270)
		{
			texture_x = 63-texture_x;
		}
	}

	
    drawLine3d_texture(gamedata,r/8,WallOffsetY,shade,texture_x,lineHeight);

	
	ray_angle += Dgre / 136 ;
	if(ray_angle < 0)
	{
		ray_angle += 2*PI;
	}
	if(ray_angle > 2*PI)
	{
		ray_angle -= 2*PI;
	}
	r++;
	}
}


void pixelPlayer(t_gamedata *gamedata)
{    
    int rectheigt = 5;
    int rectwidth = 5; // odd numbers so arm is in middle;
    int j;
    int i = 0;
    /*player rectangle*/
    while (i < rectheigt)
    {
        j = 0;
        while (j < rectwidth)
        {
            my_mlx_pixel_put(gamedata, gamedata->player_x + j, gamedata->player_y + i, 0xFFFFFF00);
            j++;
        }
        ++i;
    }
    /*player arm*/
    //printf("im rayangle: %f \n",gamedata->player_angle);
    //printf("im player_y = %d \n",(int)(gamedata->player_y / 16) * 16);
    drawRays(gamedata);
    drawLine(gamedata,gamedata->player_x + 2,gamedata->player_y + 2,
    (gamedata->player_x + 2) - 2 * -gamedata->player_dx, (gamedata->player_y + 2) - 2 * gamedata->player_dy,0x00FF0000);
    // mlx_pixel_put(gamedata->mlx, gamedata->mlx_window, gamedata->player_x + j, gamedata->player_y + i, 0x00FF0000);

}


void init(t_gamedata *gamedata)
{
    //char	*path_player;
   // char	*path_wall;
    int x = 16;
    int y = 16;

	//path_wall = "./assets/wall.xpm";
	//path_player = "./assets/player.xpm";

    gamedata->img_wall = mlx_xpm_file_to_image(gamedata->mlx, "./assets/wall.xpm", &x, &y);
   // gamedata->img_player = mlx_xpm_file_to_image(gamedata->mlx, path_player, &x, &y);
}

// void drawPlayer(t_gamedata *gamedata)
// {
//     mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, gamedata->img_player,
//     gamedata->player_x, gamedata->player_y);
// }

void drawWall(t_gamedata *gamedata,int i,int j)
{
    mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, gamedata->img_wall,
    i, j );
}

void drawMap(t_gamedata *call_map)
{
    int i;
    int j;

    int x;
    int y = 0;
    
    i = 0;
	render_floor(call_map,call_map->trgb_floor);
	render_ceiling(call_map,call_map->trgb_ceiling);
	render_bg_map(call_map,call_map->trgb_floor);
    while(call_map->map_split[i] != NULL)
    {
        j = 0;
        x = 0;
        while(call_map->map_split[i][j] != '\0' && '\n')
        {
            if(call_map->map_split[i][j] == '1')
            {
                render_rect(call_map,x,y);
            }
            if(call_map->map_split[i][j] == 'N')
            {
                
                call_map->player_x = x;
                call_map->player_y = y;
                call_map->player_angle = PI / 2;
                call_map->player_dx = cos(call_map->player_angle) * 5;
			    call_map->player_dy = sin(call_map->player_angle) * 5;
                pixelPlayer(call_map);
            }

            x += 16;
            j++;
        }
        y += 16;
        i++;
    }
    mlx_put_image_to_window(call_map->mlx, call_map->mlx_window, call_map->img2d, 0, 0); // where to put image solve
	mlx_put_image_to_window(call_map->mlx, call_map->mlx_3dwindow, call_map->img3dwin, 0, 0);
}

void drawMap2(t_gamedata *call_map)
{
    int i;
    int j;

    int x;
    int y = 0;
    
    i = 0;
    //drawWall(call_map,x,y);
    call_map->img2d = mlx_new_image(call_map->mlx,call_map->mapX*16,call_map->mapY*16);
	call_map->img3dwin = mlx_new_image(call_map->mlx,1024,512);
	render_floor(call_map,call_map->trgb_floor);
	render_ceiling(call_map,call_map->trgb_ceiling);
	render_bg_map(call_map,call_map->trgb_floor);
    while(call_map->map_split[i] != NULL)
    {
        j = 0;
        x = 0;
        while(call_map->map_split[i][j] != '\0')
        {
            if(call_map->map_split[i][j] == '1')
            {
               render_rect(call_map,x,y);
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
   mlx_put_image_to_window(call_map->mlx, call_map->mlx_window, call_map->img2d, 0, 0); // where to put image solve
   mlx_put_image_to_window(call_map->mlx, call_map->mlx_3dwindow, call_map->img3dwin, 0, 0);
}

void init_textures(t_gamedata *gamedata)
{
    int x = 64;
    gamedata->north_texture = mlx_xpm_file_to_image(gamedata->mlx,gamedata->north_texture_path,&x,&x);
    gamedata->north_addr = mlx_get_data_addr(gamedata->north_texture, &gamedata->north_bits_per_pixel, &gamedata->north_line_length,
								&gamedata->north_endian);
}

int main(int argc,char **argv)
{
   // t_gamedata  *call_map;
    t_gamedata  *gamedata;

    gamedata = malloc(sizeof(t_gamedata));
    if(argc != 2)
        printf("add map \n");
    gamedata->mlx = mlx_init();
    gamedata->map_path = argv[1];
    read_map(gamedata);
    gamedata->map_split = ft_split(gamedata->map,'\n');
    gamedata->mapX = get_line_len(gamedata);
    gamedata->mapY = get_height(gamedata);
    gamedata->mlx_window = mlx_new_window(gamedata->mlx,16*  gamedata->mapX, 16 * gamedata->mapY,"Hello World");
    gamedata->img2d = mlx_new_image(gamedata->mlx,gamedata->mapX*16,gamedata->mapY*16);
	gamedata->mlx_3dwindow = mlx_new_window(gamedata->mlx,1024, 512,"Hello World");
	gamedata->window_height = 512;
	gamedata->window_width = 1024;
    gamedata->img3dwin = mlx_new_image(gamedata->mlx,gamedata->window_width,gamedata->window_height);
    gamedata->addr = mlx_get_data_addr(gamedata->img2d, &gamedata->bits_per_pixel, &gamedata->line_length,
								&gamedata->endian);
    
     gamedata->addr3d = mlx_get_data_addr(gamedata->img3dwin, &gamedata->bits_per_pixel3d, &gamedata->line_length3d,
								&gamedata->endian3d);
	gamedata->trgb_floor = create_trgb(0,gamedata->floor_color[0],gamedata->floor_color[1],gamedata->floor_color[2]);
	gamedata->trgb_ceiling = create_trgb(0,gamedata->ceiling_color[0],gamedata->ceiling_color[1],gamedata->ceiling_color[2]);
	//mlx_new_image(gamedata->mlx,16*  gamedata->mapX, 16 * gamedata->mapY);
   // init(gamedata);
    drawMap(gamedata);
   
    mlx_hook(gamedata->mlx_window, 2, 1L << 0, key_event, gamedata);
	//mlx_hook(gamedata.mlx_window, 17, 1L << 17, exit_game, &gamedata);
	mlx_loop(gamedata->mlx);
    return 0;
}

//Map Error Handling
//Readmap put into struct
//Raytracing