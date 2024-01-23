/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_screen_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:50:52 by ntardy            #+#    #+#             */
/*   Updated: 2024/01/23 19:51:09 by ntardy           ###   ########.fr       */
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
