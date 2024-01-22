/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:14:39 by ntardy            #+#    #+#             */
/*   Updated: 2024/01/22 17:36:17 by ntardy           ###   ########.fr       */
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
typedef struct s_face		t_face;
typedef struct s_extra		t_extra;

struct s_pars_map{
	char		*line;
	t_pars_map	*next;
} ;

struct s_color{
	int	r;
	int	g;
	int	b;
} ;

struct s_textures{
	char	*no_path;
	char	*nos_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	t_img	*no_img;
	t_img	*nos_img;
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
	float		posx;
	float		posy;
	float		dir;
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

struct s_face{
	int		start_wall_height;
	int		end_wall_height;
	float	start_wall_width;
	int		wall_width;
	float	pos_wall_x;
	float	pos_wall_y;
	float	old_dist;
	float	dist;
	int		wall_start;
	int		wall_end;
	int		card;
} ;

struct s_extra{
	float		start_rot;
	float		dir;
	float		off_rot;
	float		current_angle;
	float		deviation_angle;
	float		dir_x;
	float		dir_y;
	float		pos_wall_x;
	float		pos_wall_y;
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
