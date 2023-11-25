/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:51:31 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/25 00:25:12 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "errors.h"

char	*get_next_line(int fd);
char	*ft_strcat_remake(char *next_line, char *buff);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup_remake(const char *src, char c);
int		ft_strlen_remake(const char *s, char c);

#endif
