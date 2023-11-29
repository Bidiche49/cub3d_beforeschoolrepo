/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbages_collector.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:05:00 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/29 10:16:10 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGES_COLLECTOR_H
# define GARBAGES_COLLECTOR_H

# include <stdlib.h>
# include "errors.h"

/*********************************/
/*            struct             */
/*********************************/
typedef struct s_garbage	t_garbage;

struct s_garbage{
	void		*ptr;
	t_garbage	*next;
} ;

/*********************************/
/*          functions            */
/*********************************/
void			collect_ptr(void);
void			garbage_collect(void);
void			tracked_free(void *ptr);
t_garbage		**get_garbage(void);

#endif
