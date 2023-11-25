/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:33:42 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/25 01:48:05 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib_utils.h"

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (is_num(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

