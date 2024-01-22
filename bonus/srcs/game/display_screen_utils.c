/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_screen_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:32:13 by ntardy            #+#    #+#             */
/*   Updated: 2024/01/22 20:43:14 by ntardy           ###   ########.fr       */
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

void	put_color(t_data *data, int pix_x, int pix_y, t_color *color)
{
	put_pixel(data->ptr->img, pix_x, pix_y, ((int)(color->r) << 16)
		| ((int)(color->g) << 8) | (int)(color->b));
}

int	calc_wall_height(int x, t_face face)
{
	int	hp;

	if (x == 0)
		return (face.start_wall_height);
	if (x == face.wall_width)
		return (face.end_wall_height);
	hp = face.start_wall_height + (((face.end_wall_height
					- face.start_wall_height) * x) / face.wall_width);
	return (hp);
}

t_img	*choice_normal_texture(t_img *texture, t_textures *textures, t_face face)
{
	// if (face.card == NORTH)
	// 	texture = textures->no_img;
	if (face.card == SOUTH)
		texture = textures->so_img;
	if (face.card == EAST)
		texture = textures->ea_img;
	if (face.card == WEST)
		texture = textures->we_img;
	return (texture);
}

t_img	*choice_txt(t_textures *textures, t_face face)
{
	t_img	*texture;
	t_data	*data;

	texture = NULL;
	data = *get_data();
	if (face.card == NORTH) {
		if (data->cycles_since_last_switch <= 250)
			texture = textures->nos_img;
		else
			texture = textures->no_img;
	}
	else
		texture = choice_normal_texture(texture, textures, face);
	return (texture);
}
