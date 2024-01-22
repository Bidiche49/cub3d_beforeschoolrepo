/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:50:17 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/25 00:39:47 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib_utils.h"

void	ft_putcharfd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstrfd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str && str[i])
		ft_putcharfd(str[i++], fd);
}
