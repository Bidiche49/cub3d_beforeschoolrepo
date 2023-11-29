/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:52:32 by ntardy            #+#    #+#             */
/*   Updated: 2023/11/29 11:12:05 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "lib_utils.h"

/*********************************/
/*          error logs           */
/*********************************/
# define ERR_WRONG_ARG "you must enter 1 argument (map path)"
# define ERR_PATH_NULL "path can't be null"
# define ERR_WRONG_EXT " wrong extension, must be "
# define ERR_OPEN_KO "unable to open the file, please check the path "
# define ERR_OPEN_DIR " is a directory, enter a map path"
# define ERR_MALLOC_KO "malloc KO"
# define ERR_PATTERN_FILE "pattern of the map not respected"
# define ERR_MAP_EMPTY "the map is empty or partially empty"
# define ERR_LINE_EMPTY "the map mustn't have empty line"
# define ERR_LITTLE_MAP "the map must have more than 2 line minimum"
# define ERR_FORBID_CHAR "forbidden char in the map"
# define ERR_WALL "wall must be close"
# define ERR_RGB "the colour of the floor/ceiling must comply with the rgb \
pattern (0-255,0-255,0-255)"

/*********************************/
/*          error code           */
/*********************************/
# define MALL_KO 55
# define OPEN_KO 10
# define PARS_KO 3
# define ARG_NOK 3

/*********************************/
/*           functions           */
/*********************************/
void	error(char *arg1, char *arg2, int err_code);
void	malloc_error(void);

#endif
