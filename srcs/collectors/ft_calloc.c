/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:11:22 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/30 21:32:06 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/collectors.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*cast_s;
	size_t			i;

	i = 0;
	cast_s = (unsigned char *)s;
	while (i < n)
	{
		cast_s[i] = c;
		i++;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	t_garbage		**garbages;
	t_garbage		*new;

	garbages = get_garbage();
	if (size != 0 && nmemb * size / size != nmemb)
		return (NULL);
	ptr = malloc(size * nmemb);
	if (!ptr)
		return (malloc_error(), NULL);
	new = malloc(sizeof(t_garbage));
	if (!new)
		return (free(ptr), malloc_error(), NULL);
	new->ptr = ptr;
	new->next = (*garbages);
	(*garbages) = new;
	ft_bzero(ptr, (size * nmemb));
	return (ptr);
}
