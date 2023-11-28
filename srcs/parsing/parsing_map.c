/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:54:14 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/28 10:55:02 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	print_map()
{
	t_map	**map;
	t_map	*current;

	map = get_map();
	if (!*map)
		return ;
	current = *map;
	while (current != NULL)
	{
		printf("%s\n", current->line);
		current = current->next;
	}
}

void	fill_map(char *line)
{
	t_map	**map;
	t_map	*current;
	t_map	*new;

	new = ft_calloc(1, sizeof(t_map *));
	new->line = ft_strdup(line);
	if (ft_strlen(new->line) > 1 && new->line[ft_strlen(new->line) - 1] == '\n')
		new->line[ft_strlen(new->line) - 1] = '\0';
	new->next = NULL;
	map = get_map();
	if (!*map)
	{
		if (line && line[0] && line[0] == '\n')
			return ;
		return (*map = new, (void)0);
	}
	current = *map;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

int	is_map_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'S' || c == 'N')
		return (1);
	if (c == 'E' || c == 'O')
		return (1);
	return (0);
}

void	check_wall(t_map *map)
{
	int	i;

	i = -1;
	while (map->line[++i])
	{
		printf("\"%c\"\n", map->line[i]);
		if (map->line[i] != ' ' && map->line[i] != '1')
			error(ERR_WALL, NULL, PARS_KO);
	}
	while (map->next)
	{
		i = 0;
		while (map->line[i] == ' ')
			i++;
		if (map->line[i] != '1' || map->line[ft_strlen(map->line) - 1] != '1')
			error(ERR_WALL, NULL, PARS_KO);
		//penser a rentrer tous les cas des murs !!!!!!!
		map = map->next;
	}
	i = -1;
	while (map->line[++i])
		if (map->line[i] != ' ' && map->line[i] != '1')
			error(ERR_WALL, NULL, PARS_KO);
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

void	parsing_map()
{
	t_map	**map;

	map = get_map();
	check_char(*map);
	check_wall(*map);
	
	(void)map;
}
