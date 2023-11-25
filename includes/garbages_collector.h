/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbages_collector.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:05:00 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/24 18:14:35 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _GARBAGES_COLLECTOR_
#define _GARBAGES_COLLECTOR_

#include <stdlib.h>
#include "errors.h"

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
void			collect_ptr();
void			garbage_collect();
void			tracked_free(void *ptr);
t_garbage		**get_garbage(void);

#endif
