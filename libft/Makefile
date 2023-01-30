# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 11:39:15 by ncotte            #+#    #+#              #
#    Updated: 2023/01/23 13:19:12 by ncotte           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_alloc.c \
					ft_atoi.c		ft_bzero.c		ft_calloc.c \
					ft_isalnum.c	ft_isalpha.c	ft_isascii.c \
					ft_isdigit.c	ft_isprint.c	ft_itoa.c \
					ft_memchr.c		ft_memcmp.c		ft_memcpy.c \
					ft_memmove.c	ft_memset.c		ft_putchar_fd.c \
					ft_putendl_fd.c	ft_putnbr_fd.c	ft_putstr_fd.c \
					ft_split.c		ft_strchr.c		ft_strdup.c \
					ft_striteri.c	ft_strjoin.c	ft_strlcat.c \
					ft_strlcpy.c	ft_strlen.c		ft_strmapi.c \
					ft_strncmp.c	ft_strnstr.c	ft_strrchr.c \
					ft_strtrim.c	ft_substr.c		ft_tolower.c \
					ft_toupper.c \
					ft_lstadd_back.c	ft_lstadd_front.c	ft_lstclear.c \
					ft_lstdelone.c		ft_lstiter.c		ft_lstlast.c \
					ft_lstmap.c			ft_lstnew.c			ft_lstsize.c \
					 \
					ft_printf.c		malloc_nbr.c		malloc_char.c \
					t_str.c			ft_uitoa.c			ft_hextoa.c \
					 \
					get_next_line_bonus.c	get_next_line_utils_bonus.c

OBJS			= $(SRCS:.c=.o)

TEST			= libft_test

CC				= @gcc
CFLAGS			= -Wall -Wextra -Werror -I.
RM				= @rm -f
LIB				= @ar rcs
DEBUG			= -g3 -fsanitize=undefined
TMP				= .tmp.txt
NAME			= libft.a

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

.c.o:			
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS)
				$(LIB) $(NAME) $(OBJS)
				@echo $(BOLD_BLUE)[BUILD][$(NAME)]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

sclean:
				$(RM) $(OBJS)

clean:			sclean
				@echo $(BOLD_BLUE)[CLEAN][$(NAME)]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

fclean:			sclean
				$(RM) $(NAME) $(TEST)
				@echo $(BOLD_BLUE)[FCLEAN][$(NAME)]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

re:				fclean $(NAME)

norm:
				@norminette $(SRCS_DIR) $(INC_DIR) | \
					(! grep -E -B 1 "(^Warning|^Error)" &> $(TMP)) && \
					echo $(BOLD_BLUE)[NORM][$(NAME)]$(BOLD_GREEN)" : OK!"$(RESET_COLOR) || \
					(echo $(BOLD_BLUE)[NORM][$(NAME)]$(BOLD_RED)" : KO!"$(RESET_COLOR) ; \
					cat $(TMP) | sed -e "s/^/    /g")
				$(RM) $(TMP)

test:			all norm
				$(CC) $(CFLAGS) -L. -lft -o $(TEST) main.c $(DEBUG)

leaks:			test
				leaks -atExit -- ./$(TEST)

debug:			CFLAGS += $(DEBUG)
debug:			$(OBJS)
				$(LIB) $(NAME) $(OBJS)
				@echo $(BOLD_BLUE)[BUILD][$(NAME)]$(BOLD_YELLOW)[DEBUG]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

.PHONY:			all clean fclean re test debug leaks norm
