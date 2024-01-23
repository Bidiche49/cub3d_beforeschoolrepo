/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:04:39 by ntardy            #+#    #+#             */
/*   Updated: 2024/01/23 19:00:14 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTORS_H
# define COLLECTORS_H

# include <stdlib.h>
# include "errors.h"
# include "getters.h"

/*********************************/
/*          functions            */
/*********************************/
void			garbage_collect(void);
void			tracked_free(void *ptr);
void			collect_fd(void);
void			tracked_close(int fd);
int				tracked_open(char *str, int arg);

typedef enum s_cardinal{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	DOOR
}	t_cardinal;

#endif
