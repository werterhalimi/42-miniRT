# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 11:39:15 by ncotte            #+#    #+#              #
#    Updated: 2023/02/21 16:17:48 by shalimi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES		:=	utils/error.c			utils/quit.c			utils/info.c \
					maths/point.c			maths/vector.c			maths/quad_solv.c \
					maths/matrix.c			maths/quake.c			maths/str_to_double.c \
					maths/trigo.c \
					objects/camera.c		objects/light.c			objects/amb_light.c \
					objects/plane.c			objects/sphere.c		objects/cylinder.c \
					objects/cone.c			objects/spot_light.c	objects/update_scene.c \
					intersect/intersect_light.c			intersect/intersect_plane.c \
					intersect/intersect_sphere.c		intersect/intersect_cylinder.c \
					intersect/intersect_cone.c			intersect/intersect_spot_light.c \
					intersect/find_intersect.c \
					print/color_trgb.c		print/put_pixel.c		print/phong.c \
					print/get_color.c		print/print_plane.c		print/print_cylinder.c \
					print/print_light.c		print/print_sphere.c	print/print_spot_light.c \
					print/print_cone.c		print/print_window.c \
					rotations/rotation.c				rotations/rotation_camera.c \
					rotations/rotation_plane.c			rotations/rotation_cylinder.c \
					rotations/rotation_cone.c			rotations/rotation_spot_light.c \
					translations/translation.c			translations/translation_camera.c \
					translations/translation_light.c	translations/translation_sphere.c \
					translations/translation_plane.c	translations/translation_cylinder.c \
					translations/translation_cone.c		translations/translation_spot_light.c \
					hooks/is_key.c			hooks/mouse_hook.c		hooks/key_hook.c \
					hooks/release.c \
					start/next_item.c		start/parse_color.c		start/parse_coord.c \
					start/parse_vector.c	start/parse_ratio.c		start/parse_length.c \
					start/parse_angle.c		start/parse_integer.c	start/parse_texture.c \
					start/parse_bonus.c		start/parse_camera.c	start/parse_amb_light.c \
					start/parse_plane.c		start/parse_light.c		start/parse_spot_light.c \
					start/parse_sphere.c	start/parse_cone.c		start/parse_cylinder.c \
					start/parse_header.c	start/read_file.c		start/init.c \
					main.c

SRCS_DIR		:=	./src/
SRCS			:=	$(addprefix $(SRCS_DIR),$(SRCS_FILES))

OBJS_FILES		:=	$(SRCS_FILES:.c=.o)
OBJS_DIR		:=	./bin/
OBJS_SUB_DIR	:= 	$(OBJS_DIR)objects	$(OBJS_DIR)maths	$(OBJS_DIR)rotations \
					$(OBJS_DIR)start	$(OBJS_DIR)utils	$(OBJS_DIR)translations \
					$(OBJS_DIR)print	$(OBJS_DIR)hooks	$(OBJS_DIR)intersect
OBJS			:=	$(addprefix $(OBJS_DIR),$(OBJS_FILES))

LIBFT_DIR		:=	./libft/
LIBFT			:=	-L $(LIBFT_DIR) -lft

MINILIBX_DIR	:=	./mlx/
MINILIBX		:=	-L $(MINILIBX_DIR) -lmlx -framework OpenGL -framework AppKit

INC_DIR			:=	./inc/
INC				:=	miniRT.h	hooks.h
HEADERS 		:=	$(addprefix $(INC_DIR),$(INC))

CC				:=	@gcc
CFLAGS			:=	-g -Wall -Wextra -Werror -I $(INC_DIR)
DEBUG			:=	-g3 -fsanitize=undefined

RM				:=	@rm -f
UNIT			:=	""
TMP				:=	.tmp.txt
NAME			:=	miniRT


RESET_COLOR		:=	"\033[0m"

BLACK			:=	"\033[0;30m"
RED				:=	"\033[0;31m"
GREEN			:=	"\033[0;32m"
YELLOW			:=	"\033[0;33m"
BLUE			:=	"\033[0;34m"
MAGENTA			:=	"\033[0;35m"
CYAN			:=	"\033[0;36m"
WHITE			:=	"\033[0;37m"

BOLD_BLACK		:=	"\033[1;30m"
BOLD_RED		:=	"\033[1;31m"
BOLD_GREEN		:=	"\033[1;32m"
BOLD_YELLOW		:=	"\033[1;33m"
BOLD_BLUE		:=	"\033[1;34m"
BOLD_MAGENTA	:=	"\033[1;35m"
BOLD_CYAN		:=	"\033[1;36m"
BOLD_WHITE		:=	"\033[1;37m"


all:			$(NAME)

${OBJS_DIR}%.o:	${SRCS_DIR}%.c $(HEADERS)
				@mkdir -p $(OBJS_DIR) $(OBJS_SUB_DIR)
				$(CC) $(UNIT) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS)
				@make -sC $(LIBFT_DIR) all
				@make -sC $(MINILIBX_DIR) all
				$(CC) $(CFLAGS) $(LIBFT) $(MINILIBX) -o $(NAME) $(OBJS)
				@echo $(BOLD_BLUE)[BUILD][$(NAME)]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

unit:			clean		
				echo salut
				make UNIT="-D UNIT"

sclean:
				$(RM) $(OBJS)
				$(RM) -r $(OBJS_SUB_DIR) $(OBJS_DIR)

clean:			sclean
				@make -sC $(LIBFT_DIR) clean
				@make -sC $(MINILIBX_DIR) clean
				@echo $(BOLD_BLUE)[CLEAN][$(NAME)]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

fclean:			sclean
				$(RM) $(NAME)
				@make -sC $(LIBFT_DIR) fclean
				@make -sC $(MINILIBX_DIR) fclean
				@echo $(BOLD_BLUE)[FCLEAN][$(NAME)]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

re:				fclean $(NAME)

norm:
				@make -sC $(LIBFT_DIR) norm
				@echo $(BOLD_BLUE)[NORM][mlx]$(BOLD_YELLOW)" : IGNORED"$(RESET_COLOR)
				@norminette $(SRCS_DIR) $(INC_DIR) | \
					(! grep -E -B 1 "(^Warning|^Error)" &> $(TMP)) && \
					echo $(BOLD_BLUE)[NORM][$(NAME)]$(BOLD_GREEN)" : OK!"$(RESET_COLOR) || \
					(echo $(BOLD_BLUE)[NORM][$(NAME)]$(BOLD_RED)" : KO!"$(RESET_COLOR) ; \
					cat $(TMP) | sed -e "s/^/    /g")
				$(RM) $(TMP)

run:			$(NAME)
				./$(NAME) scenes/valid.rt

leaks:			$(NAME) norm
				leaks -atExit -- ./$(NAME) scenes/valid.rt

debug:			CFLAGS += $(DEBUG)
debug:			$(OBJS)
				@make -sC $(LIBFT_DIR) debug
				@make -sC $(MINILIBX_DIR) debug
				$(CC) $(CFLAGS) $(LIBFT) $(MINILIBX) -o $(NAME) $(OBJS)
				@echo $(BOLD_BLUE)[BUILD][$(NAME)]$(BOLD_YELLOW)[DEBUG]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

.PHONY:			all clean fclean re leaks run debug test unit norm
