# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboualla <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/31 20:59:16 by oboualla          #+#    #+#              #
#    Updated: 2019/11/07 00:31:30 by oboualla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a 

CC = gcc -Wall -Wextra -Werror

rm = rm -rf

src =	ft_atoi.c ft_bzero.c ft_change_chr_to_nwchr.c\
		ft_count_char.c ft_count_to_find.c ft_count_word.c\
		free_double.c ft_is_separ.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c\
		ft_itoa.c ft_lstadd.c ft_lstdel.c\
		ft_lstdelone.c ft_lstiter.c ft_lstmap.c\
		ft_lstnew.c ft_memalloc.c ft_memccpy.c\
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c\
		ft_memmove.c ft_memset.c ft_new_lst.c \
		ft_putchar.c ft_putchar_fd.c ft_putendl.c \
		ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
		ft_putstr.c ft_putstr_fd.c ft_rev.c \
		ft_reverse.c ft_skip_lensep.c ft_skip_sep.c \
		ft_sqrt.c ft_strcat.c ft_strccpy.c \
		ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c \
		ft_strdel.c ft_strdup.c ft_strequ.c \
		ft_striter.c ft_striteri.c ft_strjoin.c \
		ft_strlcat.c ft_strlen.c ft_strmap.c \
		ft_strmapi.c ft_strncat.c ft_getchr.c ft_strncmp.c ft_strccmp.c\
		ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c \
		ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c \
		ft_strtrim.c ft_tolower.c ft_toupper.c ft_wordlen.c ft_remplacer_str.c ft_strcdup.c ft_strndup.c

obj = ft_atoi.o ft_bzero.o ft_change_chr_to_nwchr.o ft_getchr.o\
	  ft_count_char.o ft_count_to_find.o ft_count_word.o ft_strndup.o\
	  ft_is_separ.o ft_isalnum.o ft_isalpha.o \
	  free_double.o ft_isascii.o ft_isdigit.o ft_isprint.o\
	  ft_itoa.o ft_lstadd.o ft_lstdel.o ft_strccmp.o\
	  ft_lstdelone.o ft_lstiter.o ft_lstmap.o\
	  ft_lstnew.o ft_memalloc.o ft_memccpy.o\
	  ft_memchr.o ft_memcmp.o ft_memcpy.o ft_memdel.o\
	  ft_memmove.o ft_memset.o ft_new_lst.o \
	  ft_putchar.o ft_putchar_fd.o ft_putendl.o \
	  ft_putendl_fd.o ft_putnbr.o ft_putnbr_fd.o \
	  ft_putstr.o ft_putstr_fd.o ft_rev.o \
	  ft_reverse.o ft_skip_lensep.o ft_skip_sep.o \
	  ft_sqrt.o ft_strcat.o ft_strccpy.o \
	  ft_strchr.o ft_strclr.o ft_strcmp.o ft_strcpy.o \
	  ft_strdel.o ft_strdup.o ft_strequ.o \
	  ft_striter.o ft_striteri.o ft_strjoin.o \
	  ft_strlcat.o ft_strlen.o ft_strmap.o \
	  ft_strmapi.o ft_strncat.o   ft_strncmp.o \
	  ft_strncpy.o ft_strnequ.o ft_strnew.o ft_strnstr.o \
	  ft_strrchr.o ft_strsplit.o ft_strstr.o ft_strsub.o \
	  ft_strtrim.o ft_tolower.o ft_toupper.o ft_wordlen.o ft_remplacer_str.o ft_strcdup.o

all : $(NAME)

$(NAME) : 
	$(CC) -c $(src) -Iincludes
	ar rc $(NAME) $(obj)

clean :
	$(rm) *.o

fclean : clean
	$(rm) $(NAME)

re : fclean all

