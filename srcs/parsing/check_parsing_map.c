/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:48:54 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/29 11:01:54 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	check_line(char *actual_line, char *line)
{
	int	i;

	i = 0;
	if (!line)
		return ;
	while (actual_line[i] && line[i])
	{
		if (actual_line[i + 1] && actual_line[i + 1] == ' ')
		{
			if (!is_wall_space(line[i]) || !is_wall_space(line[i + 1])
				|| !is_wall_space(line[i + 2]))
				error(ERR_WALL, " line_actual_line", PARS_KO);
		}
		i++;
	}
	if (ft_strlen(actual_line) < ft_strlen(line))
	{
		while (line[i])
		{
			if (line[i] != '1')
				error(ERR_WALL, " line_line", PARS_KO);
			i++;
		}
	}
}

void	check_wall_and_space(char *line, int ref)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ref == 2 && (line[i] != '1' || line[ft_strlen(line) - 1] != '1'))
		error(ERR_WALL, NULL, PARS_KO);
	while (line[i])
	{
		if (line[i + 1] && line[i + 1] == ' ' && line[i] == '0')
			error(ERR_WALL, NULL, PARS_KO);
		if (line[i + 1] && line[i] == ' ' && line[i + 1] == '0')
			error(ERR_WALL, NULL, PARS_KO);
		if (ref == 1 && line[i] != ' ' && line[i] != '1')
			error(ERR_WALL, NULL, PARS_KO);
		i++;
	}
}

void	check_wall(t_map *map)
{
	char	*prev_line;

	check_wall_and_space(map->line, 1);
	prev_line = map->line;
	map = map->next;
	while (map->next)
	{
		check_wall_and_space(map->line, 2);
		check_line(map->line, prev_line);
		check_line(map->line, map->next->line);
		prev_line = map->line;
		map = map->next;
	}
	check_line(map->line, prev_line);
	check_wall_and_space(map->line, 1);
}

void	check_char(t_map *map)
{
	int	i;

	while (map)
	{
		i = 0;
		if (!map->line || (map->line[0] && map->line[0] == '\n'))
			error(ERR_LINE_EMPTY, NULL, PARS_KO);
		while (map->line[i])
			if (!is_map_char(map->line[i++]))
				error(ERR_FORBID_CHAR, NULL, PARS_KO);
		map = map->next;
	}
}
