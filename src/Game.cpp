
#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"
#include "Timer.hpp"
#include "EnemyManager.hpp"


#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/assign.hpp>
#include <boost/range/adaptor/indexed.hpp>


using namespace boost::adaptors;


//disposable variables
int x = 0;
int way = 0;
int enemyID = 0;
bool onButton;
int  mouse_x, mouse_y;
 SDL_Rect curs_dst;
 SDL_Texture *sprite;

//The map object
Map* map;


//The ECS manager object
Manager manager;

//SDL main game rander object
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

int Game::currentTime = 1;

std::vector<ColliderComponent*> Game::colliders;
//list of enemy objects
///std::vector<Enemy*> enemyLists;
//List of velocities for enemies, red from Map::LoadMap()
std::vector<Vector2D> Game::path;

std::vector<Tower*> towerList;

//Timer *mTimer = Timer::Instance();

EnemyManager  *eM = new EnemyManager(&manager);

//auto& player(manager.addEntity());

auto& button(manager.addEntity());
//Enemy objects
/*Enemy *enemy = new Enemy(&manager);
EnemyManager *enemy1 = new Enemy(&manager);
Enemy *enemy2 = new Enemy(&manager);
Enemy *enemy3 = new Enemy(&manager);*/
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

	button.addComponent<TransformComponent>(960, 896, 64, 64, 1);//736, 576,
	button.addComponent<SpriteComponent>("assets/Build.png");
	button.addGroup(groupButtons);


	eM->init();

	//eM->CreateEnemy("BOOBS");

	/*
	//iniliasing enemies and putting them into the list
	enemy->addEnemy(192.0, -64.0, 0.0, 1.0);
	enemyLists.emplace(enemyLists.end(),enemy);

	enemy1->addEnemy(192.0, -64.0, 0.0, 1.0);
	enemyLists.emplace(enemyLists.end(),enemy1);
	
	enemy2->addEnemy(192.0, -64.0, 0.0, 1.0);
	enemyLists.emplace(enemyLists.end(),enemy2);
	
	enemy3->addEnemy(192.0, -64.0, 0.0, 1.0);
	enemyLists.emplace(enemyLists.end(),enemy3);
	//printf("enemyLists size = %d\n",enemyLists.size() );
*/
	sprite = TextureManager::LoadTexture("assets/T1.png");

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
	
			    if(button.getComponent<SpriteComponent>().isInside(500)){
	    			onButton = true;
			    	
	    			printf("%s\n", "clicked mouse on the button");
	    		}
	    		if(event.button.button == SDL_BUTTON_RIGHT){
	    			onButton = false;
	    			
	    		}
	    	case SDL_KEYDOWN:
	    		if(event.key.keysym.sym == SDLK_ESCAPE){
	    			printf("%s\n","SDLK_ESCAPE" );
	    			onButton = false;
	    		}

			default:
				break;
		}
	}
}
auto& towers(manager.getGroup(Game::groupTowers));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::update()
{	
	int tNr = 0;
	int eNr = 0;
	int hitList = 0;
	//calls the manager refresh to update exsitings entities
	manager.refresh();
	//calls the manager to updates all entities and their componenents
	//feks position, speed, size etc. 
	manager.update();

	eM->update();

	if(onButton){

		 SDL_Point mPosition;
		 //int  mouse_x, mouse_y;
		 bool pressed = SDL_GetMouseState( &mPosition.x, &mPosition.y );
		// std::cout<<pressed<<std::endl;
		 curs_dst = {mPosition.x-32, mPosition.y-32, 64, 64};
		 
		 
		if(pressed & SDL_BUTTON(SDL_BUTTON_LEFT) && !button.getComponent<SpriteComponent>().isInside(500)){
		 	
			if(towers.size() == 0){
				Tower* tower1 = new Tower(&manager);;
				tower1->addTower(mPosition.x-32, mPosition.y-32);
				towerList.emplace(towerList.end(),tower1);
				printf("made first Tower: %d\n", towers.size() );
				onButton = false;
			}else{
				SDL_Rect pospos = {mPosition.x-32, mPosition.y-32, 64,64};
				for(auto& t: towers){
					if(!(t->getComponent<SpriteComponent>().isInside(towers.size()))){ 
					 	Tower* tower1 = new Tower(&manager);
					 	tower1->addTower(mPosition.x-32, mPosition.y-32);
					 	towerList.emplace(towerList.end(),tower1);
					 	printf("made Tower: %d\n", towers.size() );
					 	onButton = false;
					 	break;
					}	
				} 		
		 	}
		}
	}

	for(auto& t: towers){
		
		//for(auto& e:boost::adaptors::reverse(enemies)){
		towerList[tNr]->hitList = false;
		towerList[tNr]->enemys = NULL;
		for(auto& e:enemies){
			towerList[tNr]->hitList = false;
			if(Collision::CC(t->getComponent<CircleComponent>(), e->getComponent<ColliderComponent>())){
				towerList[tNr]->targetEnemy(eM->enemyList[eNr]);
				//towerList[tNr]->targetEnemy(e->getComponent<TransformComponent>().position,e->getComponent<TransformComponent>().velocity);
				towerList[tNr]->hitList = true;
				hitList++;
				///printf("Enemie[%d] in range to Tower[%d]\n",eNr, tNr );
				break;
			}
			//towerList[tNr]->hitList = false;
			eNr ++;
		}

		//towerList[tNr]->update(hitList);
		//hitList = 0;
		eNr = 0;
		tNr++;
	}tNr = 0;
	
	
	for(auto& t: towerList){
		//printf("Tower-sTimer : %d\n", t->sTimer->deltaTime()); 
		t->update(2);
	}

	for(auto& p : projectiles ){
		for (auto& e : enemies){
			//printf("eNr = %d\n", eNr );
			if(Collision::AABB(p->getComponent<ColliderComponent>(),e->getComponent<ColliderComponent>())){
				eM->enemyList[eNr]->takeDamage(25);
				//printf("enemyLists[%d].health = %d\n", eNr,enemyLists[eNr]->health );
				//printf("enemyLists.begin()+eNr = %d \n",enemyLists.begin()+eNr );
				printf("%s\n","hit!" );	
				if(eM->enemyList[eNr]->health <= 0){
					printf("DEA\n");
					//printf("eNr = %d, ", eNr );
					e->destroy();
					//eM->enemyList[eNr]->die();

					eM->enemyList.erase(eM->enemyList.begin()+eNr);
					eM->enemyNr--;
				}
				p->destroy();
			}
			eNr++;
		}
		eNr=0; 
	}
}	

//gets the list of tiles, enemies, buttons from the manager 
auto& tiles(manager.getGroup(Game::groupMap));
//auto& players(manager.getGroup(Game::group//Players));


auto& buttons(manager.getGroup(Game::groupButtons));

//auto& towers(manager.getGroup(Game::groupTowers));

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
	for(auto& tw : towers){
		tw->draw();
	}
	for(auto& p : projectiles){
		p->draw();
	}
	if(onButton){
		SDL_RenderCopy(renderer, sprite, NULL, &curs_dst);
	}

	SDL_RenderPresent(renderer);
	

}
void Game::clean()
{	SDL_DestroyTexture(sprite);
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




