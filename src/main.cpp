#include "Game.hpp"

Game *game =  nullptr;

int main(int argc, char * argv[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	int cnt = 0;

	game = new Game();

	game->init("Area 51 TD", 1024, 960, false);

	while(game->running()){

		frameStart = SDL_GetTicks();

		game->handleEvents(); 
		game->update();
		game->render();
		
		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime){
			SDL_Delay(frameDelay - frameTime);
		}
		cnt++;
		if((cnt % 60) == 0){

			printf("%d .. 16 = %d\n", cnt,(cnt % 16)  );
			game->currentTime +=1;
			cnt =0;	
		}
		
	}

	game->clean();


	return 0;
}