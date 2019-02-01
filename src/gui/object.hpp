#pragma once

#include <string>
#include <vector>
#include <memory>

#include "../include/sdl2.hpp"

#include "../gl/VectorType.hpp"

#include "style.hpp"


namespace gui {

	class Object { //0.6v
	private:
		std::string name;
		gl::Vector2ui size;
		gl::Vector2f pos;
		bool pressed, hovered, clicked, active;

		std::shared_ptr<const Style> style;

	public:

		std::vector<std::unique_ptr<gui::Object>> childrens;

		Object(const std::string& name, const std::shared_ptr<Style>& style)
		 : name(name) , size(256,255) , pos(0,0) , style(style) {}
		Object(const Object& other)
		 : name(name) , size(size) , pos(pos) 
		 , style(style) , childrens(childrens) {};
		~Object();

		virtual void draw();

		virtual void update();

		virtual void event(SDL_Event&);

		/* properties */

		Object& setPosition(const gl::Vector2f&);
		Object& setPosition(const float& x, const float& y);
		constexpr gl::Vector2f getPosition() const {return pos;}

		Object& setSize(const gl::Vector2ui&);
		Object& setSize(const unsigned int& x, const unsigned int& y);
		constexpr gl::Vector2ui getSize() const {return size;}

		Object& setStyle(const std::shared_ptr<const Style>&);
		const std::shared_ptr<const Style>& getStyle() const {return style;}

		/* events */

		constexpr bool isPressed() const {return pressed;}
		constexpr bool isHovered() const {return hovered;}
		constexpr bool isActive()  const {return active;}

	};

};