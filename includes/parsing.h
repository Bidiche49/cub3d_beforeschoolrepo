/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:52:32 by ntardy            #+#    #+#             */
/*   Updated: 2023/12/06 13:17:56 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "get_next_line.h"
# include "getters.h"
# include "cub.h"

void	parsing(int argc, char **argv);
void	parsing_map(void);
void	print_data(void);/////A ENLEVER!!
void	fill_map(char *line);

void	check_ext(char *path, char *ext);
void	check_path(char *path);
void	check_file(char *path, int *fd);
void	check_line_texture(char *line);
void	check_wall(t_pars_map *map);
void	check_char(t_pars_map *map);
void	check_player(t_pars_map *map);
int		textures_is_empty(int ref);
int		is_wall_space(char c);
int     is_player(char c);
int		is_map_char(char c);
char	**cast_map(void);

#endif
