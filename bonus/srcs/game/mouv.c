/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:34:24 by audrye            #+#    #+#             */
/*   Updated: 2024/01/21 20:02:06 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

void	mouv_press_w(t_data *data)
{
	data->player.posy += cos(data->player.dir) * 0.1f;
	data->player.posx += sin(data->player.dir) * 0.1f;
	if (data->map[(int)data->player.posy][(int)data->player.posx] == '1')
	{
		data->player.posy -= cos(data->player.dir) * 0.1f;
		data->player.posx -= sin(data->player.dir) * 0.1f;
	}
}

void	mouv_press_s(t_data *data)
{
	data->player.posy -= cos(data->player.dir) * 0.1f;
	data->player.posx -= sin(data->player.dir) * 0.1f;
	if (data->map[(int)data->player.posy][(int)data->player.posx] == '1')
	{
		data->player.posy += cos(data->player.dir) * 0.1f;
		data->player.posx += sin(data->player.dir) * 0.1f;
	}
}

void	mouv_press_d(t_data *data)
{
	float	right_dir;

	right_dir = data->player.dir + M_PI / 2;
	data->player.posy += cos(right_dir) * 0.1f;
	data->player.posx += sin(right_dir) * 0.1f;
	if (data->map[(int)data->player.posy][(int)data->player.posx] == '1')
	{
		data->player.posy -= cos(right_dir) * 0.1f;
		data->player.posx -= sin(right_dir) * 0.1f;
	}
}

void	mouv_press_a(t_data *data)
{
	float	left_dir;

	left_dir = data->player.dir - M_PI / 2;
	data->player.posy += cos(left_dir) * 0.1f;
	data->player.posx += sin(left_dir) * 0.1f;
	if (data->map[(int)data->player.posy][(int)data->player.posx] == '1')
	{
		data->player.posy -= cos(left_dir) * 0.1f;
		data->player.posx -= sin(left_dir) * 0.1f;
	}
}
