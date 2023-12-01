/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_collector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:02:29 by ntardy            #+#    #+#             */
/*   Updated: 2023/12/01 02:13:37 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/collectors.h"

void	add_fd(int fd)
{
	t_fd		**fds;
	t_fd		*new;

	fds = get_fd();
	new = ft_calloc(sizeof(t_fd), 1);
	new->fd = fd;
	new->next = (*fds);
	(*fds) = new;
}

int	tracked_open(char *path, int arg)
{
	int	fd;

	if (!path)
		return (-1);
	fd = open(path, arg);
	if (fd == -1)
		return (-1);
	add_fd(fd);
	return (fd);
}

void	tracked_close(int fd)
{
	t_fd	**fds;
	t_fd	*current;
	t_fd	*prev ;


	fds = get_fd();
	current = *fds;
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				(*fds) = current->next;
            close(current->fd);
			tracked_free(current);
            break ;
		}
		prev = current;
		current = current->next;
	}
}

void	collect_fd(void)
{
	t_fd *fd_current;

	fd_current = *get_fd();
	while (fd_current)
	{
		close(fd_current->fd);
		fd_current = fd_current->next;
	}
	*get_fd() = NULL;
}