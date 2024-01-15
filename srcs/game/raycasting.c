/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:58:50 by audrye            #+#    #+#             */
/*   Updated: 2024/01/14 18:46:10 by audrye           ###   ########.fr       */
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

float distance_to_next_edge(float posX, float posY, float dirX, float dirY)
{
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

float	shoot_ray(t_data *data, float pos_x, float pos_y, float dir_x, float dir_y) // avec cette fonction on n'as la taille du cube
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
	return (dist_tot);
}

// int	print_wall_column(t_data *data, int pix_x, int wall_start, int wall_end, int wall_size)
// {
// 	t_img	*texture;
// 	t_cube	*cube;

// 	texture = data->textures->we_img;
// 	while (wall_start < wall_end)
// 	{

// 	}
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
		if (pix_x >= 0 && pix_x < data->ptr->img->width && wall_start >= 0 && wall_start < data->ptr->img->height)
        {
            int texture_coord_y = current_texture_y * current_texture->height;

            int coord = texture_coord_y * current_texture->size_line + texture_coord_x * (current_texture->bpp / 8);

            int const r = current_texture->data[coord];
            int const g = current_texture->data[coord + 1];
            int const b = current_texture->data[coord + 2];
            put_pixel(data->ptr->img, pix_x, wall_start, (r << 16) | (g << 8) | b);
		}
        current_texture_y += texture_y_step;
        ++wall_start;
    }
	return (wall_size);
}

void	print_color(t_data *data, int pix_x, int pix_y, t_color *color)
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
			print_color(data, pix_x, pix_y, data->textures->ceiling);
		else if (pix_y < wall_end)
			pix_y += put_wall(data, pix_x, wall_start, wall_end, wall_size);
		else
			print_color(data, pix_x, pix_y, data->textures->floor);
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

void	print_column(t_data *data)
{
	float const	posx = data->player.posX;
	float const	posy = data->player.posY;

	clear_img(data->ptr->img, 0x040014);
	plage_shoot(data, posx, posy, data->player.dir);
}
