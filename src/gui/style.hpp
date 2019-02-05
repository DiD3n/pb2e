#pragma once

#include <string>
#include "../gl/ColorType.hpp"

namespace gui {

	struct Style { //0.7v
		std::string name = "Flat Blue";

		//colors
		gl::Color primary    = { (ubyte) 76 , 209, 55 , 255},
				  secondary  = { (ubyte) 68 , 189, 50 , 255},
				  background = { (ubyte) 47 , 54 , 64 , 255},
				  textColor  = { (ubyte) 245, 246, 250, 255};

		//shader
		gl::Shader shader;

		//shader
		gl::VertexBufferLayout vbl;

		Style(const std::string& vertShaderPath = "res/basicUIVert.glsl", const std::string& fragShaderPath = "res/basicUIFrag.glsl") 
		: shader(vertShaderPath, fragShaderPath) {vbl.push({2}).push({3});}
		Style(const std::string& fragShaderPath, const std::string& vertShaderPath, const gl::VertexBufferLayout& vbl) 
		: shader(fragShaderPath, vertShaderPath) , vbl(vbl) {}

	};

};