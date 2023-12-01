/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 01:24:55 by ntardy            #+#    #+#             */
/*   Updated: 2023/12/01 01:38:21 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib_utils.h"

void del_pars_map()
{
    t_pars_map  **map;
    t_pars_map  *line_map;
    
    map = get_pars_map();
    while ((*map))
    {
        line_map = (*map);
        (*map) = (*map)->next;
        tracked_free(line_map->line);
        tracked_free(line_map);
    }
    tracked_free(map);
}
