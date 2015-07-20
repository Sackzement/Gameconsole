#pragma once

#include "Sprite.h"


class Text : public Sprite
{
public:
    string textString;
    
    Text(string s = "") : Sprite()  {
        
        textString = s;
        
        if ( textString != "" )  {
            
            updateTex();
        }
    }
    void updateTex()  {
        
        
    }
};



