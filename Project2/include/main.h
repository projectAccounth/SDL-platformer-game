#pragma once

#include "SDL_handler.h"

typedef struct {
	int x, y;
	SDL_Texture* sprite;
} Player;

// main class of this game
class Main {
private:
	SDL_Window* mainwindow = NULL;
	SDL_Renderer* renderer = NULL;
	Player* player = new Player { 5, 6, NULL };

	const int xCap = 20;

	const int GRAVITY = 1;

	int speed_x = 0, speed_y = 0;
public:
	
	// window creation function
	void createWindow() {

		SDL_Init(SDL_INIT_EVERYTHING);
		// Assigning a value to the window
		mainwindow = SDL_CreateWindow("Main", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
		// defining the renderer
		renderer = SDL_CreateRenderer(mainwindow, -1, SDL_RENDERER_PRESENTVSYNC);
		// give the window a color
		SDL_SetRenderDrawColor(renderer, 60, 80, 80, 255);

		SDL_Texture* texture = NULL;

		player->x = WIDTH / 2;
		player->y = HEIGHT / 2;

		speed_x = 0, speed_y = 0;
	}

	SDL_Texture* createPlayer() {
		// loading image
		SDL_Surface* playerimg = IMG_Load("res/player.png");

		if (playerimg) {
			player->sprite = SDL_CreateTextureFromSurface(renderer, playerimg);

			SDL_FreeSurface(playerimg);
		}
		else {
			SDL_Log(SDL_GetError());
		}
		return player->sprite;
	}
	
	// controls for the player
	void controls() {
		const Uint8* keyState = SDL_GetKeyboardState(NULL);

		if (keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_A]) {
			speed_x -= 12;
		}
		if (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_D]) {
			speed_x += 12;
		}
		if (keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_W]) {
			speed_y = -15;
		}
	}

	// updating the player's state
	void update() {

		speed_y += GRAVITY;
		player->y += speed_y;


		if (player->x < 0) {
			player->x = 0;
		}
		else if (player->x >= WIDTH - SPRITE_SIZE) {
			player->x = WIDTH - SPRITE_SIZE;
		}
		if (player->y < 0) {
			player->y = 0;
		}
		else if (player->y >= HEIGHT - SPRITE_SIZE) {
			player->y = HEIGHT - SPRITE_SIZE;
			speed_y = 0;
		}
		
	}
	// function to render stuff
	void renderWindow() {
		player->sprite = createPlayer();
		
		SDL_Rect playerRect;

		SDL_RenderClear(renderer);

		// assigning values to the rectangle
		playerRect.x = player->x;
		playerRect.y = player->y;
		playerRect.w = 32;
		playerRect.h = 32;

		SDL_RenderCopy(renderer, player->sprite, NULL, &playerRect);
		SDL_RenderPresent(renderer);
	}

	// the boolean, also the function responsible for the events
	bool processEvent() {
		SDL_Event event;
		bool isRunning = true;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_WINDOWEVENT_CLOSE: {
				isRunning = false;
			}
			break;
			case SDL_QUIT:
				isRunning = false;
				break;
			}

			controls();
		}
		
		return isRunning;
	}

	// this function will be ran when we quit the program
	void onQuit() {
		SDL_DestroyWindow(mainwindow);
		SDL_DestroyRenderer(renderer);
		//SDL_DestroyTexture(player->sprite);
		SDL_Quit();
	}
};
