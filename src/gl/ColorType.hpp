#pragma once 

typedef unsigned char ubyte;

namespace gl {

    class Color {
        public:
        float r, g, b, a;


        Color(const Color& other)
         : r(other.r) , g(other.g) , b(other.b) , a(other.a) {}

        /* 0.0 - 1.0 (float) */
        Color(const float& c)
         : r(c) , g(c) , b(c) , a(1.f) {}
        Color(const float& r,const float& g = 0, const float& b = 0, const float& a = 1.f)
         : r(r) , g(g) , b(b) , a(a) {}

        /* 0 - 255 (unsigned char aka byte) */
         Color(const ubyte& c)
         : r(c/255.f) , g(c/255.f) , b(c/255.f) , a(255) {}
        Color(const ubyte& r,const ubyte& g = 0, const ubyte& b = 0, const ubyte& a = 255)
         : r(r/255.f) , g(g/255.f) , b(b/255.f) , a(a/255.f) {}

        Color operator +(const Color& other) const { return Color(r + other.r, g + other.g, b + other.b, a + other.a); }
        Color operator -(const Color& other) const { return Color(r - other.r, g - other.g, b - other.b, a - other.a); }
        Color operator *(const Color& other) const { return Color(r * other.r, g * other.g, b * other.b, a * other.a); }
        Color operator /(const Color& other) const { return Color(r / other.r, g / other.g, b / other.b, a / other.a); }


        Color& operator =(const Color& other) { 
            r = other.r; 
            g = other.g; 
            b = other.b; 
            a = other.a; 
            return *this; 
        }

        Color& operator +=(const Color& other) { 
            r += other.r; 
            g += other.g; 
            b += other.b; 
            a += other.a; 
            return *this; 
        }
        Color& operator -=(const Color& other) { 
            r -= other.r; 
            g -= other.g; 
            b -= other.b; 
            a -= other.a; 
            return *this; 
        }
        Color& operator *=(const Color& other) { 
            r *= other.r; 
            g *= other.g; 
            b *= other.b; 
            a *= other.a; 
            return *this; 
        }
        Color& operator /=(const Color& other) { 
            r /= other.r; 
            g /= other.g; 
            b /= other.b; 
            a /= other.a; 
            return *this; 
        }

        bool operator ==(const Color& other) const {
            if(r == other.r && g == other.g && b == other.b && a == other.a)
                return true;
            else
                return false;
        }
        bool operator !=(const Color& other) const {
            if(r != other.r && g != other.g && b != other.b && a != other.a)
                return true;
            else
                return false;
        }


        bool operator <(const Color& other) const{
            if(r < other.r && g < other.g && b < other.b && a < other.a)
                return true;
            else
                return false;
        }
        bool operator >(const Color& other) const {
            if(r > other.r && g > other.g && b > other.b && a > other.a)
                return true;
            else
                return false;
        }


        bool operator <=(const Color& other) const {
            if(r <= other.r && g <= other.g && b <= other.b && a <= other.a)
                return true;
            else
                return false;
        }
        bool operator >=(const Color& other) const {
            if(r >= other.r && g >= other.g && b >= other.b && a >= other.a)
                return true;
            else
                return false;
        }
    };

};
