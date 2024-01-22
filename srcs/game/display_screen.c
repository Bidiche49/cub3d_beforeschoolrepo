/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:34:56 by ntardy            #+#    #+#             */
/*   Updated: 2024/01/21 19:12:23 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

int	put_wall(t_data *data, int pix_x, int wall_size, t_face face)
{
	t_img	*texture;
	float	texture_y;
	int		texture_coord_x;
	int		texture_coord_y;
	int		coord;

	texture = choice_txt(data->textures, face);
	texture_coord_x = (texture->width + (texture->width
				* (face.start_wall_width - (int)face.start_wall_width)));
	texture_y = 0.0f;
	while (face.wall_start < face.wall_end)
	{
		texture_coord_y = texture_y * texture->height;
		coord = texture_coord_y * texture->size_line + texture_coord_x
			* (texture->bpp / 8);
		put_pixel(data->ptr->img, pix_x, face.wall_start,
			*(int *)(texture->data + coord));
		texture_y += (1.0f - 0.0f) / wall_size;
		++face.wall_start;
	}
	return (wall_size);
}

int	put_face(t_data *data, int pix_x, t_face face)
{
	int	pix_y;
	int	x;

	x = 0;
	while (x <= face.wall_width && pix_x < data->ptr->img->width)
	{
		face.wall_start = data->ptr->img->height / 2
			- calc_wall_height(x, face) / 2;
		face.wall_end = face.wall_start + calc_wall_height(x, face);
		pix_y = 0;
		while (pix_y < data->ptr->img->height)
		{
			if (pix_y < face.wall_start)
				put_color(data, pix_x + x, pix_y, data->textures->ceiling);
			else if (pix_y < face.wall_end)
				pix_y += put_wall(data, pix_x + x,
						calc_wall_height(x, face), face);
			else
				put_color(data, pix_x + x, pix_y, data->textures->floor);
			pix_y++;
		}
		x++;
	}
	return (x);
}

int	compass(t_face *face, t_data *data, t_extra extra)
{
	face->dist = shoot_ray(data, face, extra);
	if (face->pos_wall_x - (int)face->pos_wall_x == 0)
	{
		face->start_wall_width = face->pos_wall_y * -1;
		face->card = EAST;
	}
	else if (face->pos_wall_y < data->player.posy
		&& face->pos_wall_y - (int)face->pos_wall_y > 0.999)
	{
		face->start_wall_width = face->pos_wall_x * -1;
		face->card = NORTH;
	}
	else if (face->pos_wall_y > data->player.posy
		&& face->pos_wall_y - (int)face->pos_wall_y < 0.001)
	{
		face->start_wall_width = face->pos_wall_x;
		face->card = SOUTH;
	}
	else
	{
		face->start_wall_width = face->pos_wall_y;
		face->card = WEST;
	}
	return (0);
}

void	pos_wall(t_face face, t_extra *extra)
{
	extra->pos_wall_y = face.pos_wall_y;
	extra->pos_wall_x = face.pos_wall_x;
}

int	print_face(t_data *data, float *current_angle, t_extra extra, int pix_x)
{
	t_face	face;
	int		iter;

	extra.dir_x = sinf(*current_angle);
	extra.dir_y = cosf(*current_angle);
	iter = compass(&face, data, extra);
	pos_wall(face, &extra);
	face.start_wall_height = data->ptr->img->height / face.dist;
	while (extra.pos_wall_y == face.pos_wall_y && extra.pos_wall_x
		== face.pos_wall_x && iter < data->ptr->img->width)
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
