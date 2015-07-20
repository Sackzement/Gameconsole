#pragma once


#include "types.h"



class Sprite  {
public:
    SDL_Texture*  texture;
    
    Sprite(SDL_Texture* tex = NULL)  {
        
        texture = tex;
        
        updateValues();
    }
    
    SDL_Rect      srcRect  = {} ;
    SDL_Rect      dstRect  = {} ;
    double        angle    = 0.  ;
    SDL_Point*    center   = NULL;
    SDL_RendererFlip flip  = SDL_FLIP_NONE;
    
    void updateValues()  {
        
        vec<2> oldSize = getSize();
        SDL_QueryTexture( texture, NULL, NULL, &defTexSize.w, &defTexSize.h );
        srcRect = defTexSize;
        setSize(oldSize.x, oldSize.y);
    }
    vec<2,float> getSize()  {
        
        vec<2,float> v;
        v.w = float(dstRect.w) / float(defTexSize.w) ;
        v.h = float(dstRect.h) / float(defTexSize.h) ;
        return v;
    }
    void setSize( float s )  {
        
        setSize(s,s);
    }
    void setSize( float w, float h )  {
        
        dstRect.w = float(defTexSize.w) * w ;
        dstRect.h = float(defTexSize.h) * h ;
    }
    
    virtual ~Sprite() {}
protected:
    SDL_Rect defTexSize = {} ;
    //vec<> pos;
    //vec<2> size = vec<2> (1.f) ;
};







