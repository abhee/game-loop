#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "./constants.h"

bool is_game_running = false;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

struct object {
    float x;
    float y;
    float width;
    float height;
} ball;

bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    window = SDL_CreateWindow (
            NULL, 
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_METAL
            );

    // Don't proceed if window can not be created
    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }

    // Renderer needs a window to attach
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }

    return true;
}

void setup() {
    ball.x = 20;
    ball.y = 20;
    ball.width = 15;
    ball.height = 15;
}

void process_input() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type) {
		case SDL_QUIT:
		    is_game_running = false;
		    break;
		case SDL_KEYDOWN:
		    if ((event.key.keysym.sym == SDLK_ESCAPE) || (event.key.keysym.sym == SDLK_q))
		    	is_game_running = false;
		    break;
	}
}

void update() {
    ball.x += 1;
    ball.y += 1;
}

void render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw a rectangle
    SDL_Rect ball_rect = {
        ball.x, ball.y, ball.width, ball.height
    };

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &ball_rect);


    // Render the rntire scene
    SDL_RenderPresent(renderer);
}

void destroy_window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char *argv[]) {
    is_game_running = initialize_window();
    setup();


    /* Game loop is similar to REPL */
    while(is_game_running) {
    	process_input();
    	update();
    	render();
    }

    destroy_window();

    return 0;
}
