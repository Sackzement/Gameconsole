#include "include/sdf.h"

#include "include/Engine.h"
#include "include/Level1.h"
#include "include/PCinfo.h"
#include <algorithm>


class Player  : public GameObject  {
public:
    vec2<double> curr_speed  = 0.;
    double moveSpeed    = .8;
    int    moveDir      = 0;
    double fallAccel    = .002;
    double jumpSpeed    = .04;
    
    Player() : GameObject()  {
        pos = vec2<double>(.1,.8);
        size = .1;
        
        Rect* rec = new Rect();
        addChild(rec);
    }
    
    void input()  override  {
        
        moveDir = 0;
        
		if (engine.kbStateOnceDown[SDLK_UP])     curr_speed.y = -jumpSpeed;
        if (engine.kbState[SDLK_LEFT])   moveDir -= 1;
		if (engine.kbState[SDLK_RIGHT])  {
			moveDir += 1;
		}
        if (engine.kbStateOnceDown[SDLK_r])  pos = .5;
    }
    void update() override  {
        
        double speedDelta = moveSpeed * engine.deltaTime;
        
		curr_speed.x = double(moveDir) * speedDelta;
        
		curr_speed.y += fallAccel;
        
		pos += curr_speed;
    }
};

Engine engine;
GameObject* screen;
PCinfo* pc;
Level1 * lvl;
Player * pl;

class Selector : GameObject  {
public:
    void input() override {
        if ( engine.kbStateOnceDown[SDLK_s] )  {
            
            
        }
    }
};

void setWindowDefaultValues()  {
    
    engine.window.setTitle("Jump n Pong");
    //engine.window.setSize(2880,1800);
    engine.window.setSize(1500,900);
    //engine.window.setFullscreen(true);
}


class  MyInput  : public GameObject  {
public:
    void input() override  {
        if (engine.kbStateOnceDown[SDLK_ESCAPE])
            engine.quit = true;
        
        if (engine.kbStateOnceDown[SDLK_SPACE])  {
            
            SDL_DisplayMode largestMode = pc->displays[0].getLargesMode();
            engine.window.setDisplayMode(largestMode);
            
            screen->size     = engine.window.size.y;
            //screen->pos.x  = double(engine.window.size.x - engine.window.size.y) * .5;
            //screen->pos.y  =
            
        }
    }
};



void ululu()  {
    
    screen           = new GameObject();
    screen->size     = engine.window.size.y;
    //screen->pos.x  = double(engine.window.size.x - engine.window.size.y) * .5;
    //screen->pos.y  =
    
    
    engine.gameObjects.push_back(screen);
    
    
    MyInput* inp = new MyInput();
    engine.gameObjects.push_back(inp);
    
    lvl = new Level1();
    screen->addChild( lvl );
    
    pl = new Player();
    screen->addChild(pl);
}

struct collPair  {
    GameObject*   objToMove;
    GameObject*   staticObj;
    double        distance;
    vec2<double>  collRect;
    
    collPair(GameObject* objToMove, GameObject* staticObj, double distance, vec2<double> collRect)  {
        this->objToMove  = objToMove;
        this->staticObj  = staticObj;
        this->distance   = distance;
        this->collRect   = collRect;
    }
    
};
auto collisions =  std::vector<collPair> ();
void checkCollisions()  {
    
    auto walls  = lvl->getChildren();

    for (auto it = walls->begin(); it != walls->end(); ++it)  {
        
        vec2<double> collRect;
        if ( pl->checkColl(**it, collRect) )  {
            
            vec2<double> plCenter, wallCenter, centerDiff;
            plCenter    = pl->pos + (pl->size * .5);
            wallCenter  = (*it)->pos + ((*it)->size * .5);
            centerDiff  =  wallCenter - plCenter;
            
            double dist = sqrt( pow(centerDiff.x, 2) + pow(centerDiff.y, 2) );
            
            collisions.push_back( collPair(pl,*it,dist, collRect) );
        }
    }
}

bool sortFunc(collPair first, collPair second)  {
    return first.distance <= second.distance;
}
void resolveCollisions()  {
    
    while ( ! collisions.empty() ) {
        
        std::sort(collisions.begin(), collisions.end(), sortFunc);
        
        collPair firstPair = collisions.front();
        vec2<double> firstCenter, secondCenter, centerDiff;
        firstCenter   = firstPair.objToMove->pos + (firstPair.objToMove->size * .5);
        secondCenter  = firstPair.staticObj->pos + (firstPair.staticObj->size * .5);
        centerDiff    = firstCenter - secondCenter;
        
        if ( pow(centerDiff.x, 2.) > pow(centerDiff.y, 2.) )  {
            if (centerDiff.x < 0.)
                firstPair.objToMove->pos.x -= firstPair.collRect.x;
            else
                firstPair.objToMove->pos.x += firstPair.collRect.x;
        }
        else  {
            if (centerDiff.y < 0.)  {
                firstPair.objToMove->pos.y -= firstPair.collRect.y;
                Player* plif = dynamic_cast<Player*>(firstPair.objToMove);
                if (plif)
					plif->curr_speed.y = 0.;
            }
            else
                firstPair.objToMove->pos.y += firstPair.collRect.y;
        }
        
        collisions.erase(collisions.begin());
        
        for (auto it=collisions.begin(); it != collisions.end();)  {
            
            if ( (*it).objToMove->checkColl(*(*it).staticObj, (*it).collRect) )  {
                
                vec2<double> firCenter, secCenter, cenDiff;
                firCenter  = (*it).objToMove->pos + ((*it).objToMove->size * .5);
                secCenter  = (*it).staticObj->pos + ((*it).staticObj->size * .5);
                cenDiff    = firCenter - secCenter;
                (*it).distance = sqrt( pow(cenDiff.x, 2) + pow(cenDiff.y, 2) );
            }
            else  {
                it = collisions.erase(it);
				continue;
            }

			++it;
        }
    }
}

int main (int argc, char** argv)  {
    
    engine.initLibs();
    
    pc = new PCinfo();
    
    setWindowDefaultValues();
 

    // set win data from file
    // if (true)  // if there is a settings file
 
    // overwrite win data from arguments
	// if (true)  //  if there are arguments
 
    engine.window.create();

    engine.loadResources();
    
    ululu();
    
    engine.collChecks.push_back(&checkCollisions);
    engine.collChecks.push_back(&resolveCollisions);
    
    engine.enterMainLoop();
    return 0;
 }