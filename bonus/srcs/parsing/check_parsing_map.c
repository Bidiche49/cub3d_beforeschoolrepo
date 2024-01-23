/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:48:54 by ntardy            #+#    #+#             */
/*   Updated: 2024/01/23 21:33:56 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	check_line(char *actual_line, char *line)
{
	int	i;

	i = -1;
	if (!line)
		return ;
	while (actual_line[++i] && line[i])
	{
		if (actual_line[i + 1] && actual_line[i + 1] == ' ')
		{
			if (!is_wall_space(line[i]) || !is_wall_space(line[i + 1])
				|| !is_wall_space(line[i + 2]))
				error(ERR_WALL, NULL, PARS_KO);
		}
	}
	if (ft_strlen(actual_line) < ft_strlen(line))
	{
		while (line[i])
		{
			if (line[i] != '1')
				error(ERR_WALL, NULL, PARS_KO);
			i++;
		}
	}
	else if (i > 0 && !line[i] && actual_line[i] && actual_line[i - 1] != '1')
		error(ERR_WALL, NULL, PARS_KO);
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
		if (line[i + 1] && line[i + 1] == ' ' && (line[i] == '0'))
			error(ERR_WALL, NULL, PARS_KO);
		if (line[i + 1] && line[i] == ' ' && (line[i + 1] == '0'))
			error(ERR_WALL, NULL, PARS_KO);
		if (ref == 1 && line[i] != ' ' && line[i] != '1')
			error(ERR_WALL, NULL, PARS_KO);
		i++;
	}
}

void	check_wall(t_pars_map *map)
{
	char	*prev_line;

	check_wall_and_space(map->line, 1);
	check_line(map->line, map->next->line);
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

void	check_char(t_pars_map *map)
{
	int	i;

	while (map)
	{
		i = 0;
		while (map->line[i])
		{
			if (!is_map_char(map->line[i]))
				error(ERR_FORBID_CHAR, NULL, PARS_KO);
			i++;
		}
		map = map->next;
	}
}

void	check_player(t_pars_map *map)
{
	int	i;
	int	nb_player;

	nb_player = 0;
	while (map)
	{
		i = 0;
		while (map->line[i])
		{
			if (!is_wall_space(map->line[i]) && map->line[i] != '0'
				&& map->line[i] != '2')
				nb_player++;
			i++;
		}
		map = map->next;
	}
	if (nb_player != 1)
		error(ERR_PLAYER, NULL, PARS_KO);
}
