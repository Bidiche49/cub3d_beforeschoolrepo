/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:34:24 by audrye            #+#    #+#             */
/*   Updated: 2023/12/12 20:01:10 by ntardy           ###   ########.fr       */
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
}

void	mouv_press_s(t_data *data)
{
	data->player.posY -= cos(data->player.dir) * 0.1f;
	data->player.posX -= sin(data->player.dir) * 0.1f;
}
