# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/09 11:34:04 by pilespin          #+#    #+#              #
#    Updated: 2017/06/29 13:04:01 by asenat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean all

NAME	=	libft.a

SDIR	=	src/
HDIR	=	includes/
ODIR	=	obj/
FOLDER	=	-I $(HDIR)

ifeq ($(shell uname), Linux)
NBTHREADS	=`cat /proc/cpuinfo | grep processor | wc -l`
else ifeq ($(shell uname), Darwin)
NBTHREADS	=`sysctl -a | grep hw.logicalcpu: | cut -d ' ' -f 2`
else
NBTHREADS	= 1
endif
$(eval NBTHREADS=$(shell echo $$(($(NBTHREADS)*2))))

MAKE_OPTS_THREAD 	= -j$(NBTHREADS)

SRCA = ft_strlen.c \
	ft_strlen_char.c \
	ft_intlen.c ft_tablen.c \
	ft_strdup.c ft_strndup.c ft_strdupf.c ft_strrev.c \
	ft_strcpy.c ft_strncpy.c \
	ft_strcat.c	ft_strncat.c \
	ft_strchr.c ft_strrchr.c \
	ft_strstr.c ft_strnstr.c \
	ft_strcmp.c ft_strncmp.c \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isoctal.c \
	ft_toupper.c ft_tolower.c \
	ft_memalloc.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
	ft_memcmp.c \
	ft_strlcat.c \
	ft_memdel.c \
	ft_strclr.c \
	ft_strequ.c \
	ft_strnequ.c \
	ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
	ft_dprintf.c ft_printf.c \
	ft_putnchar.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_puttab.c ft_puttab3.c ft_puttabint.c ft_tabdup.c \
	ft_itoa.c ft_itoabig.c ft_itoaf.c ft_atoi.c ft_atoibig.c ft_atof.c \
	ft_strnew.c ft_strdel.c \
	ft_strsub.c \
	ft_strjoin.c ft_strjoinf.c ft_strjoin_max.c \
	ft_strtrim.c \
	ft_strsplit.c ft_strsplit_start.c ft_implode.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_sorttab.c ft_swapchar.c \
	ft_get_next_line.c \
	ft_freetabchar.c \
	ft_make_tabchar.c \
	ft_pow.c ft_sqrt.c ft_absint.c \
	ft_utime.c \
	ft_random.c \
	ft_putstrc.c ft_putcharc.c \
	ft_strdup_add_space.c ft_strdup_whitout_space.c \
	ft_count_char.c \
	ft_ispair.c \
	ft_isimpair.c \
	ft_replace_char.c \
	ft_doublearrayndel.c \
	ft_splitfilepath.c \
	ft_lstnew.c \
	ft_realloc.c \
	ft_lstadd.c \
	memalloc_or_die.c \

SRCH	=	libft.h \

SRCO	=	$(SRCA:.c=.o)

CC		=	gcc -g
LIB		=	-L ./libft/ -lft
FLAGS	=	-Wall -Wextra -Werror

MAKE_OPTS = --no-print-directory $(MAKE_OPTS_THREAD)

SRC 	=	$(patsubst %.c, $(SDIR)%.c, $(SRCA))
HDR		=	$(patsubst %.h, $(HDIR)%.h, $(SRCH))
OBJ		=	$(patsubst %.c, $(ODIR)%.o, $(SRCA))

all: compil

compil:
	@mkdir -p $(ODIR)
	@make $(NAME) $(MAKE_OPTS)

$(NAME): $(OBJ) $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[37m END $(NAME)\033[0m"

$(ODIR)%.o: $(SDIR)%.c $(HDR)
	@$(CC) -c $< -o $@ $(FLAGS) $(FOLDER)
	@echo "\033[32m ok \033[33m $@\033[0m"

clean:
	@rm -rf $(ODIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
