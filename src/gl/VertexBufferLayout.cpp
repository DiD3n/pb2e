#include "VertexBufferLayout.hpp"

namespace gl {

    VertexBufferLayout& VertexBufferLayout::operator += (const LayoutElement& element) {
        list.push_back(element);
        stride += list.back().count * list.back().getTypeSize();
        return *this;
    }

    VertexBufferLayout& VertexBufferLayout::operator << (const LayoutElement& element) {
        *this += element;
        return *this;
    }

    LayoutElement VertexBufferLayout::operator -- () {
        LayoutElement tmp(list.back());
        this->list.pop_back();
        return tmp;
    }

    VertexBufferLayout& VertexBufferLayout::push(unsigned int count, unsigned int type, bool normalized) {
        *this += {count,type,normalized};
        return *this;
    }

    std::string VertexBufferLayout::getScheme() const {
        std::string tmp = "";
        for (const LayoutElement& i : list) {
            if (tmp != "")
                tmp += " | ";
            tmp += std::to_string(i.count) + "x";
            switch (i.type) {
                case GL_FLOAT:
                    tmp += "Float";
                break;
                case GL_DOUBLE:
                    tmp += "Double";
                break;
                case GL_UNSIGNED_BYTE:
                    tmp += "Uint";
                break;
                case GL_UNSIGNED_INT:
                    tmp += "Uchar";
                break;
                case GL_BYTE:
                    tmp += "Int";
                break;
                case GL_INT:
                    tmp += "Char";
                break;
            }
        }
        return tmp;
    }

};