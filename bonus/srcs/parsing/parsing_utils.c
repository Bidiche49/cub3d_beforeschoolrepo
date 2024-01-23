/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:54:42 by ntardy            #+#    #+#             */
/*   Updated: 2024/01/23 21:34:11 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	is_map_char(char c)
{
	if (c == '0' || c == '2')
		return (1);
	if (is_player(c))
		return (1);
	return (is_wall_space(c));
}

void	fill_data(void)
{
	t_data	**data;

	data = get_data();
	*data = ft_calloc(sizeof(t_data), 1);
	(*data)->ptr = ft_calloc(1, sizeof(t_ptr));
	(*data)->textures = *get_textures();
	(*data)->map = cast_map();
	(*data)->player = fill_player((*data)->map);
}
