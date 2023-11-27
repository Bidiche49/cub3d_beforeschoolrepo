/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:13:27 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/25 00:28:47 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/getters.h"

char **get_map()
{
	static char	**map = NULL;

	return (map);
}

t_textures **get_textures()
{
	static t_textures	*textures = NULL;

	return (&textures);
}
