#pragma once

#include "VectorType.hpp"
#include <array>

namespace gl {

    template<typename T>
    class Rect {
        public:
        T x, y, w, h;

        /* clockwise from the top left */
        std::array<Vector2<T>,4> getVertices() const {
            return std::array<Vector2<T>,4>{ Vector2<T>(x , y), Vector2<T>(x + w, y), Vector2<T>(x + w, y + h), Vector2<T>(x, y + h) }; 
        }

        Rect(const T& a = 0)
         : x(a) , y(a) , w(a) , h(a) {}
        Rect(const T& x, const T& y,const T& w, const T& h)
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

    typedef Rect<float> Rectf;
    typedef Rect<double> Rectd;
    typedef Rect<int> Recti;
    typedef Rect<unsigned int> Rectui;
    typedef Rect<char> Rectb;
    typedef Rect<unsigned char> Rectub;
};
