/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:55:05 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/29 12:26:57 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	parsing_file(char *path)
{
	int			fd;
	char		*line;

	fd = open(path, O_DIRECTORY);
	check_file(path, &fd);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] && line[0] != '\n' && textures_is_empty(2))
			check_line_texture(line); //////////Penser a bien close les fds dans tous les cas
		else if (line[0] && !textures_is_empty(2))
			fill_map(line);
		tracked_free(line);
		line = get_next_line(fd);
	}
	if (textures_is_empty(2))
		error (ERR_MAP_EMPTY, NULL, PARS_KO);
	close(fd);
}

void	init_data(void)
{
	t_textures	**textures;
	t_textures	*new;

	textures = get_textures();
	new = ft_calloc(1, sizeof(t_textures *));
	new->no_path = NULL;
	new->so_path = NULL;
	new->we_path = NULL;
	new->ea_path = NULL;
	new->floor = NULL;
	new->ceiling = NULL;
	(*textures) = new;
}

void	parsing(int argc, char **argv)
{
	if (argc != 2)
		error(ERR_WRONG_ARG, NULL, ARG_NOK);
	check_path(argv[1]);
	init_data();
	parsing_file(argv[1]);
	parsing_map();
	print_map();
}
