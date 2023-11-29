/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:47:27 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/29 11:02:39 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	check_ext(char *path, char *ext)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		error(ERR_WRONG_EXT, ext, ARG_NOK);
	if (ft_strcmp(path + (len - ft_strlen(ext)), ext))
		error(ERR_WRONG_EXT, ext, ARG_NOK);
}

void	check_path(char *path)
{
	if (!path)
		error(ERR_PATH_NULL, NULL, ARG_NOK);
	check_ext(path, ".cub");
}

void	check_file(char *path, int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		error(path, ERR_OPEN_DIR, OPEN_KO);
	}
	*fd = open(path, O_RDONLY);
	if (*fd == -1)
		error(ERR_OPEN_KO, path, OPEN_KO);
}