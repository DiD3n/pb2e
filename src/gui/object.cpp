#include "object.hpp"


namespace gui {

	/* properties */

	Object& Object::setPosition(const gl::Vector2f& pos) {
		this->pos = pos;
		return *this;
	}
	Object& Object::setPosition(const float& x, const float& y) {
		this->pos.x = x;
		this->pos.y = y;
		return *this;
	}

	Object& Object::setSize(const gl::Vector2ui& size) {
		this->size = size;
		return *this;
	}
	Object& Object::setSize(const unsigned int& x, const unsigned int& y) {
		this->size.x = x;
		this->size.y = y;
		return *this;
	}

	Object& Object::setStyle(const std::shared_ptr<const Style>& style) {
		this->style = style;
		return *this;
	}

};