/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:32:45 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/25 01:42:34 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib_utils.h"

char	*get_first_word(char *str)
{
	char	*first_word;
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	first_word = ft_calloc((i + 1), sizeof(char));
	if (first_word == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		first_word[i] = str[i];
		i++;
	}
	return (first_word);
}

char	*ft_strdup(char *src)
{
	unsigned int	i;
	char			*str;

	i = -1;
	if (!src)
		return (NULL);
	str = ft_calloc((ft_strlen(src) + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (src[++i])
		str[i] = src[i];
	return (str);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int		i;
	int		y;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	str = ft_calloc((len + 1), sizeof (char));
	if (!str)
		return (NULL);
	i = 0;
	y = 0;
	while (s[i])
	{
		if (i >= start && y < len)
		{
			str[y++] = s[i];
		}
		i++;
	}
	str[y] = '\0';
	return (str);
}
