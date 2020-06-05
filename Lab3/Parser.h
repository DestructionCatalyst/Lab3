#pragma once
#include <string>
#include <vector>
#include <cmath>

namespace trees {
	template<class T>
	std::vector<T> parse(std::string str);

	template<class T>
	T parse_single(std::string str);

	template<class T>
	T parse_pairs(std::string str);

	std::vector<std::string> split_to_nodes(std::string str);
}