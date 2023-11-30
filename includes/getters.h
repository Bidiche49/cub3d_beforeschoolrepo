/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:14:39 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/30 21:52:57 by ntardy           ###   ########.fr       */
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
typedef struct s_garbage	t_garbage;
typedef struct s_fd			t_fd;

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

struct s_garbage{
	void		*ptr;
	t_garbage	*next;
} ;

struct s_fd{
	int		fd;
	t_fd	*next;
} ;

/*********************************/
/*            getters            */
/*********************************/
t_map		**get_map(void);
t_textures	**get_textures(void);
t_garbage	**get_garbage(void);
t_fd		**get_fd(void);

#endif
