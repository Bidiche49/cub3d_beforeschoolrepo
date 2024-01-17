/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:58:50 by audrye            #+#    #+#             */
/*   Updated: 2024/01/17 20:12:55 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	int *const	ptr = (int *)img->data;

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

float shoot_ray(t_data *data, float pos_x, float pos_y, float dir_x, float dir_y, t_face *face, float deviation_angle)
{
	float dist_tot = 0.0f;
	int iter = 0;
	while (iter < 20 && data->map[(int)pos_y][(int)pos_x] != '1') {
		float dist = distance_to_next_edge(pos_x, pos_y, dir_x, dir_y);
		pos_x += dir_x * dist;
		pos_y += dir_y * dist;
		dist_tot += dist;
		++iter;
	}
	face->pos_wall_x = pos_x;
	face->pos_wall_y = pos_y;

	return (dist_tot * cosf(deviation_angle));
}


int put_wall(t_data *data, int pix_x, int wall_start, int wall_end, int wall_size, t_face face)
{
	t_img *texture = data->textures->we_img;
	int texture_coord_x;
	float texture_y;
	int texture_coord_y;
	int coord;

	texture_coord_x = (texture->width + (texture->width * (face.start_wall_width - (int)face.start_wall_width)));
	texture_y = 0.0f;
	while (wall_start < wall_end)
	{
		texture_coord_y = texture_y * texture->height;
		coord = texture_coord_y * texture->size_line + texture_coord_x * (texture->bpp / 8);
		put_pixel(data->ptr->img, pix_x, wall_start, (texture->data[coord] << 16) |
			(texture->data[coord + 1] << 8) |
			texture->data[coord + 2]);
		texture_y += (1.0f - 0.0f) / wall_size;
		++wall_start;
	}
	return (wall_size);
}


void	put_color(t_data *data, int pix_x, int pix_y, t_color *color)
{
	put_pixel(data->ptr->img, pix_x, pix_y, ((int)(color->r) << 16) | ((int)(color->g) << 8) | (int)(color->b));
}

int	calc_wall_height(int x, t_face face)
{
	int	hp;

	if (x == 0)
		return (face.start_wall_height);
	if (x == face.wall_width)
		return (face.end_wall_height);
	hp = face.start_wall_height + (((face.end_wall_height - face.start_wall_height) * x) / face.wall_width);
	return (hp);
}

int	put_face(t_data *data, int pix_x, t_face face)
{
	int	pix_y;
	int	x;
	int	wall_start;
	int	wall_end;

	x = 0;
	while (x <= face.wall_width && pix_x < data->ptr->img->width)
	{
		wall_start = data->ptr->img->height / 2 - calc_wall_height(x, face) / 2;
		wall_end = wall_start + calc_wall_height(x, face);
		pix_y = 0;
		while (pix_y < data->ptr->img->height)
		{
			if (pix_y < wall_start)
				put_color(data, pix_x + x, pix_y, data->textures->ceiling);
			else if (pix_y < wall_end)
				pix_y += put_wall(data, pix_x + x, wall_start, wall_end, calc_wall_height(x, face), face);
			else
				put_color(data, pix_x + x, pix_y, data->textures->floor);
			pix_y++;
		}
		x++;
	}
	return (x);
}

int print_face(t_data *data, float pos_x, float pos_y, float *start_rot, float off_rot, int pix_x, float deviation_angle)
{
	t_face	face;
	float	pos_wall_x;
	float	pos_wall_y;
	int		iter;
	float	dir_x;
	float	dir_y;

	(void)dir_x;
	(void)dir_y;
	face.dist = shoot_ray(data, pos_x, pos_y, sinf(*start_rot), cosf(*start_rot), &face, deviation_angle);
	pos_wall_y = face.pos_wall_y;
	pos_wall_x = face.pos_wall_x;
	iter = 0;
	if (face.pos_wall_x - (int)face.pos_wall_x == 0)//East
		face.start_wall_width = face.pos_wall_y * -1;
	else if (face.pos_wall_y < data->player.posY && face.pos_wall_y - (int)face.pos_wall_y > 0.999)//North
		face.start_wall_width = face.pos_wall_x * -1;
	else if (face.pos_wall_y > data->player.posY && face.pos_wall_y - (int)face.pos_wall_y < 0.001)//South
		face.start_wall_width = face.pos_wall_x;
	else//West
		face.start_wall_width = face.pos_wall_y;
	face.start_wall_height = data->ptr->img->height / face.dist;
	while (pos_wall_y == face.pos_wall_y && pos_wall_x == face.pos_wall_x && iter < data->ptr->img->width)
	{
		*start_rot = *start_rot + off_rot;
		dir_x = sinf(*start_rot);
		dir_y = cosf(*start_rot);
		face.old_dist = face.dist;
		 face.dist = shoot_ray(data, pos_x, pos_y, sinf(*start_rot), cosf(*start_rot), &face, deviation_angle);
		if (pos_wall_x == 0 && pos_wall_y == 0)
		{
			pos_wall_x = face.pos_wall_x;
			pos_wall_y = face.pos_wall_y;
		}
		iter++;
	}
	face.end_wall_width = face.pos_wall_x;
	face.end_wall_height = data->ptr->img->height / face.old_dist;
	face.wall_width = iter -1;

	return (put_face(data, pix_x, face));
}


void	plage_shoot(t_data *data, float pos_x, float pos_y, float rot) {
	int pix_x = 0;
	float start_rot = rot - 0.15f * M_PI;
	float off_rot = (0.3f * M_PI) / data->ptr->img->width;

	while (pix_x < data->ptr->img->width) {
		float current_angle = start_rot + pix_x * off_rot;
		float deviation_angle = fabs(rot - current_angle);
		pix_x += print_face(data, pos_x, pos_y, &current_angle, off_rot, pix_x, deviation_angle);
	}
}

void	print_column(t_data *data)
{
	float const	posx = data->player.posX;
	float const	posy = data->player.posY;

	clear_img(data->ptr->img, 0x040014);
	plage_shoot(data, posx, posy, data->player.dir);
}
