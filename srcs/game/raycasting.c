/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:58:50 by audrye            #+#    #+#             */
/*   Updated: 2023/12/12 21:44:07 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	int *const	ptr = (int *)img->data; // Cast (char *) to (int *)

	if (x < 0 || y < 0 || x > img->width || y > img->height)
		return ;
	ptr[x + y * (img->size_line / (img->bpp / 8))] = color;
}

void	clear_img(t_img *img, int color)
{
	int	index;

	index = 0;
	while (index < img->width * img->height)
	{
		((int *)img->data)[index] = color;
		++index;
	}
}

void	put_horizontal_line(t_img *img, int y, int color)
{
	int	x;

	x = 0;
	while (x <= img->width)
	{
		put_pixel(img, x, y, color);
		x++;
	}
}

void	put_vertical_line(t_img *img, int x, int color)
{
	int	y;

	y = 0;
	while (y <= img->height)
	{
		put_pixel(img, x, y, color);
		y++;
	}
}

void	put_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	int dx, dy, p, x, y;
	dx=x1-x0;
	dy=y1-y0;
	x=x0;
	y=y0;
	p=2*dy-dx;
	while (x< x1)
	{
		if (p>=0)
		{
			put_pixel(img, x, y, color);
			y=y+1;
			p=p+2*dy-2*dx;
		}
		else
		{
			put_pixel(img, x, y, color);
			p=p+2*dy;
		}
		x=x+1;
	}
}

// void	put_line_touch(t_img *img, int x0, int y0, int x1, int y1, int color)
// {

// }

static void _drawCircle(t_img *img, int xc, int yc, int x, int y, int color)
{
    put_pixel(img, xc+x, yc+y, color);
    put_pixel(img, xc-x, yc+y, color);
    put_pixel(img, xc+x, yc-y, color);
    put_pixel(img, xc-x, yc-y, color);
    put_pixel(img, xc+y, yc+x, color);
    put_pixel(img, xc-y, yc+x, color);
    put_pixel(img, xc+y, yc-x, color);
    put_pixel(img, xc-y, yc-x, color);
}

void	put_circle(t_img *img, int xc, int yc, int r, int color)
{
	int x = 0, y = r;
    int d = 3 - 2 * r;
    _drawCircle(img, xc, yc, x, y, color);
    while (y >= x)
    {
        // for each pixel we will
        // draw all eight pixels

        x++;

        // check for decision parameter
        // and correspondingly
        // update d, x, y
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
    	_drawCircle(img, xc, yc, x, y, color);
    }
}

void	put_grid(t_img *img, int cell_dim, int color)
{
	int	i;

	i = 0;
	while (i < img->width)
	{
		put_vertical_line(img, i, color);
		i += cell_dim;
	}
	i = 0;
	while (i < img->height)
	{
		put_horizontal_line(img, i, color);
		i += cell_dim;
	}
}

float distance_to_next_edge(float posX, float posY, float dirX, float dirY) {
	float const	tx1 = (((int)posX) - 0.000001f - posX) / dirX;
	float const	tx2 = (((int)posX) + 1.000001f - posX) / dirX;
	float const	ty1 = (((int)posY) - 0.000001f - posY) / dirY;
	float const	ty2 = (((int)posY) + 1.000001f - posY) / dirY;

	float tmin = fmax(fmin(tx1, tx2), fmin(ty1, ty2));
	float tmax = fmin(fmax(tx1, tx2), fmax(ty1, ty2));

	if (tmin < 0.0f)
		return (tmax);
	return (tmin);
}

float	shoot_ray(t_data *data, float pos_x, float pos_y, float dir_x, float dir_y)
{
	float		dist;
	float		dist_tot;
	int			iter;

	dist_tot = 0.0f;
	iter = 0;
	while (iter < 20 && data->map[(int)pos_y][(int)pos_x] != '1')
	{
		dist = distance_to_next_edge(pos_x, pos_y, dir_x, dir_y);

		pos_x += dir_x * dist;
		pos_y += dir_y * dist;
		dist_tot += dist;
		++iter;
	}
	// printf("dist_tot = %f\n", dist_tot);
	return (dist_tot);
}

// float	shoot_ray(t_data *data, float pos_x, float pos_y, float dir_x, float dir_y)
// {
// 	int		iterations;

// 	dir_x *= 0.001f;
// 	dir_y *= 0.001f;
// 	iterations = 0;
// 	while (iterations < 100000)
// 	{
// 		pos_x += dir_x;
// 		pos_y += dir_y;
// 		if (data->map[(int)pos_y][(int)pos_x] == '1')
// 			return (iterations * 0.001f);
// 		++iterations;
// 	}
// 	return (iterations * 0.001f);
// }

int put_wall(t_data *data, int pix_x, int wall_start, int wall_end, int wall_size)
{
	t_img *current_texture = data->textures->we_img;  // Utilisez la texture que vous souhaitez afficher

    float texture_x = ((float)pix_x / (float)data->ptr->img->width);  // Normalisez la position x de la texture
    int texture_coord_x = texture_x * current_texture->width;

    float texture_y_start = 0.0f;
    float texture_y_end = 1.0f;

    float texture_y_step = (texture_y_end - texture_y_start) / wall_size;

    float current_texture_y = texture_y_start;

    while (wall_start < wall_end)
    {
        int texture_coord_y = current_texture_y * current_texture->height;

        int coord = texture_coord_y * current_texture->size_line + texture_coord_x * (current_texture->bpp / 8);

        int const r = current_texture->data[coord];
        int const g = current_texture->data[coord + 1];
        int const b = current_texture->data[coord + 2];

        put_pixel(data->ptr->img, pix_x, wall_start, (r << 16) | (g << 8) | b);

        current_texture_y += texture_y_step;
        ++wall_start;
    }
	return (wall_size);
}

// int put_wall(t_data *data, int pix_x, int wall_start, int wall_end, int wall_size)
// {
//     while (wall_start < wall_end)
//     {
//         float texture_y = ((float)(wall_start - wall_start) / (float)wall_size); // Normalisez la position y de la texture
//         int texture_coord_y = texture_y * (data->textures->we_img->height);

//         int coord = texture_coord_y * data->textures->we_img->size_line + pix_x * (data->textures->we_img->bpp / 8);

//         int const r = data->textures->we_img->data[coord];
//         int const g = data->textures->we_img->data[coord + 1];
//         int const b = data->textures->we_img->data[coord + 2];

//         put_pixel(data->ptr->img, pix_x, wall_start, (r << 16) | (g << 8) | b);
//         ++wall_start;
//     }
//     return wall_size;
// }

// void	put_wall(t_data *data, int pix_x, int pix_y, float dist)
// {
// 	float const	rdist = fmax(dist, 1.f);
// 	int const	r = 0xc7 / rdist;
// 	int const	g = 0x64 / rdist;
// 	int const	b = 0x64 / rdist;
// 	// t_img *img = data->textures->so_img;
// 	// int	coord = pix_y * data->textures->we_img->size_line + pix_x * (data->textures->we_img->bpp / 8);

// 	// int const	r = data->textures->we_img->data[coord];
// 	// int const	g = data->textures->we_img->data[coord + 1];
// 	// int const	b = data->textures->we_img->data[coord + 2];

// 	put_pixel(data->ptr->img, pix_x, pix_y, (r << 16) | (g << 8) | b);
// }

void	put_color(t_data *data, int pix_x, int pix_y, t_color *color)
{
	put_pixel(data->ptr->img, pix_x, pix_y, ((int)(color->r) << 16) | ((int)(color->g) << 8) | (int)(color->b));
}

void	put_slice(t_data *data, int pix_x, float dist)
{
	int	pix_y;
	int	wall_size = data->ptr->img->height / dist;
	int	wall_start = data->ptr->img->height / 2 - wall_size / 2;
	int	wall_end = wall_start + wall_size;


	pix_y = 0;
	while (pix_y < data->ptr->img->height)
	{
		if (pix_y < wall_start)
			put_color(data, pix_x, pix_y, data->textures->ceiling);
		else if (pix_y < wall_end)
			pix_y += put_wall(data, pix_x, wall_start, wall_end, wall_size);
		else
			put_color(data, pix_x, pix_y, data->textures->floor);
		++pix_y;
	}
}

void	plage_shoot(t_data *data, float pos_x, float pos_y, float rot)
{
	int		pix_x;
	float	start_rot;
	float	off_rot;
	float	dir_x;
	float	dir_y;

	start_rot = rot - 0.15f * M_PI;
	off_rot = (0.3f * M_PI) / data->ptr->img->width;
	pix_x = 0;
	while (pix_x < data->ptr->img->width)
	{
		start_rot = start_rot + off_rot;
		dir_x = sinf(start_rot);
		dir_y = cosf(start_rot);
		put_slice(data, pix_x, shoot_ray(data, pos_x, pos_y, dir_x, dir_y));
		++pix_x;
	}
}

// void	put_blocks(t_data *data, int cell_dim, int color)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (data->map[y])
// 	{
// 		x = 0;
// 		while (data->map[y][x])
// 		{
// 			if (data->map[y][x] == '1')
// 				put_circle(data->ptr->img, x * cell_dim + cell_dim / 2, y * cell_dim + cell_dim / 2, cell_dim / 2, color);
// 			++x;
// 		}
// 		++y;
// 	}
// }

void	print_column(t_data *data)
{
	float const	posx = data->player.posX; // data->player.pos_x
	float const	posy = data->player.posY;
	// float const	dir_x = sinf(rot);
	// float const	dir_y = cosf(rot);
	// int const	cell_size = 14;
	// prendre sa position dans la map dans

	clear_img(data->ptr->img, 0x040014);
	// put_grid(data->ptr->img, cell_size, 0x71758A);
	// put_blocks(data, cell_size, 0xF800E5);
	 // utilister la position du joueur par rapport a sa position dans la map
	// put_circle(data->ptr->img, posx * cell_size,posy * cell_size, 10, 0x64c700);
	// shoot_ray(data, posx, posy, dir_x, dir_y, cell_size);
	plage_shoot(data, posx, posy, data->player.dir);
}
