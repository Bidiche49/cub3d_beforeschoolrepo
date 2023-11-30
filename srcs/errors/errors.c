/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:28:17 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/30 22:32:21 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/errors.h"

void	error(char *arg1, char *arg2, int err_code)
{
	ft_putstrfd("Error: ", 2);
	ft_putstrfd(arg1, 2);
	if (arg2)
		ft_putstrfd(arg2, 2);
	ft_putcharfd('\n', 2);
	collect_fd();
	garbage_collect();
	exit(err_code);
}

void	malloc_error(void)
{
	error(ERR_MALLOC_KO, NULL, MALL_KO);
}
