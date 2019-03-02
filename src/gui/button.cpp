#include "button.hpp"

namespace gui
{

	Button::Button(const std::string& name, const std::shared_ptr<const Style>& style)
	 : Object(name, style) , callBack(nullptr) { }

	Button::Button(const std::string& name, const std::shared_ptr<const Style>& style, const std::function<void()>& func)
	 : Object(name, style) , callBack(new std::function<void()>(func)) { }

	Button::Button(const Button& other)
	 : Button(other.name, other.style, *other.callBack) { }

	Button::~Button()
	{
		if (callBack) //clear pointer
			delete callBack;
	}

	void Button::bindCallBack(const std::function<void()>& func)
	{
		if (callBack) //clear pointer
			delete callBack;
		
		callBack = new std::function<void()>(func);
	}
	void Button::unBindCallBack()
	{
		if (callBack) //clear pointer
			delete callBack;
		
		callBack = nullptr;
	}

}; //namespace gui