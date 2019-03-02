#pragma once

#include <string>

#include "storage.hpp"


namespace res {

	class dataManager {
	public:
		Storage<int> ints;
		Storage<float> floats;
		Storage<char> chars;
		Storage<double> doubles;
	};

};