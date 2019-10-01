#import "EnemyManager.hpp"

	std::vector<Enemy*> EnemyManager::enemyList;
	int EnemyManager::enemyNr;
	Timer *emTimer = new Timer();

	EnemyManager::EnemyManager(Manager* man): manager(man){}
	EnemyManager::~EnemyManager(){}

	void EnemyManager::init(){
		 
		 //emTimer = Timer::Instance();
		 enemyNr = 0;
		 
		for(int i = 0; i < 7 ; i++){
			
			EnemyManager::CreateEnemy(5);		
			
		}
	}


	void EnemyManager::CreateEnemy(int x){
		printf("Creating enemy\n");

		enemyList.emplace(enemyList.end(),new Enemy(manager));
		enemyList.back()->addEnemy(192.0, -64.0, 0.0, 1.0);
		//enemyList.back()->takeDamage(x);
	}	

	void EnemyManager::SpawnEnemy(){
		//printf("%f\n",->t->position.y );
		//std::cout << enemyList[enemyNr]->t->position <<std::endl;
		//printf("Spawning Enemies\n");
		//printf("enemyList.size(): %d\n",enemyList.size() );
		emTimer->update();
		//printf("emTimer: %f\n",emTimer->DeltaTime());
		//printf("EnemyNr: %d\n", enemyNr);
			//every 2 seconds spawns new enemy, the <10 is here for the margin
		if((emTimer->deltaTime() >= 2 ) && enemyNr < enemyList.size()){
			emTimer->reset();
			enemyNr++;
			printf("enemyNr increased: %d\n", enemyNr );
		
		}
	//loops through the enemy list, according to spawned enemies


	}

	void EnemyManager::update(){
	
		SpawnEnemy();

		for(int i = 0; i < enemyNr; i++){
		//calls enemy update, to updates animations and velocities
			//printf("enemyList[%d]->health = %d\n", i, enemyList[i]->health );
			enemyList[i]->update(i);
			//printf("updating enemyList[%d]\n",i);
		}
	}





