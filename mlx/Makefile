#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
SRC+= mlx_png.c mlx_mouse.m
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2
CFLAGS+=-w

# add to match string put with X11 in size and position
CFLAGS+= -DSTRINGPUTX11

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

all: $(NOM)

$(NOM):	$(OBJ)
	ar -r $(NOM) $(OBJ)
	ranlib $(NOM)
	@echo $(BOLD_BLUE)[BUILD][$(NOM)]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

sclean:
	rm -f $(NOM) $(OBJ) *~
	rm -f mlx_app

clean:	sclean
	@echo $(BOLD_BLUE)[CLEAN][$(NOM)]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

fclean:	sclean
	rm -f libmlx.a
	@echo $(BOLD_BLUE)[FCLEAN][$(NOM)]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

debug:	CFLAGS += -g3 -fsanitize=address
debug:	$(OBJ)
	ar -r $(NOM) $(OBJ)
	ranlib $(NOM)
	@echo $(BOLD_BLUE)[BUILD][$(NOM)]$(BOLD_YELLOW)[DEBUG]$(BOLD_GREEN)" : DONE"$(RESET_COLOR)

re: clean all
