#pragma once

#include <array>

namespace gl {

    template<typename T>
    class Vector2 {
        public:
        T x, y;

        constexpr Vector2(const T& x = 0, const T& y = 0)
         : x(x) , y(y) {}
        constexpr Vector2(const Vector2& other)
         : x(other.x) , y(other.y) {}

        operator std::array<Vector2<float>,1>() { return {*this};}

        Vector2 operator +(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
        Vector2 operator -(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
        Vector2 operator *(const Vector2& v) const { return Vector2(x * v.x, y * v.y); }
        Vector2 operator /(const Vector2& v) const { return Vector2(x / v.x, y / v.y); }


        Vector2& operator =(const Vector2& v) { 
            x = v.x; 
            y = v.y; 
            return *this; 
        }

        Vector2& operator +=(const Vector2& v) { 
            x += v.x; 
            y += v.y; 
            return *this; 
        }
        Vector2& operator -=(const Vector2& v) { 
            x -= v.x; 
            y -= v.y; 
            return *this; 
        }
        Vector2& operator *=(const Vector2& v) { 
            x *= v.x; 
            y *= v.y; 
            return *this; 
        }
        Vector2& operator /=(const Vector2& v) { 
            x /= v.x; 
            y /= v.y; 
            return *this; 
        }

        constexpr bool operator ==(const Vector2& v) const {
            return (x == v.x && y == v.y);
        }
        constexpr bool operator !=(const Vector2& v) const {
            return (x != v.x && y != v.y);
        }


        constexpr bool operator <(const Vector2& v) const{
            return (x < v.x && y < v.y);
        }
        constexpr bool operator >(const Vector2& v) const {
            return (x > v.x && y > v.y);
        }


        constexpr bool operator <=(const Vector2& v) const {
            return (x <= v.x && y <= v.y);
        }
        constexpr bool operator >=(const Vector2& v) const {
            return (x >= v.x && y >= v.y);
        }

    };

    typedef Vector2<float> Vector2f;
    typedef Vector2<double> Vector2d;
    typedef Vector2<int> Vector2i;
    typedef Vector2<unsigned int> Vector2ui;
    typedef Vector2<char> Vector2b;
    typedef Vector2<unsigned char> Vector2ub;
};