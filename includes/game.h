/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:50:22 by audrye            #+#    #+#             */
/*   Updated: 2024/01/22 16:10:25 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "cub.h"

int		deal_key(int key, t_data *data);
void	mlx_loop_init(void);
int		exit_game(void);

void	print_column(t_data *data);

//---------------------------------------//
//					MOUV				 //
//---------------------------------------//

void	mouv_press_left(t_data *data);
void	mouv_press_right(t_data *data);
void	mouv_press_w(t_data *data);
void	mouv_press_s(t_data *data);
void	mouv_press_a(t_data *data);
void	mouv_press_d(t_data *data);

//---------------------------------------//
//				DISPLAY SCREEN			 //
//---------------------------------------//

t_img	*choice_txt(t_textures *textures, t_face face);
void	put_pixel(t_img *img, int x, int y, int color);
void	clear_img(t_img *img, int color);
void	put_color(t_data *data, int pix_x, int pix_y, t_color *color);
int		calc_wall_height(int x, t_face face);
int		print_face(t_data *data, float *current_angle, \
t_extra extra, int pix_x);

//---------------------------------------//
//				RAYCASTING				 //
//---------------------------------------//

float	shoot_ray(t_data *data, t_face *face, t_extra extra);

#endif
