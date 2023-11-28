/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:13:27 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/27 19:40:46 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/getters.h"

t_map **get_map()
{
	static t_map	*map = NULL;

	return (&map);
}

t_textures **get_textures()
{
	static t_textures	*textures = NULL;

	return (&textures);
}
