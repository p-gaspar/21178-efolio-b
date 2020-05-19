#
# UC: 21178 - Laboratório de Programação
# e-fólio B 2019-20 (makefile)
#
# Aluno: 1902551 - Pedro Gaspar
#

CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic

efolio: 
	gcc $(CFLAGS) -o ./output/efolio ./_shared/helpers.c ./_shared/vector.c ./canvas/canvas.c ./file-manager/file-manager.c ./file-manager/helpers.c ./ui/ui.c ./main.c 
