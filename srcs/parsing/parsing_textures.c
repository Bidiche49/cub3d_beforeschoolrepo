/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:44:15 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/29 10:59:07 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_color	*convert_rgb(char *rgb)
{
	char	**split_rgb;
	t_color	*color;

	if (ft_countword(rgb, ',') != 3)
		return (error(ERR_RGB, NULL, PARS_KO), NULL);
	split_rgb = ft_split(rgb, ',');
	color = ft_calloc(1, sizeof(t_color *));
	color->r = ft_atoi(split_rgb[0]);
	if (color->r < 0 || color->r > 255)
		return (error(ERR_RGB, NULL, PARS_KO), NULL);
	color->g = ft_atoi(split_rgb[1]);
	if (color->g < 0 || color->g > 255)
		return (error(ERR_RGB, NULL, PARS_KO), NULL);
	color->b = ft_atoi(split_rgb[2]);
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

void	check_line_texture(char *line)
{
	char		*first_word;
	t_textures	*textures;

	textures = *get_textures();
	first_word = get_first_word(line);
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

int	textures_is_empty(void)
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
