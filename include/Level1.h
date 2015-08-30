#pragma once
#include "GameObject.h"

class Wall : public Rect  {
public:
    Wall() : Rect()  {
        
        size = .1;
        color = 0x666666ff;
        
        Color recColor  = 0x333333ff;
        
        Rect* recUP     = new Rect();
        Rect* recDown   = new Rect();
        Rect* recLeft   = new Rect();
        Rect* recRight  = new Rect();
        
        recUP->color     = recColor;
        recDown->color   = recColor;
        recLeft->color   = recColor;
        recRight->color  = recColor;
        
        
        recUP->pos     = 0.;
        recDown->pos   = vec2<double>(0.,.9);
        recLeft->pos   = 0.;
        recRight->pos  = vec2<double>(.9,0.);
        
        recUP->size     = vec2<double>(1.,.1);
        recDown->size   = vec2<double>(1.,.1);
        recLeft->size   = vec2<double>(.1,1.);
        recRight->size  = vec2<double>(.1,1.);
        
        addChild(recUP);
        addChild(recDown);
        addChild(recLeft);
        addChild(recRight);
    }
};



class Level1 : public GameObject  {
public:
    Level1() : GameObject()  {
        
        // create top and buttom walls
        for (int i=0; i< 16; ++i)  {
            Wall* wa = new Wall();
            wa->pos.x = .1 * double(i);
            addChild(wa);
            
            wa = new Wall();
            wa->pos.x = .1 * double(i);
            wa->pos.y = .9;
            addChild(wa);
        }
        // create left and right walls
        for (int i=0; i< 8; ++i)  {
            Wall* wa = new Wall();
            wa->pos.y = .1 + ( .1 * double(i) );
            addChild(wa);
            
            wa = new Wall();
            wa->pos.x = 1.5;
            wa->pos.y = .1 + ( .1 * double(i) );
            addChild(wa);
        }
        
    }
};




















