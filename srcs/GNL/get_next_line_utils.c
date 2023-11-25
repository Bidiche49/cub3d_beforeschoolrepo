/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:53:03 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/25 01:03:03 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

int	ft_strlen_remake(const char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c && c == '\n')
		return (i + 1);
	return (i);
}

char	*ft_strdup_remake(const char *src, char c)
{
	unsigned int	i;
	char			*dest;

	dest = NULL;
	i = -1;
	if (!src)
		return (NULL);
	dest = ft_calloc(sizeof(char), (ft_strlen_remake(src, c) + 1));
	if (dest == NULL)
		return (NULL);
	while (src[++i] && src[i] != c)
		dest[i] = src[i];
	if (src[i] == c && c == '\n')
		dest[i] = '\0';
	return (dest);
}

char	*ft_strcat_remake(char *next_line, char *buff)
{
	int		i;
	int		j;
	char	*line_tmp;

	i = 0;
	j = 0;
	line_tmp = ft_strdup_remake(next_line, '\0');
	tracked_free(next_line);
	next_line = ft_calloc(sizeof(char), (ft_strlen_remake(line_tmp, '\0')
				+ ft_strlen_remake(buff, '\n') + 1));
	if (!next_line)
		return (0);
	while (line_tmp && line_tmp[i])
		next_line[i++] = line_tmp[j++];
	j = 0;
	while (buff[j] && buff[j] != '\n')
		next_line[i++] = buff[j++];
	if (buff[j] == '\n')
		next_line[i] = '\n';
	tracked_free(line_tmp);
	return (next_line);
}
