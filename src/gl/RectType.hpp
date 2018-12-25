#pragma once

#include "VectorType.hpp"

template<typename T>
struct tmpGlRect{
    T x, y, x2, y2;
};

namespace gl {

    template<typename T>
    class Rect {
        public:
        T x, y, w, h;

        tmpGlRect<T> getGlRect() {return {x,y,w+x,h+y};}

        Rect(const T& x = 0, const T& y = 0,const T& w = 0, const T& h = 0)
         : x(x) , y(y) , w(w) , h(h) {}
        Rect(const Rect& other)
         : x(other.x) , y(other.y), w(other.w) , h(other.h) {}

        Rect operator +(const Rect& other) const { return Rect(x + other.x, y + other.y, h + other.h, w + other.w); }
        Rect operator -(const Rect& other) const { return Rect(x - other.x, y - other.y, h - other.h, w - other.w); }
        Rect operator *(const Rect& other) const { return Rect(x * other.x, y * other.y, h * other.h, w * other.w); }
        Rect operator /(const Rect& other) const { return Rect(x / other.x, y / other.y, h / other.h, w / other.w); }


        Rect& operator =(const Rect& other) { 
            x = other.x; 
            y = other.y; 
            w = other.w; 
            h = other.h; 
            return *this; 
        }

        Rect& operator +=(const Rect& other) { 
            x += other.x; 
            y += other.y; 
            w += other.w; 
            h += other.h; 
            return *this; 
        }
        Rect& operator -=(const Rect& other) { 
            x -= other.x; 
            y -= other.y; 
            w -= other.w; 
            h -= other.h; 
            return *this; 
        }
        Rect& operator *=(const Rect& other) { 
            x *= other.x; 
            y *= other.y; 
            w *= other.w; 
            h *= other.h; 
            return *this; 
        }
        Rect& operator /=(const Rect& other) { 
            x /= other.x; 
            y /= other.y; 
            w /= other.w; 
            h /= other.h; 
            return *this; 
        }

        bool operator ==(const Rect& other) const {
            if(x == other.x && y == other.y && w == other.w && h == other.h)
                return true;
            else
                return false;
        }
        bool operator !=(const Rect& other) const {
            if(x != other.x && y != other.y && w != other.w && h != other.h)
                return true;
            else
                return false;
        }


        bool operator <(const Rect& other) const{
            if(x < other.x && y < other.y && w < other.w && h < other.h)
                return true;
            else
                return false;
        }
        bool operator >(const Rect& other) const {
            if(x > other.x && y > other.y && w > other.w && h > other.h)
                return true;
            else
                return false;
        }


        bool operator <=(const Rect& other) const {
            if(x <= other.x && y <= other.y && w <= other.w && h <= other.h)
                return true;
            else
                return false;
        }
        bool operator >=(const Rect& other) const {
            if(x >= other.x && y >= other.y && w >= other.w && h >= other.h)
                return true;
            else
                return false;
        }
    };

    typedef Rect<float> Rectf

};
