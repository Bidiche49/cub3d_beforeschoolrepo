/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:50:28 by audrye            #+#    #+#             */
/*   Updated: 2023/12/11 19:38:56 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

void	fill_texture(t_data **data)
{
	int	h_w;

	h_w = 64;
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
	(*data)->textures->we_img->data = mlx_get_data_addr((*data)->textures->we_img, &(*data)->textures->we_img->bpp,
		&(*data)->textures->we_img->size_line, &(*data)->textures->we_img->type);// securiser get_data_addr
}

int	deal_key(int key, t_data *data)
{
	(void)data;
	if (key == XK_Escape)
		exit_game(NULL);
	return (key);
}

int	game_loop(void *mlx_data)
{
	t_data *const	data = mlx_data;

	print_column(data);
	mlx_put_image_to_window(data->ptr->mlx, data->ptr->win, data->ptr->img, 0, 0);
	return (0);
}

void	mlx_loop_init()
{
	t_data	**data;

	data = get_data();
	(*data)->ptr->mlx = mlx_init();
	if (!(*data)->ptr->mlx)
		error(ERR_PTR_MLX_KO, NULL, MLX_KO);
	(*data)->ptr->win = mlx_new_window((*data)->ptr->mlx, 400, 400, "cub3D");
	if (!(*data)->ptr->win)
		error(ERR_PTR_WIN_KO, NULL, MLX_KO);
	(*data)->ptr->img = mlx_new_image((*data)->ptr->mlx, 400, 400);
	(*data)->ptr->img->data = mlx_get_data_addr((*data)->ptr->img, &(*data)->ptr->img->bpp,
		&(*data)->ptr->img->size_line, &(*data)->ptr->img->type);
	//CHECK FOR IMAGE ERROR
	mlx_key_hook((*data)->ptr->win, deal_key, (*data));
	fill_texture(data);
	//appel de raycasting ici.
	// mlx_hook((*data)->ptr->win, 17, 1, error, (*data));
	mlx_loop_hook((*data)->ptr->mlx, &game_loop, *data);
	mlx_loop((*data)->ptr->mlx);
}

