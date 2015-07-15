#pragma once


typedef unsigned char  byte;
typedef const    char  cchar;



template <byte s = 4, class T = float>
class    vec    {
private:
    T      arr[(s<4?4:s)]    = {} ;
public:
    vec()                  {}
    vec(T all)  {
        
        for (int i=0;i<s;++i)
            arr[i] = all;
    }
    vec(T a, T b, T c =0.f, T d =0.f)  {
        
        arr[0] = a ;
        arr[1] = b ;
        arr[2] = c ;
        arr[3] = d ;
    }
    
    T operator[]  (int i)  {
        return arr[i];
    }
    T &      x       = arr[0];
    T &      y       = arr[1];
    T &      z       = arr[2];
    T &      w       = arr[0];
    T &      h       = arr[1];
    T &      d       = arr[2];
    T &      a       = arr[3];
} ;
