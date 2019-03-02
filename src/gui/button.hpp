#pragma once

#include "object.hpp"

#include <functional>

namespace gui
{

	class Button : public Object
	{
	protected:

		std::function<void()>* callBack;

	public:

		Button(const std::string& name, const std::shared_ptr<const Style>& style);
		Button(const std::string& name, const std::shared_ptr<const Style>& style, const std::function<void()>& func);
		Button(const Button&);
		~Button();

		//override
		void bindCallBack(const std::function<void()>&);
		void unBindCallBack();

	};

}; //namespace gui