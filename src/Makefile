CC = gcc
CFLAGS = -Wall \
		-ansi \
		-pedantic
EXE = game

OFILES = coordinate.o \
		image.o \
		window.o \
		board.o \
		generator.o \
		game.o \
		ui.o \
		game_view.o \
		main_view.o \
		size_view.o \
		image_view.o \
		score_view.o \
		score.o \
		main.o
	
${EXE} : ${OFILES}
	$(CC) $(CFLAGS) -o ${EXE} ${OFILES} -lgraph &&\
	cp -f game ../TaquinGame/game


main.o : main.c window.h coordinate.h image.h board.h generator.h main.c		
	$(CC) -c main.c -lgraph
image.o : image.c coordinate.h image.h image.c
	$(CC) -c image.c
coordinate.o : coordinate.c coordinate.h coordinate.c
	$(CC) -c coordinate.c
window.o : window.c coordinate.h window.h window.c
	$(CC) -c window.c -lgraph
board.o : board.c coordinate.h image.h board.h board.c
	$(CC) -c board.c -lgraph
generator.o : generator.c coordinate.h generator.h
	$(CC) -c generator.c
game.o : game.c game.h coordinate.h image.h
	$(CC) -c game.c
ui.o : ui.c ui.h coordinate.h
	$(CC) -c ui.c
game_view.o : game_view.c views.h board.h coordinate.h window.h ui.h generator.h
	$(CC) -c game_view.c
main_view.o : main_view.c views.h board.h coordinate.h window.h ui.h
	$(CC) -c main_view.c
size_view.o : size_view.c views.h board.h coordinate.h window.h ui.h
	$(CC) -c size_view.c
image_view.o : image_view.c views.h board.h coordinate.h window.h ui.h
	$(CC) -c image_view.c
score_view.o : score_view.c views.h board.h coordinate.h window.h ui.h
	$(CC) -c score_view.c
score.o : score.c score.h
	$(CC) -c score.c

	
clean : 
	-rm -f ${OFILES}
	-rm -f ${EXE}


	
