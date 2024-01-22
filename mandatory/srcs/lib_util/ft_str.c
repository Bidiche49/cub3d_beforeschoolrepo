/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:50:17 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/29 10:42:34 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib_utils.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}
