/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:54:14 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/29 11:46:00 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	print_map(void)
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
	if (ft_strlen(new->line) > 1
		&& new->line[ft_strlen(new->line) - 1] == '\n')
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

int	is_wall_space(char c)
{
	if (c == '1' || c == ' ')
		return (1);
	return (0);
}

int	is_map_char(char c)
{
	if (c == '0')
		return (1);
	if (c == 'S' || c == 'N')
		return (1);
	if (c == 'E' || c == 'O')
		return (1);
	return (is_wall_space(c));
}

void	parsing_map(void)
{
	t_map	**map;

	map = get_map();
	if (!map || !(*map)->next || !(*map)->next->next)
		error(ERR_LITTLE_MAP, NULL, PARS_KO);
	check_char(*map);
	check_player(*map);
	check_wall(*map);
}
