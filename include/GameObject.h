#pragma once
#include <iostream>
#include "types.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>




class GameObject  {

public:
    vec2<double>  pos;
    vec2<double>  size;
    
    GameObject();
    
    virtual void input();
    virtual void update();
    virtual void render();
    
    void inputChildren()  const;
    void updateChildren() const;
    void renderChildren() const;
    
    bool hasChildren() const;
    bool hasChild(GameObject* ch) const;
    void addChild(GameObject* ch);
    void removeChild(GameObject* ch);
    void removeAllChildren();

protected:
    std::vector<GameObject*> * m_children;
    
};



class Color  {
private:
    Uint32 m_color;
public:
    Uint8& r;
    Uint8& g;
    Uint8& b;
    Uint8& a;
    
    Color();
    Color(Uint32 newColor);
           operator Uint32    () const;
    Color& operator =         (Uint32 newColor);
};


class  Shape  : public GameObject  {
public:
    Color      color;
    
    Shape();
};
class  Rect   : public Shape   {
public:
    void render() override;
    
};


class Texture  {
public:
    const int& w;
    const int& h;
    
    Texture();
    Texture( SDL_Texture* sdlTexture, int width, int height );
    
    void setSdlTexture( SDL_Texture* sdlTexture, int width, int height );
    
              operator SDL_Texture* ();
    Texture&  operator =            (const Texture& tex);

private:
    SDL_Texture*  m_sdlTexture;
    
    int  m_w;
    int  m_h;
};
class Image        : public GameObject  {
private:
    SDL_Rect*  m_clipRect;
public:
    Texture    texture;
    byte       flip;
    double     rot;
    
    Image();
    void render() override;
};












































