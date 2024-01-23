# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 18:25:02 by ntardy            #+#    #+#              #
#    Updated: 2024/01/23 19:59:12 by ntardy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	cub3D
BONUS_NAME			=	cub3D_bonus
CC					=	gcc
LIB_MLX 			=	minilibx-linux

#*********************************#
#*             FLAGS             *#
#*********************************#
CFLAGS				=	-Wall -Werror -Wextra
VALGRIND_OPTIONS	=	--leak-check=full --show-leak-kinds=all --track-fds=yes

#*********************************#
#*      MANDATORY_PATH_FILES     *#
#*********************************#
MANDATORY_SRCS_PATH =		mandatory/srcs/
UTILS_PATH =	$(MANDATORY_SRCS_PATH)lib_util/
GNL_PATH =		$(MANDATORY_SRCS_PATH)GNL/
ERROR_PATH =	$(MANDATORY_SRCS_PATH)errors/
PARS_PATH =		$(MANDATORY_SRCS_PATH)parsing/
GARBAGE_PATH =	$(MANDATORY_SRCS_PATH)collectors/
GETTERS_PATH =	$(MANDATORY_SRCS_PATH)getters/
GAME_PATH =		$(MANDATORY_SRCS_PATH)game/
INCLUDE_PATH =	mandory/includes/

#*********************************#
#*        BONUS_PATH_FILES       *#
#*********************************#
BONUS_SRCS_PATH =		bonus/srcs/
BONUS_GAME_PATH =		$(BONUS_SRCS_PATH)game/
BONUS_PARS_PATH =		$(BONUS_SRCS_PATH)parsing/
BONUS_GETTERS_PATH =	$(BONUS_SRCS_PATH)getters/
BONUS_INCLUDE_PATH =	bonus/includes/

#*********************************#
#*             FILES             *#
#*********************************#
FILES_UTILS =	$(UTILS_PATH)ft_str.c				\
				$(UTILS_PATH)ft_str_malloc.c		\
				$(UTILS_PATH)ft_write.c				\
				$(UTILS_PATH)ft_atoi.c				\
				$(UTILS_PATH)ft_split.c				\
				$(UTILS_PATH)ft_lst.c				\
				$(GNL_PATH)get_next_line.c			\
				$(GNL_PATH)get_next_line_utils.c	\
				$(ERROR_PATH)errors.c

FILES_GARBAGE =	$(GARBAGE_PATH)fds_collector.c		\
				$(GARBAGE_PATH)garbages_collector.c	\
				$(GARBAGE_PATH)ft_calloc.c

FILES_PARS =	$(PARS_PATH)parsing.c				\
				$(PARS_PATH)parsing_map.c			\
				$(PARS_PATH)check_parsing_map.c		\
				$(PARS_PATH)check_parsing.c			\
				$(PARS_PATH)parsing_utils.c			\
				$(PARS_PATH)parsing_textures.c

FILES_GAME =	$(GAME_PATH)init_mlx.c				\
				$(GAME_PATH)exit.c					\
				$(GAME_PATH)mouv.c					\
				$(GAME_PATH)mouv_2.c				\
				$(GAME_PATH)display_screen_utils.c	\
				$(GAME_PATH)display_screen.c		\
				$(GAME_PATH)raycasting.c			\
				$(GETTERS_PATH)getters.c


SRCS =			$(MANDATORY_SRCS_PATH)cub.c			\
				$(FILES_PARS)						\
				$(FILES_GARBAGE)					\
				$(FILES_UTILS)						\
				$(FILES_GAME)

BONUS_FILES_PARS =	$(BONUS_PARS_PATH)parsing.c					\
					$(BONUS_PARS_PATH)parsing_map.c				\
					$(BONUS_PARS_PATH)check_parsing_map.c		\
					$(BONUS_PARS_PATH)check_parsing.c			\
					$(BONUS_PARS_PATH)parsing_utils.c			\
					$(BONUS_PARS_PATH)parsing_textures.c

BONUS_FILES_GAME =	$(BONUS_GAME_PATH)init_mlx.c				\
					$(BONUS_GAME_PATH)exit.c					\
					$(BONUS_GAME_PATH)mouv.c					\
					$(BONUS_GAME_PATH)mouv_2.c					\
					$(BONUS_GAME_PATH)display_screen_utils.c	\
					$(BONUS_GAME_PATH)display_screen_utils_2.c	\
					$(BONUS_GAME_PATH)display_screen.c			\
					$(BONUS_GAME_PATH)raycasting.c				\

BONUS_SRCS =		$(BONUS_SRCS_PATH)cub.c		\
					$(BONUS_GETTERS_PATH)getters.c\
					$(BONUS_FILES_PARS)			\
					$(FILES_GARBAGE)			\
					$(FILES_UTILS)				\
					$(BONUS_FILES_GAME)

OBJS =			$(SRCS:.c=.o)

BONUS_OBJS =	$(BONUS_SRCS:.c=.o)

MLX =	-L$(LIB_MLX) -lmlx_Linux -L/usr/lib -I$(LIB_MLX) -lXext -lX11 -lm -lz

# HEADER =		$(INCLUDE_PATH)cub.h				\
# 				$(INCLUDE_PATH)errors.h				\
# 				$(INCLUDE_PATH)collectors.h			\
# 				$(INCLUDE_PATH)get_next_line.h		\
# 				$(INCLUDE_PATH)getters.h			\
# 				$(INCLUDE_PATH)lib_utils.h			\
# 				$(INCLUDE_PATH)parsing.h			\
# 				$(INCLUDE_PATH)game.h				\
# 				$(LIB_MLX)/mlx.h

# BONUS_HEADER =	$(BONUS_INCLUDE_PATH)cub.h				\
# 				$(BONUS_INCLUDE_PATH)errors.h			\
# 				$(BONUS_INCLUDE_PATH)collectors.h		\
# 				$(BONUS_INCLUDE_PATH)get_next_line.h	\
# 				$(BONUS_INCLUDE_PATH)getters.h			\
# 				$(BONUS_INCLUDE_PATH)lib_utils.h		\
# 				$(BONUS_INCLUDE_PATH)parsing.h			\
# 				$(BONUS_INCLUDE_PATH)game.h				\

#*********************************#
#*            COLORS             *#
#*********************************#
RESET	= \033[0m
GREEN	= \033[32m
YELLOW	= \033[33m

#*********************************#
#*           TARGETS             *#
#*********************************#


$(NAME): $(OBJS)
	@echo "$(YELLOW)Compiling in progress...$(RESET)"
	@make -C $(LIB_MLX)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I $(INCLUDE_PATH) -I $(LIB_MLX) $(MLX)
	@echo "$(GREEN)------------------------$(RESET)"
	@echo "$(GREEN)$(NAME) is compile !$(RESET)"

$(BONUS_NAME): $(BONUS_OBJS)
	@echo "$(YELLOW)Compiling in progress...$(RESET)"
	@make -C $(LIB_MLX)
	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) -I $(BONUS_INCLUDE_PATH) -I $(LIB_MLX) $(MLX)
	@echo "$(GREEN)------------------------$(RESET)"
	@echo "$(GREEN)$(BONUS_NAME) is compile !$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -I/usr/include -I$(LIB_MLX) -Imlx_linux -c $< -o $@ -I $(INCLUDE_PATH)

#*********************************#
#*         PHONY TARGETS         *#
#*********************************#

.PHONY: all clean fclean re bonus

all: $(NAME)

bonus: $(BONUS_NAME)

clean:
	@echo "$(YELLOW)Removing object files...$(RESET)"
	@rm -f $(OBJS) $(BONUS_OBJS)
	@echo "$(GREEN)Object files removed.$(RESET)"

fclean: clean
	@echo "$(YELLOW)Removing the executable...$(RESET)"
	@rm -f $(NAME) $(BONUS_NAME)
	@echo "$(GREEN)Executable removed.$(RESET)"

re: fclean all

rebonus: fclean bonus
