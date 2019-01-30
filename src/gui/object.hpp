#pragma once

#include <string>
#include <vector>
#include "../gl/VectorType.hpp"
#include "../include/sdl2.hpp"

namespace gui {

	class Object { //0.3v
	private:
		gl::Vector2ui size;
		gl::Vector2f pos;
		bool pressed,hovered,clicked,active;
		//std::vector 

	public:

		Object();
		Object(const Object& other);
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

		Object& setSize();		

		/* events */

		constexpr bool isPressed() const {return pressed;}
		constexpr bool isHovered() const {return hovered;}
		constexpr bool isActive()  const {return active;}

	};

};