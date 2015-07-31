#pragma once
#include <string>
#include <vector>

typedef unsigned char  byte;
typedef const    char  cchar;

typedef unsigned int   uint;

template <typename T>
struct vec2  {
public:
    T  x;
    T  y;
    
    vec2() :
    x(0),
    y(0)
    {}
    
    vec2(const T& a) :
    x(a),
    y(a)
    {}
    
    vec2(const T& xx, const T& yy) :
    x(xx),
    y(yy)
    {}
    
    template <typename U>
    vec2& operator = (const vec2<U>& rhs)  {
        
        x  = rhs.x;
        y  = rhs.y;
        
        return *this;
    }
    template <typename U>
    vec2& operator = (const U& rhs)  {
        
        x  = rhs;
        y  = rhs;
        
        return *this;
    }
    
    template <typename U>
    vec2& operator += (const vec2<U>& rhs)  {
        
        x  += rhs.x;
        y  += rhs.y;
        
        return *this;
    }
    template <typename U>
    vec2& operator += (const U& rhs)  {
        
        x  += rhs;
        y  += rhs;
        
        return *this;
    }
    template <typename U>
    vec2& operator -= (const vec2<U>& rhs)  {
        
        x  -= rhs.x;
        y  -= rhs.y;
        
        return *this;
    }
    template <typename U>
    vec2& operator -= (const U& rhs)  {
        
        x  -= rhs;
        y  -= rhs;
        
        return *this;
    }
    template <typename U>
    vec2& operator *= (const vec2<U>& rhs)  {
        
        x  *= rhs.x;
        y  *= rhs.y;
        
        return *this;
    }
    template <typename U>
    vec2& operator *= (const U& rhs)  {
        
        x  *= rhs;
        y  *= rhs;
        
        return *this;
    }
    template <typename U>
    vec2& operator /= (const vec2<U>& rhs)  {
        
        x  /= rhs.x;
        y  /= rhs.y;
        
        return *this;
    }
    template <typename U>
    vec2& operator /= (const U& rhs)  {
        
        x  /= rhs;
        y  /= rhs;
        
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
    vec2 operator + (const U& rhs) const {
        
        vec2 lhs(*this);
        
        lhs.x  += rhs;
        lhs.y  += rhs;
        
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
    vec2 operator - (const U& rhs) const {
        
        vec2 lhs(*this);
        
        lhs.x  -= rhs;
        lhs.y  -= rhs;
        
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
    vec2 operator * (const U& rhs) const {
        
        vec2 lhs(*this);
        
        lhs.x  *= rhs;
        lhs.y  *= rhs;
        
        return lhs;
    }
    template <typename U>
    vec2 operator / (const vec2<U>& rhs) const {
        
        vec2 lhs(*this);
        
        lhs.x  /= rhs.x;
        lhs.y  /= rhs.y;
        
        return lhs;
    }
    template <typename U>
    vec2 operator / (const U& rhs) const {
        
        vec2 lhs(*this);
        
        lhs.x  /= rhs;
        lhs.y  /= rhs;
        
        return lhs;
    }
};





