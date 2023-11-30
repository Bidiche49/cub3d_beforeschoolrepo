/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:13:27 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/30 21:24:04 by ntardy           ###   ########.fr       */
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

t_garbage	**get_garbage(void)
{
	static t_garbage	*garbage = NULL;

	return (&garbage);
}

t_fd	**get_fd(void)
{
	static t_fd	*fd = NULL;

	return (&fd);
}