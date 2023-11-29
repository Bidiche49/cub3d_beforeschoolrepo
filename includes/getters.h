/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:14:39 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/29 10:16:54 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETTERS_H
# define GETTERS_H

# include <unistd.h>

/*********************************/
/*            structs            */
/*********************************/
typedef struct s_map		t_map;
typedef struct s_color		t_color;
typedef struct s_textures	t_textures;

struct s_map{
	char	*line;
	t_map	*next;
} ;

struct s_color{
	int	r;
	int	g;
	int	b;
} ;

struct s_textures{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	t_color	*floor;
	t_color	*ceiling;
} ;

/*********************************/
/*            getters            */
/*********************************/
t_map		**get_map(void);
t_textures	**get_textures(void);

#endif
