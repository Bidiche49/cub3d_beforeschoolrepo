/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:20:38 by audrye            #+#    #+#             */
/*   Updated: 2023/12/08 16:04:47 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	exit_game(char *str)
{
// 	t_data **data;

// 	data = get_data();
	if (str)
		ft_putstrfd(str, 1);

	garbage_collect();
	exit(0);
}
