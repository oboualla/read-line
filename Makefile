
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboualla <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 19:52:16 by oboualla          #+#    #+#              #
#    Updated: 2019/11/10 20:20:08 by oboualla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = src/arrow.c src/history2.c  src/deplacer_mot.c src/get_curpos.c src/history.c src/init_objet.c src/read_line.c src/reprint.c\
	  src/signal.c src/termcap.c src/other_key.c src/auto_complition/auto_completion.c src/auto_complition/complet_line.c\
	  src/auto_complition/couleur.c src/auto_complition/objet.c src/auto_complition/print_ac.c \
	  src/auto_complition/readpath.c get_next_line/get_next_line.c 

OBJ = arrow.o deplacer_mot.o history2.o get_curpos.o history.o init_objet.o \
	  read_line.o reprint.o signal.o termcap.o auto_completion.o complet_line.o \
	  couleur.o objet.o print_ac.o readpath.o get_next_line.o other_key.o

EXEC = readline.a

all : EXEC

EXEC :
	$(CC) $(CFLAGS) -c $(SRC)
	ar rc $(EXEC) $(OBJ)
	ranlib $(EXEC)

clean :
	rm $(OBJ)

fclean : clean
	rm $(EXEC)

re : fclean all
