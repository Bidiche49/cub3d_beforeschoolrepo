/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbages_collector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:03:54 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/29 10:38:48 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/garbages_collector.h"

t_garbage	**get_garbage(void)
{
	static t_garbage	*garbage = NULL;

	return (&garbage);
}

void	null_this_free(void *ptr)
{
	if (!ptr)
		return ;
	free(ptr);
	ptr = NULL;
}

void	tracked_free(void *ptr)
{
	t_garbage	**garbages;
	t_garbage	*current;
	t_garbage	*prev ;

	if (!ptr)
		return ;
	garbages = get_garbage();
	current = *garbages;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				(*garbages) = current->next;
			null_this_free(current->ptr);
			null_this_free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	garbage_collect(void)
{
	t_garbage	*current;
	t_garbage	*next;

	next = NULL;
	current = *get_garbage();
	while (current)
	{
		next = current->next;
		if (current->ptr)
		{
			free(current->ptr);
			current->ptr = NULL;
		}
		free(current);
		current = NULL;
		current = next;
	}
	*get_garbage() = NULL;
}
