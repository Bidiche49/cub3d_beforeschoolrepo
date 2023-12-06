/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:50:28 by audrye            #+#    #+#             */
/*   Updated: 2023/12/06 19:29:33 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

void	fill_texture(t_data **data)
{
	int	h_w;

	h_w = 300;
	(*data)->textures->no_img
		= mlx_xpm_file_to_image((*data)->ptr->mlx, (*data)->textures->no_path, &h_w, &h_w);
	if (!(*data)->textures->no_img)
		error(ERR_IMG, (*data)->textures->no_path, MLX_KO);
	(*data)->textures->so_img
		= mlx_xpm_file_to_image((*data)->ptr->mlx, (*data)->textures->so_path, &h_w, &h_w);
	if (!(*data)->textures->so_img)
		error(ERR_IMG, (*data)->textures->so_path, MLX_KO);
	(*data)->textures->ea_img
		= mlx_xpm_file_to_image((*data)->ptr->mlx, (*data)->textures->ea_path, &h_w, &h_w);
	if (!(*data)->textures->ea_img)
		error(ERR_IMG, (*data)->textures->ea_path, MLX_KO);
	(*data)->textures->we_img
		= mlx_xpm_file_to_image((*data)->ptr->mlx, (*data)->textures->we_path, &h_w, &h_w);
	if (!(*data)->textures->we_img)
		error(ERR_IMG, (*data)->textures->we_path, MLX_KO);
}

int	deal_key(int key, t_data *data)
{
	(void)data;
	if (key == 65307)
		exit_game(NULL);
	return (key);
}

void	mlx_loop_init()
{
	t_data	**data;

	data = get_data();
	(*data)->ptr->mlx = mlx_init();
	if (!(*data)->ptr->mlx)
		error(ERR_PTR_MLX_KO, NULL, MLX_KO);
	(*data)->ptr->win = mlx_new_window((*data)->ptr->mlx, 300, 300, "cub3D");
	if (!(*data)->ptr->win)
		error(ERR_PTR_WIN_KO, NULL, MLX_KO);
	mlx_key_hook((*data)->ptr->win, deal_key, (*data));
	fill_texture(data);
	// mlx_hook((*data)->ptr->win, 17, 1, error, (*data));
	mlx_loop((*data)->ptr->mlx);
}

