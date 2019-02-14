#pragma once

#include "VectorType.hpp"
#include <array>

namespace gl {

    template<typename T>
    class Rect {
        public:
        T x, y, w, h;

        constexpr gl::Vector2<T>& xy() {return *(gl::Vector2<T>*)&x;}
        constexpr const gl::Vector2<T>& xy() const {return *(gl::Vector2<T>*)&x;}
        constexpr gl::Vector2<T>& wh() {return *(gl::Vector2<T>*)&w;}
        constexpr const gl::Vector2<T>& wh() const {return *(gl::Vector2<T>*)&w;}

        /* clockwise from the top left */
        constexpr std::array<Vector2<T>,4> getVertices() const {
            return { Vector2<T>(x , y), Vector2<T>(x + w, y), Vector2<T>(x + w, y + h), Vector2<T>(x, y + h) }; 
        }
        operator std::array<Vector2<T>,4>() { return getVertices(); }
        template<typename T2>
        operator Rect<T2>() { return {(T2)x, (T2)y, (T2)w, (T2)h}; }

        constexpr Rect(const T& a = 0)
         : x(a) , y(a) , w(a) , h(a) {}
        constexpr Rect(const T& x, const T& y,const T& w, const T& h)
         : x(x) , y(y) , w(w) , h(h) {}
        constexpr Rect(const Rect& other)
         : x(other.x) , y(other.y), w(other.w) , h(other.h) {}

        constexpr Rect operator +(const Rect& other) const { return Rect(x + other.x, y + other.y, h + other.h, w + other.w); }
        constexpr Rect operator -(const Rect& other) const { return Rect(x - other.x, y - other.y, h - other.h, w - other.w); }
        constexpr Rect operator *(const Rect& other) const { return Rect(x * other.x, y * other.y, h * other.h, w * other.w); }
        constexpr Rect operator /(const Rect& other) const { return Rect(x / other.x, y / other.y, h / other.h, w / other.w); }

        constexpr Rect operator +(const T& val) const { return Rect(x + val, y + val, h + val, w + val); }
        constexpr Rect operator -(const T& val) const { return Rect(x - val, y - val, h - val, w - val); }
        constexpr Rect operator *(const T& val) const { return Rect(x * val, y * val, h * val, w * val); }
        constexpr Rect operator /(const T& val) const { return Rect(x / val, y / val, h / val, w / val); }


        constexpr Rect& operator =(const Rect& other) { 
            x = other.x; 
            y = other.y; 
            w = other.w; 
            h = other.h; 
            return *this; 
        }


        constexpr Rect& operator +=(const Rect& other) { 
            return *this = (*this) + other;
        }

        constexpr Rect& operator -=(const Rect& other) { 
            return *this = (*this) - other;
        }

        constexpr Rect& operator *=(const Rect& other) { 
            return *this = (*this) * other;
        }

        constexpr Rect& operator /=(const Rect& other) { 
            return *this = (*this) / other; 
        }



        constexpr bool operator ==(const Rect& other) const {
            return (x == other.x && y == other.y && w == other.w && h == other.h);
        }
        constexpr bool operator !=(const Rect& other) const {
            return (x != other.x && y != other.y && w != other.w && h != other.h);
        }


        constexpr bool operator <(const Rect& other) const{
            return (x < other.x && y < other.y && w < other.w && h < other.h);
        }
        constexpr bool operator >(const Rect& other) const {
            return (x > other.x && y > other.y && w > other.w && h > other.h);
        }


        constexpr bool operator <=(const Rect& other) const {
            return (x <= other.x && y <= other.y && w <= other.w && h <= other.h);
        }
        constexpr bool operator >=(const Rect& other) const {
            return (x >= other.x && y >= other.y && w >= other.w && h >= other.h);
        }
    };

    typedef Rect<float> Rectf;
    typedef Rect<double> Rectd;
    typedef Rect<int> Recti;
    typedef Rect<unsigned int> Rectui;
    typedef Rect<char> Rectb;
    typedef Rect<unsigned char> Rectub;
};
