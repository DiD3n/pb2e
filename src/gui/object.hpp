#pragma once

#include <string>
#include <vector>
#include <memory>

#include "../include/sdl2.hpp"

#include "../gl/Renderer.hpp"
#include "../gl/VectorType.hpp"

#include "style.hpp"


namespace gui {

	class Object { //0.8v
	protected:
		std::string name;
		gl::Rectf rect;
		bool pressed, hovered, clicked, active;

		std::shared_ptr<const Style> style;

	public:

		std::vector<std::shared_ptr<gui::Object>> childrens;

		Object(const std::string& name, const std::shared_ptr<const Style>& style)
		 : name(name) , rect(0,0,256,255) , style(style) {}
		Object(const Object& other)
		 : name(name) , rect(rect) , style(style) , childrens(childrens) {};
		~Object() {}

		virtual void draw(gl::Renderer&);

		virtual void update() {};

		virtual void event(SDL_Event&) {};

		/* properties */

		Object& setPosition(const gl::Vector2f&);
		Object& setPosition(const float& x, const float& y);
		constexpr gl::Vector2f getPosition() const {return rect.xy();}

		Object& setSize(const gl::Vector2f&);
		Object& setSize(const unsigned int& x, const unsigned int& y);
		constexpr gl::Vector2f getSize() const {return (rect.wh());}

		Object& setStyle(const std::shared_ptr<const Style>&);
		const std::shared_ptr<const Style>& getStyle() const {return style;}

		/* events */

		constexpr bool isPressed() const {return pressed;}
		constexpr bool isHovered() const {return hovered;}
		constexpr bool isActive()  const {return active;}

	};

};