/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audrye <audrye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:14:39 by ntardy            #+#    #+#             */
/*   Updated: 2023/12/11 19:29:46 by audrye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETTERS_H
# define GETTERS_H

# include <unistd.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

/*********************************/
/*            structs            */
/*********************************/
typedef struct s_pars_map	t_pars_map;
typedef struct s_color		t_color;
typedef struct s_textures	t_textures;
typedef struct s_garbage	t_garbage;
typedef struct s_fd			t_fd;
typedef struct s_player		t_player;
typedef struct s_data		t_data;
typedef struct s_ptr		t_ptr;
typedef float t_v2f __attribute__ ((vector_size (8)));

struct s_pars_map{
	char	*line;
	t_pars_map	*next;
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
	t_img	*no_img;
	t_img	*so_img;
	t_img	*we_img;
	t_img	*ea_img;
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

struct s_player{
	int		posX;
	int		posY;
	int		startDir;
	// double
} ;

struct s_data{
	char		**map;
	t_textures	*textures;
	t_player	player;
	t_ptr		*ptr;
} ;

struct s_ptr{
	void	*mlx;
	void	*win;
	t_img	*img;
} ;

struct s_maths{
	float	x;
	float	y;
} ;

/*********************************/
/*            getters            */
/*********************************/
t_pars_map		**get_pars_map(void);
t_textures		**get_textures(void);
t_garbage		**get_garbage(void);
t_fd			**get_fd(void);
t_data			**get_data(void);


#endif
