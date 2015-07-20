#pragma once
#include "RenderObject.h"




struct Color  {
    operator Uint32 ()  {
        return m_color;
    }
    void  operator= (Uint32 rhs)  {
        
        m_color = rhs;
    }
    
    Uint8& r  = *( (Uint8*)&m_color );
    Uint8& g  = *(&r+1);
    Uint8& b  = *(&r+2);
    Uint8& a  = *(&r+3);
private:
    Uint32 m_color = 0;
};



class  Shape : public RenderObject  {
public:
    Shape();
    Color color;
protected:
    void setRenderColor();
};








