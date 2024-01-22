/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:58:50 by audrye            #+#    #+#             */
/*   Updated: 2024/01/21 19:12:23 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

float	distance_to_next_edge(float posX, float posY, float dirX, float dirY)
{
	float	tx[2];
	float	ty[2];
	float	tmin;
	float	tmax;

	tx[0] = (((int)posX) - 0.000001f - posX) / dirX;
	tx[1] = (((int)posX) + 1.000001f - posX) / dirX;
	ty[0] = (((int)posY) - 0.000001f - posY) / dirY;
	ty[1] = (((int)posY) + 1.000001f - posY) / dirY;
	tmin = fmax(fmin(tx[0], tx[1]), fmin(ty[0], ty[1]));
	tmax = fmin(fmax(tx[0], tx[1]), fmax(ty[0], ty[1]));
	if (tmin < 0.0f)
		return (tmax);
	return (tmin);
}

float	shoot_ray(t_data *data, t_face *face, t_extra extra)
{
	float	pos_x;
	float	pos_y;
	float	dist_tot;
	int		iter;
	float	dist;

	dist_tot = 0.0f;
	iter = 0;
	pos_x = data->player.posx;
	pos_y = data->player.posy;
	while (iter < 20 && data->map[(int)pos_y][(int)pos_x] != '1')
	{
		dist = distance_to_next_edge(pos_x, pos_y, extra.dir_x, extra.dir_y);
		pos_x += extra.dir_x * dist;
		pos_y += extra.dir_y * dist;
		dist_tot += dist;
		++iter;
	}
	face->pos_wall_x = pos_x;
	face->pos_wall_y = pos_y;
	return (dist_tot * cosf(extra.deviation_angle));
}

void	plage_shoot(t_data *data, float rot)
{
	t_extra	extra;
	int		pix_x;

	pix_x = 0;
	extra.start_rot = rot - 0.15f * M_PI;
	extra.off_rot = (0.3f * M_PI) / data->ptr->img->width;
	while (pix_x < data->ptr->img->width)
	{
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
