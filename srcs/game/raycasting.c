/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:58:50 by audrye            #+#    #+#             */
/*   Updated: 2024/01/17 21:00:49 by ntardy           ###   ########.fr       */
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

float shoot_ray(t_data *data, t_face *face, t_extra extra)
{
	float pos_x;
	float pos_y;
	float dist_tot = 0.0f;
	int iter = 0;

	pos_x = data->player.posX;
	pos_y = data->player.posY;
	while (iter < 20 && data->map[(int)pos_y][(int)pos_x] != '1') {
		float dist = distance_to_next_edge(pos_x, pos_y, extra.dir_x, extra.dir_y);
		pos_x += extra.dir_x * dist;
		pos_y += extra.dir_y * dist;
		dist_tot += dist;
		++iter;
	}
	face->pos_wall_x = pos_x;
	face->pos_wall_y = pos_y;

	return (dist_tot * cosf(extra.deviation_angle));
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

int compass(t_face *face, t_data *data, t_extra extra)
{

	face->dist = shoot_ray(data, face, extra);
	if (face->pos_wall_x - (int)face->pos_wall_x == 0)//East
		face->start_wall_width = face->pos_wall_y * -1;
	else if (face->pos_wall_y < data->player.posY && face->pos_wall_y - (int)face->pos_wall_y > 0.999)//North
		face->start_wall_width = face->pos_wall_x * -1;
	else if (face->pos_wall_y > data->player.posY && face->pos_wall_y - (int)face->pos_wall_y < 0.001)//South
		face->start_wall_width = face->pos_wall_x;
	else//West
		face->start_wall_width = face->pos_wall_y;
	return (0);
}

void pos_wall(t_face face, t_extra *extra)
{
	extra->pos_wall_y = face.pos_wall_y;
	extra->pos_wall_x = face.pos_wall_x;
}

int print_face(t_data *data, float *current_angle, t_extra extra, int pix_x)
{
	t_face	face;
	int		iter;

	extra.dir_x = sinf(*current_angle);
	extra.dir_y = cosf(*current_angle);
	iter = compass(&face, data, extra);
	pos_wall(face, &extra);
	face.start_wall_height = data->ptr->img->height / face.dist;
	while (extra.pos_wall_y == face.pos_wall_y && extra.pos_wall_x == face.pos_wall_x && iter < data->ptr->img->width)
	{
		*current_angle = *current_angle + extra.off_rot;
		extra.dir_x = sinf(*current_angle);
		extra.dir_y = cosf(*current_angle);
		face.old_dist = face.dist;
		face.dist = shoot_ray(data, &face, extra);
		if (extra.pos_wall_x == 0 && extra.pos_wall_y == 0)
			pos_wall(face, &extra);
		iter++;
	}
	face.end_wall_height = data->ptr->img->height / face.old_dist;
	face.wall_width = iter -1;
	return (put_face(data, pix_x, face));
}


void	plage_shoot(t_data *data, float rot) {
	t_extra extra;
	int pix_x = 0;
	extra.start_rot = rot - 0.15f * M_PI;
	extra.off_rot = (0.3f * M_PI) / data->ptr->img->width;

	while (pix_x < data->ptr->img->width) {
		extra.current_angle = extra.start_rot + pix_x * extra.off_rot;
		extra.deviation_angle = fabs(rot - extra.current_angle);
		pix_x += print_face(data, &extra.current_angle, extra, pix_x);
	}
}

void	print_column(t_data *data)
{
	clear_img(data->ptr->img, 0x040014);
	plage_shoot(data, data->player.dir);
}
