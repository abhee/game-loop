#build:
#	gcc -Wall -std=c99 ./src/*.c -I /opt/homebrew/include/SDL2 -D_THREAD_SAFE -L /opt/homebrew/lib -lSDL2 -o game

build:
	gcc -Wall -std=c99 ./src/*.c `sdl2-config --cflags --libs` -o game
	
run:
	./game

clean:
	rm game