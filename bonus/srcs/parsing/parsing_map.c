/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:54:14 by ntardy            #+#    #+#             */
/*   Updated: 2024/01/21 18:56:29 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	fill_map(char *line)
{
	t_pars_map	**map;
	t_pars_map	*current;
	t_pars_map	*new;

	new = ft_calloc(1, sizeof(t_pars_map));
	new->line = ft_strdup(line);
	if (ft_strlen(new->line) > 1
		&& new->line[ft_strlen(new->line) - 1] == '\n')
		new->line[ft_strlen(new->line) - 1] = '\0';
	new->next = NULL;
	map = get_pars_map();
	if (!(*map))
	{
		if (line && line[0] && line[0] == '\n')
			return ;
		(*map) = new;
		return ;
	}
	current = (*map);
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

char	**cast_map(void)
{
	t_pars_map	*line;
	char		**map;
	int			nb_line;

	line = *get_pars_map();
	nb_line = 1;
	while (line)
	{
		line = line->next;
		nb_line++;
	}
	map = ft_calloc(sizeof(char *), nb_line);
	line = *get_pars_map();
	nb_line = 0;
	while (line)
	{
		map[nb_line++] = ft_strdup(line->line);
		line = line->next;
	}
	del_pars_map();
	return (map);
}

t_pars_map	*check_empty_line_loop(t_pars_map *map)
{
	t_pars_map	*tmp;

	tmp = NULL;
	while (map)
	{
		if (map->next && map->next->line && map->next->line[0] == '\n')
		{
			tmp = map;
			map = map->next;
		}
		while (map && map->line && map->line[0] == '\n')
		{
			map = map->next;
			if (map && map->line[0] && map->line[0] != '\n')
				error(ERR_LINE_EMPTY, NULL, PARS_KO);
		}
		if (map)
			map = map->next;
	}
	return (tmp);
}

void	check_empty_line(t_pars_map *map)
{
	t_pars_map	*tmp;

	tmp = check_empty_line_loop(map);
	if (tmp)
	{
		map = tmp->next;
		tmp->next = NULL;
		while (map)
		{
			tmp = map->next;
			tracked_free(map->line);
			tracked_free(map);
			map = tmp;
		}
	}
}

void	parsing_map(void)
{
	t_pars_map	**map;

	map = get_pars_map();
	if (!map || !(*map))
		error(ERR_MAP_EMPTY, NULL, PARS_KO);
	if (!(*map)->next || !(*map)->next->next)
		error(ERR_LITTLE_MAP, NULL, PARS_KO);
	check_empty_line(*map);
	check_char(*map);
	check_player(*map);
	check_wall(*map);
}
