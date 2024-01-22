/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:20:38 by audrye            #+#    #+#             */
/*   Updated: 2024/01/22 15:53:52 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	exit_game(void)
{
	t_data	**data;

	data = get_data();
	mlx_destroy_image((*data)->ptr->mlx, (*data)->textures->ea_img);
	mlx_destroy_image((*data)->ptr->mlx, (*data)->textures->so_img);
	mlx_destroy_image((*data)->ptr->mlx, (*data)->textures->no_img);
	mlx_destroy_image((*data)->ptr->mlx, (*data)->textures->we_img);
	mlx_destroy_image((*data)->ptr->mlx, (*data)->ptr->img);
	mlx_destroy_window((*data)->ptr->mlx, (*data)->ptr->win);
	mlx_destroy_display((*data)->ptr->mlx);
	free((*data)->ptr->mlx);
	garbage_collect();
	exit(0);
	return (0);
}
