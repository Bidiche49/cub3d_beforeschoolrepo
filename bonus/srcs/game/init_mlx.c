/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:50:28 by audrye            #+#    #+#             */
/*   Updated: 2024/01/23 21:32:03 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

void	fill_texture_2(t_data **data, int h_w)
{
	(*data)->textures->ea_img
		= mlx_xpm_file_to_image((*data)->ptr->mlx,
			(*data)->textures->ea_path, &h_w, &h_w);
	if (!(*data)->textures->ea_img)
		error(ERR_IMG, (*data)->textures->ea_path, MLX_KO);
	(*data)->textures->we_img
		= mlx_xpm_file_to_image((*data)->ptr->mlx,
			(*data)->textures->we_path, &h_w, &h_w);
	if (!(*data)->textures->we_img)
		error(ERR_IMG, (*data)->textures->we_path, MLX_KO);
	(*data)->textures->door_img
		= mlx_xpm_file_to_image((*data)->ptr->mlx,
			(*data)->textures->door_path, &h_w, &h_w);
	if (!(*data)->textures->door_img)
		error(ERR_IMG, (*data)->textures->door_path, MLX_KO);
}

void	fill_texture(t_data **data)
{
	int	h_w;

	h_w = 64;
	(*data)->textures->nos_img
		= mlx_xpm_file_to_image((*data)->ptr->mlx,
			(*data)->textures->nos_path, &h_w, &h_w);
	if (!(*data)->textures->nos_img)
		error(ERR_IMG, (*data)->textures->nos_path, MLX_KO);
	(*data)->textures->no_img
		= mlx_xpm_file_to_image((*data)->ptr->mlx,
			(*data)->textures->no_path, &h_w, &h_w);
	if (!(*data)->textures->no_img)
		error(ERR_IMG, (*data)->textures->no_path, MLX_KO);
	(*data)->textures->so_img
		= mlx_xpm_file_to_image((*data)->ptr->mlx,
			(*data)->textures->so_path, &h_w, &h_w);
	if (!(*data)->textures->so_img)
		error(ERR_IMG, (*data)->textures->so_path, MLX_KO);
	fill_texture_2(data, h_w);
}

int	deal_key(int key, t_data *data)
{
	if (key == XK_Left)
		mouv_press_left(data);
	if (key == XK_Right)
		mouv_press_right(data);
	if (key == XK_w || key == XK_W)
		mouv_press_w(data);
	if (key == XK_s || key == XK_S)
		mouv_press_s(data);
	if (key == XK_a || key == XK_A)
		mouv_press_a(data);
	if (key == XK_d || key == XK_D)
		mouv_press_d(data);
	if (key == XK_e || key == XK_E)
		open_doors(data);
	if (key == XK_Escape)
		exit_game();
	return (key);
}

int	game_loop(void *mlx_data)
{
	t_data *const	data = mlx_data;
	t_data			*tmp_data;

	tmp_data = *get_data();
	print_column(data);
	tmp_data->cycles_since_last_switch++;
	if (tmp_data->cycles_since_last_switch >= 500)
		tmp_data->cycles_since_last_switch = 0;
	mlx_put_image_to_window(data->ptr->mlx, data->ptr->win,
		data->ptr->img, 0, 0);
	return (0);
}

void	mlx_loop_init(void)
{
	t_data	**data;

	data = get_data();
	(*data)->mouse_pos = 10000;
	(*data)->ptr->mlx = mlx_init();
	if (!(*data)->ptr->mlx)
		error(ERR_PTR_MLX_KO, NULL, MLX_KO);
	(*data)->ptr->win = mlx_new_window((*data)->ptr->mlx, 900, 600, "cub3D");
	if (!(*data)->ptr->win)
		error(ERR_PTR_WIN_KO, NULL, MLX_KO);
	(*data)->ptr->img = mlx_new_image((*data)->ptr->mlx, 900, 600);
	(*data)->ptr->img->data = mlx_get_data_addr((*data)->ptr->img,
			&(*data)->ptr->img->bpp,
			&(*data)->ptr->img->size_line,
			&(*data)->ptr->img->type);
	if (!(*data)->ptr->img->data)
		error(ERR_PTR_WIN_KO, NULL, MLX_KO);
	fill_texture(data);
	(*data)->cycles_since_last_switch = 0;
	mlx_loop_hook((*data)->ptr->mlx, &game_loop, *data);
	mlx_key_hook((*data)->ptr->win, &deal_key, (*data));
	mlx_hook((*data)->ptr->win, MotionNotify, PointerMotionMask,
		&mouse_move, (*data));
	mlx_hook((*data)->ptr->win, 17, 1, exit_game, *data);
	mlx_loop((*data)->ptr->mlx);
}
