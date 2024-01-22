/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:01:40 by ntardy            #+#    #+#             */
/*   Updated: 2024/01/22 16:10:19 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

void	mouv_press_left(t_data *data)
{
	data->player.dir -= 0.1f;
}

void	mouv_press_right(t_data *data)
{
	data->player.dir += 0.1f;
}
