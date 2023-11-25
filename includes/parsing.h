/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:52:32 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/25 00:21:31 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PARSING_
#define _PARSING_

#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "cub.h"

void	parsing(int argc, char **argv);
void	parsing_map(char *path);

#endif
