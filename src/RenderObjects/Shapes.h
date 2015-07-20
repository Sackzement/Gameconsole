#pragma once
#include "Shape.h"


struct Position  {
    int x  = 0;
    int y  = 0;
};



class  Pixel : public Shape, public Position  {
public:
    Pixel();
protected:
    void renderToTargetRenderer()  override;
};