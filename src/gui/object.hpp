#pragma once

#include <string>
#include <vector>

#include "../include/sdl2.hpp"

#include "../gl/VectorType.hpp"

#include "style.hpp"


namespace gui {

	class Object { //0.4v
	private:
		std::string name;
		gl::Vector2ui size;
		gl::Vector2f pos;
		bool pressed, hovered, clicked, active;

		const Style& style;

	public:

		std::vector<Object> children;

		Object(const std::string& name, const Style& style)
		 : name(name) , size(256,255) , pos(0,0) , style(style) {}
		Object(const Object& other)
		 : name(name) , size(size) , pos(pos) 
		 , style(style) , children(children) {};
		~Object();

		virtual void draw();

		virtual void update();

		void event(SDL_Event&);

		/* properties */

		Object& setPosition(const gl::Vector2f&);
		Object& setPosition(const float& x, const float& y);
		gl::Vector2f getPosition() const;

		Object& setSize(const gl::Vector2ui&);
		Object& setSize(const unsigned int& x, const unsigned int& y);
		gl::Vector2ui getSize() const;

		Object& setStyle(const Style&);
		const gui::Style& getStyle() const;

		/* events */

		constexpr bool isPressed() const {return pressed;}
		constexpr bool isHovered() const {return hovered;}
		constexpr bool isActive()  const {return active;}

	};

};