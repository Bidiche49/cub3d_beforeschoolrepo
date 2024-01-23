/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_screen_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:32:13 by ntardy            #+#    #+#             */
/*   Updated: 2024/01/23 21:29:26 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

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

t_img	*choice_normal_texture(t_img *texture
, t_textures *textures, t_face face)
{
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
	if (face.is_door == 1)
		texture = textures->door_img;
	else if (face.card == NORTH)
	{
		if (data->cycles_since_last_switch <= 250)
			texture = textures->nos_img;
		else
			texture = textures->no_img;
	}
	else
		texture = choice_normal_texture(texture, textures, face);
	return (texture);
}

void	horizontal_compass(t_face *face, t_data *data)
{
	if (face->pos_wall_y > data->player.posy
		&& face->pos_wall_y - (int)face->pos_wall_y < 0.001)
	{
		face->start_wall_width = face->pos_wall_x;
		if (face->is_door == 0)
			face->card = SOUTH;
	}
	else
	{
		face->start_wall_width = face->pos_wall_y;
		if (face->is_door == 0)
			face->card = WEST;
	}
}
