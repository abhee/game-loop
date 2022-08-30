#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

int initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL");
		return FALSE;
	}

	return TRUE;
}

int main(int argc, char *argv[]) {
	initialize_window();
	return 0;
}
