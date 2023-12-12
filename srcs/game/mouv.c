/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:34:24 by audrye            #+#    #+#             */
/*   Updated: 2023/12/12 21:37:24 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

void	mouv_press_a(t_data *data)
{
	data->player.dir -= 0.1f;
}

void	mouv_press_d(t_data *data)
{
	data->player.dir += 0.1f;
}

void	mouv_press_w(t_data *data)
{
	data->player.posY += cos(data->player.dir) * 0.1f;
	data->player.posX += sin(data->player.dir) * 0.1f;
	if (data->map[(int)data->player.posY][(int)data->player.posX] == '1')
	{
		data->player.posY -= cos(data->player.dir) * 0.1f;
		data->player.posX -= sin(data->player.dir) * 0.1f;
	}
}

void	mouv_press_s(t_data *data)
{
	data->player.posY -= cos(data->player.dir) * 0.1f;
	data->player.posX -= sin(data->player.dir) * 0.1f;
	if (data->map[(int)data->player.posY][(int)data->player.posX] == '1')
	{
		data->player.posY += cos(data->player.dir) * 0.1f;
		data->player.posX += sin(data->player.dir) * 0.1f;
	}
}
