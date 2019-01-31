#pragma once

#include <string>
#include "../gl/ColorType.hpp"

namespace gui {

	class Style { //0.1v
	public:
		std::string name = "Flat Blue";
		gl::Color primary = {(ubyte)76, 209, 55}, secondary = {(ubyte)68, 189, 50}, background= {(ubyte)47, 54, 64};
		gl::Color textColor = {(ubyte)245, 246, 250};
	};

};