/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:13:27 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/29 10:39:39 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/getters.h"

t_map	**get_map(void)
{
	static t_map	*map = NULL;

	return (&map);
}

t_textures	**get_textures(void)
{
	static t_textures	*textures = NULL;

	return (&textures);
}
