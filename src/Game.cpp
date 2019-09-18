
#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"


bool onButton;

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

auto& button(manager.addEntity());

const char* mapfile = "assets/TileSet.png";

enum groupLabels : std::size_t{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColiders,
	groupButtons,
};



Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if(fullscreen){
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
		printf("Subsystems Initializes!...\n");
	
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

		if(window){
			printf("Window created! \n");
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if(renderer){
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			printf("Renderer created! \n");
		}
	
		isRunning = true;
	}

	//player = new GameObject("assets/Goku2.png", 0, 0);
	//enemy = new GameObject("assets/enemy.png", 100, 100);
	map = new Map();

	Map::LoadMap("assets/Map_16x16", 16, 16);


	player.addComponent<TransformComponent>(64,64,3);
	player.addComponent<SpriteComponent>("assets/All.png",true);
	player.addComponent<KeyboardController>();
	
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
	//player.getComponent<SpriteComponent>().Play("Walk");

	button.addComponent<TransformComponent>(0, 0, 64, 64, 1);//736, 576,
	button.addComponent<SpriteComponent>("assets/Build.png");
	button.addGroup(groupButtons);
}

void Game::handleEvents()
{
	//SDL_Event  event;
	//SDL_PollEvent (&event);
	while(SDL_PollEvent (&event)){
		switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
			
				SDL_Point mPosition;
	    		SDL_GetMouseState( &mPosition.x, &mPosition.y );
			    if(button.getComponent<SpriteComponent>().isInside(&mPosition)){
	    			onButton = true;
			    	
	    			printf("%s\n", "clicked mouse on the button");
	    		}

			default:
				break;
		}
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	if(onButton){
		//button.getComponent<SpriteComponent>().setTex("assets/Tower.png");
		button.getComponent<SpriteComponent>().changeTex();

		onButton = false;

	}
	for(auto cc: colliders){
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
		
	}


}	

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));
auto& buttons(manager.getGroup(groupButtons));

void Game::render()
{
	SDL_RenderClear(renderer);

	for(auto& t : tiles){
		t->draw();	
	}
	for(auto& p : players){
		p->draw();	
	}
	for(auto& e : enemies){
		e->draw();	
	}
	for(auto& b : buttons){
		b->draw();	
	}
	
	SDL_RenderPresent(renderer);

}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Game Cleaned\n");
}

void Game::AddTile(int srcX, int srcY, int xPos, int yPos){
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xPos, yPos, mapfile);
	tile.addGroup(groupMap);
}	




