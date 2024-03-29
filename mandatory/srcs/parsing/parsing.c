/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:55:05 by ntardy            #+#    #+#             */
/*   Updated: 2024/01/21 19:12:23 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	parsing_file(char *path)
{
	int			fd;
	char		*line;

	fd = tracked_open(path, O_DIRECTORY);
	check_file(path, &fd);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] && line[0] != '\n' && textures_is_empty(2))
			check_line_texture(line);
		else if (line[0] && !textures_is_empty(2))
			fill_map(line);
		tracked_free(line);
		line = get_next_line(fd);
	}
	if (textures_is_empty(2))
		error (ERR_MAP_EMPTY, NULL, PARS_KO);
	tracked_close(fd);
}

void	init_data(void)
{
	t_textures	**textures;
	t_textures	*new;

	textures = get_textures();
	new = ft_calloc(1, sizeof(t_textures));
	new->floor = ft_calloc(1, sizeof(t_color));
	new->floor->r = -1;
	new->floor->g = -1;
	new->floor->b = -1;
	new->ceiling = ft_calloc(1, sizeof(t_color));
	new->ceiling->r = -1;
	new->ceiling->g = -1;
	new->ceiling->b = -1;
	(*textures) = new;
}

float	dir_player(char **map, int x, int y)
{
	if (map[y][x] == 'N')
		return (M_PI);
	else if (map[y][x] == 'E')
		return (M_PI / 2);
	else if (map[y][x] == 'S')
		return (0.0f);
	else if (map[y][x] == 'W')
		return (((M_PI / 2) * -1));
	return (0.5);
}

t_player	fill_player(char **map)
{
	int			x;
	int			y;
	t_player	player;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player(map[y][x]))
			{
				player.dir = dir_player(map, x, y);
				player.posx = (float)x + 0.5f;
				player.posy = (float)y + 0.5f;
				return (player);
			}
			x++;
		}
		y++;
	}
	player.dir = dir_player(map, x, y);
	player.posx = x;
	player.posy = y;
	return (player);
}

void	parsing(int argc, char **argv)
{
	if (argc != 2)
		error(ERR_WRONG_ARG, NULL, ARG_NOK);
	check_path(argv[1]);
	init_data();
	parsing_file(argv[1]);
	parsing_map();
	fill_data();
}
