/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:44:15 by ntardy            #+#    #+#             */
/*   Updated: 2024/01/22 17:41:34 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_color	*convert_rgb(char *rgb, t_color *color)
{
	char	**split_rgb;

	if (ft_countword(rgb, ',') != 3)
		return (error(ERR_RGB, NULL, PARS_KO), NULL);
	split_rgb = ft_split(rgb, ',');
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
	fd = tracked_open(path_texture, O_DIRECTORY);
	check_file(path_texture, &fd);
	tracked_close(fd);
	return (ft_strdup(path_texture));
}

void	if_forest(char *first_word, char *start, t_textures *textures)
{
	if (!ft_strcmp(first_word, "NO") && !textures->no_path)
		textures->no_path = check_texture(start);
	else if (!ft_strcmp(first_word, "NOS") && !textures->nos_path)
		textures->nos_path = check_texture(start);
	else if (!ft_strcmp(first_word, "SO") && !textures->so_path)
		textures->so_path = check_texture(start);
	else if (!ft_strcmp(first_word, "WE") && !textures->we_path)
		textures->we_path = check_texture(start);
	else if (!ft_strcmp(first_word, "EA") && !textures->ea_path)
		textures->ea_path = check_texture(start);
	else if (!textures_is_empty(1) && !ft_strcmp(first_word, "C")
		&& textures->ceiling->b == -1)
		convert_rgb(start, textures->ceiling);
	else if (!textures_is_empty(1) && !ft_strcmp(first_word, "F")
		&& textures->floor->b == -1)
		convert_rgb(start, textures->floor);
	else
		error(ERR_PATTERN_FILE, NULL, PARS_KO);
}

void	check_line_texture(char *line)
{
	char		*first_word;
	char		*start;

	first_word = get_first_word(line);
	start = line + ft_strlen(first_word) + 1;
	if_forest(first_word, start, *get_textures());
	tracked_free(first_word);
}

int	textures_is_empty(int ref)
{
	t_textures	**textures;

	textures = get_textures();
	if (!(*textures)->no_path || !(*textures)->so_path)
		return (1);
	if (!(*textures)->we_path || !(*textures)->ea_path)
		return (1);
	if (ref == 2 && ((*textures)->floor->r == -1
			|| (*textures)->ceiling->r == -1))
		return (1);
	return (0);
}
