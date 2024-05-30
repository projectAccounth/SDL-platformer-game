#pragma once

#include "SDL_handler.h"

typedef struct {
	int x, y;
	SDL_Texture* sprite;
} Player;

//vars
SDL_Window* mainwindow = NULL;
SDL_Renderer* renderer = NULL;
Player* player = new Player{ 5, 6, NULL };

const int xCap = 20;

const int GRAVITY = 1;

float speed_x = 0, speed_y = 0;

int fullscreen = 0;
// end comment

// main class of this game
class Main {
private:
	SDL_Color fontColor = { 255,255,255 };
	SDL_Rect ground1 = {0,380,640,100};
	SDL_Rect ground2 = { 640-32-80,340,80,40 };
	bool isJumping = false;
public:
	// window creation function
	void createWindow() {

		SDL_Init(SDL_INIT_EVERYTHING);

		isJumping = false;
		// Assigning a value to the window
		mainwindow = SDL_CreateWindow("Main", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

		SDL_SetWindowFullscreen(mainwindow, 0);
		// defining the renderer
		renderer = SDL_CreateRenderer(mainwindow, -1, SDL_RENDERER_PRESENTVSYNC);
		
		player->x = WIDTH / 2;
		player->y = HEIGHT / 2;

		speed_x = 0, speed_y = 0;

		fullscreen = 0;
	}

	SDL_Texture *createFPSText() {
		TTF_Init();

		TTF_Font* SegoeUI = TTF_OpenFont("res/fonts/segoeui.ttf", 25);
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(SegoeUI, "lololol", fontColor);

		SDL_Texture* FPSCounter = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_FreeSurface(surfaceMessage);

		return FPSCounter;
	}

	void renderFPSText() {
		SDL_Texture* FPSCounter = createFPSText();
		SDL_Rect Message_rect; //create a rect
		Message_rect.x = 0;  //controls the rect's x coordinate 
		Message_rect.y = 0; // controls the rect's y coordinte
		Message_rect.w = 100; // controls the width of the rect
		Message_rect.h = 100;

		SDL_RenderCopy(renderer, FPSCounter, NULL, &Message_rect);

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
				speed_x -= 3;
				if (speed_x <= -xCap)
					speed_x = -xCap;
		}
		if (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_D]) {
				speed_x += 3;
				if (speed_x >= xCap)
					speed_x = xCap;
		}
		if (keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_W]) {
			if (!isJumping) {
				speed_y = -15;
				if (speed_y < 0) {
					isJumping = true;
				}
			}
			else if (isJumping) {}
		}
		if (keyState[SDL_SCANCODE_F11]) {
			if (SDL_PRESSED) {
				if (fullscreen == 0) {
					SDL_SetWindowFullscreen(mainwindow, SDL_WINDOW_FULLSCREEN);
					fullscreen = 1;
				}
				else {
					SDL_SetWindowFullscreen(mainwindow, 0);
					fullscreen = 0;
				}
			}
		}
	}

	void gameGrav() {
		speed_y += GRAVITY;
		player->y += speed_y;

		speed_x *= 0.7;
		player->x += speed_x;
	}

	void debugLoop() {
		sleep_for(milliseconds(100));
		cout << "\n";
		cout << "speedx: " << speed_x << endl;
		cout << "speedy: " << speed_y << endl;
		cout << "isjumping: " << isJumping << endl;
	}

	// updating the player's state
	void update() {
		SDL_Rect playerRect = playerRectCre();

		SDL_bool collision = SDL_HasIntersection(&ground1, &playerRect);
		SDL_bool collision1 = SDL_HasIntersection(&ground2, &playerRect);

		if (collision) {
			player->y = HEIGHT - ground1.h - SPRITE_SIZE;
			speed_y = 0;
		}

		if (player->x < 0) {
			player->x = 0;
		}
		else if (player->x >= WIDTH - SPRITE_SIZE) {
			player->x = WIDTH - SPRITE_SIZE;
		}
		if (player->y < 0) {
			player->y = 0;
		}
		if (collision || collision1) {
			isJumping = false;
		}
	}

	SDL_Rect playerRectCre() {
		SDL_Rect playerRect;
		playerRect.x = player->x;
		playerRect.y = player->y;
		playerRect.w = 32;
		playerRect.h = 32;
		return playerRect;
	}
	// function to render stuff
	void renderWindow() {
		player->sprite = createPlayer();
		
		SDL_Rect playerRect = playerRectCre();
		SDL_SetRenderDrawColor(renderer, 60, 80, 80, 255);
		SDL_RenderClear(renderer);

		// assigning values to the rectangle
		

		SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
		SDL_RenderFillRect(renderer, &ground1);

		SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
		SDL_RenderFillRect(renderer, &ground2);

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
				case SDL_QUIT: {
					isRunning = false;
					break;
				}
			}
			controls();
		}
		
		return isRunning;
	}

	// this function will be ran when we quit the program
	void onQuit() {
		SDL_Texture* FPSCounter = createFPSText();
		SDL_DestroyWindow(mainwindow);
		SDL_DestroyTexture(FPSCounter);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(player->sprite);
		TTF_Quit();
		SDL_Quit();
	}
};
