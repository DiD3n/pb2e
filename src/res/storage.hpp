#pragma once

#include <map>
#include <utility>

namespace res {

	template<typename T>
	class Storage {
	private:

		std::map<std::string, T> items;

	public:

		Storage() {}
		Storage(const Storage& other)
		 : items(other.items) {}

		~Storage() {}


		//using args for construcor (a bit faster) 
		template<typename ... Args>
		inline void add(const std::string& key, const Args&...);

		inline void remove(const std::string& key);

		inline void clear();

		// ultra safe
		T& get(const std::string& n);

		// a bit faster but not safe
		T& operator[](const std::string& n);

	};

}; //namespace res

#include "storage.inl"