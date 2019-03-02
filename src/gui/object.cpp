#include "object.hpp"


namespace gui
{

	void Object::draw(gl::Renderer& renderer) {

		renderer.draw<gl::rectangle>(style->shader,rect,style.get()->background);
		
	}

	/* properties */

	Object& Object::setPosition(const gl::Vector2f& pos)
	{
		this->rect.xy() = pos;
		return *this;
	}
	Object& Object::setPosition(const float& x, const float& y)
	{
		this->rect.x = x;
		this->rect.y = y;
		return *this;
	}

	Object& Object::setSize(const gl::Vector2f& size)
	{
		this->rect.wh() = size;
		return *this;
	}
	Object& Object::setSize(const unsigned int& x, const unsigned int& y)
	{
		this->rect.w = x;
		this->rect.h = y;
		return *this;
	}

	Object& Object::setStyle(const std::shared_ptr<const Style>& style)
	{
		this->style = style;
		return *this;
	}

}; //namespace gui