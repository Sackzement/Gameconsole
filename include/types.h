#pragma once
#include <string>
#include <vector>

typedef unsigned char  byte;
typedef const    char  cchar;

typedef unsigned int   uint;

template <typename T>
struct vec2  {
public:
    T  x = 0;
    T  y = 0;
    
    vec2()  {}
    vec2(const T& xx, const T& yy) : vec2()  {
        
        x  = xx;
        y  = yy;
    }
    
    template <typename U>
    vec2& operator = (const vec2<U>& rhs)  {
        
        x  = rhs.x;
        y  = rhs.y;
        
        return *this;
    }
    
    template <typename U>
    vec2& operator += (const vec2<U>& rhs)  {
        
        x  += rhs.x;
        y  += rhs.y;
        
        return *this;
    }
    template <typename U>
    vec2& operator -= (const vec2<U>& rhs)  {
        
        x  -= rhs.x;
        y  -= rhs.y;
        
        return *this;
    }
    template <typename U>
    vec2& operator *= (const vec2<U>& rhs)  {
        
        x  *= rhs.x;
        y  *= rhs.y;
        
        return *this;
    }
    template <typename U>
    vec2& operator /= (const vec2<U>& rhs)  {
        
        x  /= rhs.x;
        y  /= rhs.y;
        
        return *this;
    }
    
    template <typename U>
    vec2 operator + (const vec2<U>& rhs) const {
        
        vec2 lhs(*this);
        
        lhs.x  += rhs.x;
        lhs.y  += rhs.y;
        
        return lhs;
    }
    template <typename U>
    vec2 operator - (const vec2<U>& rhs) const {
        
        vec2 lhs(*this);
        
        lhs.x  -= rhs.x;
        lhs.y  -= rhs.y;
        
        return lhs;
    }
    template <typename U>
    vec2 operator * (const vec2<U>& rhs) const {
        
        vec2 lhs(*this);
        
        lhs.x  *= rhs.x;
        lhs.y  *= rhs.y;
        
        return lhs;
    }
    template <typename U>
    vec2 operator / (const vec2<U>& rhs) const {
        
        vec2 lhs(*this);
        
        lhs.x  /= rhs.x;
        lhs.y  /= rhs.y;
        
        return lhs;
    }
};





