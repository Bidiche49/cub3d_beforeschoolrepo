/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:55:05 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/27 18:51:17 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	check_ext(char *path, char *ext)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		error(ERR_WRONG_EXT, ext, ARG_NOK);
	if (ft_strcmp(path + (len - ft_strlen(ext)), ext))
		error(ERR_WRONG_EXT, ext, ARG_NOK);
}


void	check_path(char *path)
{
	if (!path)
		error(ERR_PATH_NULL, NULL, ARG_NOK);
	check_ext(path, ".cub");
}

void	check_file(char *path, int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		error(path , ERR_OPEN_DIR, OPEN_KO);
	}
	*fd = open(path, O_RDONLY);
	if (*fd == -1)
		error(ERR_OPEN_KO, path, OPEN_KO);
}

t_color	*convert_rgb(char *rgb)
{
	char	**split_rgb;
	t_color	*color;

	printf("avant atoi\n\n");
	printf("nb word : %d\n", ft_countword(rgb, ','));
	if (ft_countword(rgb, ',') != 3)
		return (error(ERR_RGB, NULL, PARS_KO), NULL);
	split_rgb = ft_split(rgb, ',');
	printf("g : %s\n", split_rgb[0]);
	printf("g : %s\n", split_rgb[1]);
	printf("g : %s", split_rgb[2]);
	color = ft_calloc(1, sizeof(t_color *));
	color->r = ft_atoi(split_rgb[0]);
	// printf("r : %d\n", ft_atoi(split_rgb[0]));
	if (color->r < 0 || color->r > 255)
		return (error(ERR_RGB, NULL, PARS_KO), NULL);
	color->g = ft_atoi(split_rgb[1]);
	printf("g : %d\n", ft_atoi(split_rgb[1]));
	if (color->g < 0 || color->g > 255)
		return (error(ERR_RGB, NULL, PARS_KO), NULL);
	color->b = ft_atoi(split_rgb[2]);
	printf("b : %d\n", ft_atoi(split_rgb[2]));
	if (color->b < 0 || color->b > 255)
		return (error(ERR_RGB, NULL, PARS_KO), NULL);
	return (color);

}

char	*check_texture(char *path_texture)
{
	int	fd;

	path_texture[ft_strlen(path_texture) - 1] = '\0';
	check_ext(path_texture, ".xpm");
	fd = open(path_texture, O_DIRECTORY);
	check_file(path_texture, &fd);
	close(fd);
	return (ft_strdup(path_texture));
}

void	check_line(char *line)
{
	char 		*first_word;
	t_textures	*textures;

	textures = *get_textures();
	printf("first word = \n");
	first_word = get_first_word(line);
	printf("first word = %s\n", first_word);
	if (!ft_strcmp(first_word, "NO"))
		textures->no_path = check_texture(line + ft_strlen(first_word) + 1);
	else if (!ft_strcmp(first_word, "SO"))
		textures->so_path = check_texture(line + ft_strlen(first_word) + 1);
	else if (!ft_strcmp(first_word, "WE"))
		textures->we_path = check_texture(line + ft_strlen(first_word) + 1);
	else if (!ft_strcmp(first_word, "EA"))
		textures->ea_path = check_texture(line + ft_strlen(first_word) + 1);
	else if (!ft_strcmp(first_word, "F"))
		textures->floor = convert_rgb(line + ft_strlen(first_word) + 1);
	else if (!ft_strcmp(first_word, "C"))
		textures->ceiling = convert_rgb(line + ft_strlen(first_word) + 1);
	else
		error(ERR_PATTERN_FILE, NULL, PARS_KO);
	tracked_free(first_word);
}

void	print_textures()
{
	t_textures	**textures;

	textures = get_textures();
	printf("chemin nord : %s\n", (*textures)->no_path);
	printf("chemin sud : %s\n", (*textures)->so_path);
}

int	textures_is_empty()
{
	t_textures	**textures;

	textures = get_textures();
	if (!(*textures)->no_path || !(*textures)->so_path)
		return (1);
	if (!(*textures)->we_path || !(*textures)->ea_path)
		return (1);
	if (!(*textures)->floor || !(*textures)->ceiling)
		return (1);
	return (0);
}

void	parsing_file(char *path)
{
	int			fd;
	char		*line;

	fd = open(path, O_DIRECTORY);
	check_file(path, &fd);
	line = get_next_line(fd);
	while (line)
	{
		printf("line = %s\n\n", line);
		if (line[0] && line[0] != '\n' && textures_is_empty())
			check_line(line);
		else if (line[0] && line[0] != '\n' && !textures_is_empty())
			parsing_map(line);
		tracked_free(line);
		printf("line = %s\n\n", line);
		line = get_next_line(fd);
	}
	printf("after while\n\n");
	if (textures_is_empty())
		error (ERR_MAP_EMPTY, NULL, PARS_KO);
	close(fd);
}

void	init_data()
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
	printf("after pars file\n");
	parsing_map(argv[1]);
	print_textures();
}
