# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 11:39:15 by ncotte            #+#    #+#              #
#    Updated: 2023/01/04 21:41:52 by shalimi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES		:=	utils/error.c		utils/str_to_d.c \
					items/color.c		items/light_ratio.c	items/double_length.c \
					items/coord.c		items/vector.c \
					objects/camera.c	objects/light.c		objects/amb_light.c \
					objects/plane.c		objects/sphere.c	objects/cylinder.c \
					init/parsing.c		init/read_file.c	init/init.c \
					main.c

SRCS_DIR		:= ./src/
SRCS			:= $(addprefix $(SRCS_DIR),$(SRCS_FILES))

OBJS_FILES		:= $(SRCS_FILES:.c=.o)
OBJS_DIR		:= ./bin/
OBJS_SUB_DIR	:= $(OBJS_DIR)objects $(OBJS_DIR)items $(OBJS_DIR)init $(OBJS_DIR)utils
OBJS			:= $(addprefix $(OBJS_DIR),$(OBJS_FILES))

LIBFT_DIR		:= ./libft/
LIBFT			:= -L $(LIBFT_DIR) -lft

MINILIBX_DIR	:= ./mlx/
MINILIBX		:= -L $(MINILIBX_DIR) -lmlx -framework OpenGL -framework AppKit

INC_DIR			:= ./inc/
INC				:= miniRT.h
HEADERS 		:= $(addprefix $(INC_DIR),$(INC))

CC				:= @gcc
CFLAGS			:= -g -Wall -Wextra -Werror -I $(INC_DIR)
DEBUG			:= -g3 -fsanitize=undefined

RM				:= @rm -f
UNIT			:= ""
TMP				:= .tmp.txt
NAME			:= miniRT


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
#				@echo $(BOLD_GREEN)"Compiling $<"$(RESET_COLOR)  #Ajout de la ligne pour afficher le pourcentage de compilation en couleur.
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

run:			$(NAME) norm
				./$(NAME)

leaks:			$(NAME)
				leaks -atExit -- ./$(NAME) scenes/test.rt

debug:			CFLAGS += $(DEBUG)
debug:			$(OBJS)
				@make -sC $(LIBFT_DIR) debug
				@make -sC $(MINILIBX_DIR) debug
				$(CC) $(CFLAGS) $(LIBFT) $(MINILIBX) -o $(NAME) $(OBJS)
				@echo $(BOLD_BLUE)[BUILD][$(NAME)]$(BOLD_YELLOW)[DEBUG]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

.PHONY:			all clean fclean re leaks run debug test unit norm
