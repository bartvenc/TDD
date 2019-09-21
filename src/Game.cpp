
#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "Enemy.hpp"

//disposable variables
int way = 0;
int enemyID = 0;
bool onButton;

//The map object
Map* map;

//The ECS manager object
Manager manager;

//SDL main game rander object
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;
//list of enemy objects
std::vector<Enemy*> enemyList;
//List of velocities for enemies, red from Map::LoadMap()
std::vector<Vector2D> Game::path;


//auto& player(manager.addEntity());

auto& button(manager.addEntity());
//Enemy objects
Enemy *enemy = new Enemy(&manager);
Enemy *enemy1 = new Enemy(&manager);
//The tile sett for AddTile() function
const char* mapfile = "assets/TileSet.png";

Game::Game()
{}
Game::~Game()
{}
//The main initliazation of everything
void Game::init(const char* title, int width, int height, bool fullscreen)
{
	//SDL function iniliatiazion
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
			//SDL_RenderSetViewport(renderer, &view);
		}
	
		isRunning = true;
	}
  
	//iniliatiazion of map object
	map = new Map();
	//loads map cords and id's for tiles.
	Map::LoadMap("assets/Map_16x16", 16, 16);

	//for(auto&& x: Game::path)
	//std::cout << x << '\n';
	//player.addComponent<TransformComponent>(64,64,3);
	//player.addComponent<SpriteComponent>("assets/All.png",true);
	//player.addComponent<KeyboardController>();
	
	//player.addComponent<ColliderComponent>("//player");
	//player.addGroup(group//Players);
	////player.getComponent<SpriteComponent>().Play("Walk");

	button.addComponent<TransformComponent>(736, 576, 64, 64, 1);//736, 576,
	button.addComponent<SpriteComponent>("assets/Build.png");
	button.addGroup(groupButtons);

	//iniliasing enemies and putting them into the list
	enemy->addEnemy(192.0, -64.0, 0.0, 1.0);
	enemyList.emplace(enemyList.end(),enemy);
	enemy1->addEnemy(192.0, -64.0, 0.0, 1.0);
	enemyList.emplace(enemyList.end(),enemy1);
	//printf("enemyList size = %d\n",enemyList.size() );

}

void Game::handleEvents()
{

	//SDL_PollEvent registers all of the events and qeues them up
	while(SDL_PollEvent (&event)){
		//iterates through event type, for eks, keyboard, mouse etc.
		switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			//just a case test	
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
	//calls the manager refresh to update exsitings entities
	manager.refresh();
	//calls the manager to updates all entities and their componenents
	//feks position, speed, size etc. 
	manager.update();

	//gets the time passed from the SDL init()
	currentTime = SDL_GetTicks();
	//printf("currentTime: %d\n", currentTime );
	//printf("enemyID %d\n", enemyID );
	//printf("(currentTime % 3000)= %d\n",(currentTime % 3000) );

	//every 2 seconds spawns new enemy, the <10 is here for the margin
	if((currentTime % 2000) < 10 ){
		if(enemyID < enemyList.size()){
			enemyID++;
			//printf("enemyID increased: %d\n", enemyID );
		}
	}
	//loops through the enemy list, according to spawned enemies
	for(int i = 0; i < enemyID; i++){
		//calls enemy update, to updates animations and velocities
		enemyList[i]->update(i+1);
	}

	if(onButton){

	}
	for(auto cc: colliders){
		//Collision::AABB(//player.getComponent<ColliderComponent>(), *cc);
		
	}

}	

//gets the list of tiles, enemies, buttons from the manager 
auto& tiles(manager.getGroup(Game::groupMap));
//auto& players(manager.getGroup(Game::group//Players));
auto& enemies(manager.getGroup(Game::groupEnemies));

auto& buttons(manager.getGroup(Game::groupButtons));


//updates all of the sprite positions, and redraw them
void Game::render()
{
	SDL_RenderClear(renderer);

	for(auto& t : tiles){
		t->draw();	
	}
	/*/for(auto& p : players){
		p->draw();	
	}*/
	for(auto& e : enemies){
		//printf("%s\n","drawing enem" );
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




