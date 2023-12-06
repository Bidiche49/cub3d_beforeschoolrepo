/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:55:05 by ntardy            #+#    #+#             */
/*   Updated: 2023/12/06 17:55:50 by audrye           ###   ########.fr       */
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
				player.startDir = map[y][x];
				player.posX = x;
				player.posY = y;
				return (player);
			}
			x++;
		}
		y++;
	}
	player.startDir = map[y][x];
	player.posX = x;
	player.posY = y;
	return (player);}

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

void	parsing(int argc, char **argv)
{
	if (argc != 2)
		error(ERR_WRONG_ARG, NULL, ARG_NOK);
	check_path(argv[1]);
	init_data();
	parsing_file(argv[1]);
	parsing_map();
	fill_data();
	print_data();
}
