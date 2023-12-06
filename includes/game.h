/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:50:22 by audrye            #+#    #+#             */
/*   Updated: 2023/12/06 19:25:02 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "cub.h"

int		deal_key(int key, t_data *data);
void	mlx_loop_init();
void	exit_game(char *str);


#endif
