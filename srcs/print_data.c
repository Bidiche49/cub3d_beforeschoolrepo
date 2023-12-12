/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:16:23 by ntardy            #+#    #+#             */
/*   Updated: 2023/12/12 20:01:10 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	print_data(void)
{
	t_data		*data;
	int			y;

	data = *get_data();
	y = 0;
	printf("MAP :\n");
	while (data->map[y])
		printf("%s\n", data->map[y++]);
	printf("\nPLAYER :\n");
	printf("posX : %f\n", data->player.posX);
	printf("posY : %f\n", data->player.posY);
	printf("direction : %f\n", data->player.dir);
	printf("\nTEXTURES PATHS :\n");
	printf("north : %s\n", data->textures->no_path);
	printf("south : %s\n", data->textures->so_path);
	printf("east : %s\n", data->textures->ea_path);
	printf("west : %s\n", data->textures->we_path);
	printf("\nCOLORS :\n");
	printf("ceiling : %d, %d, %d\n", data->textures->ceiling->r, data->textures->ceiling->g, data->textures->ceiling->b);
	printf("floor : %d, %d, %d\n", data->textures->floor->r, data->textures->floor->g, data->textures->floor->b);

}
