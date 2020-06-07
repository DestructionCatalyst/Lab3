#pragma once
#include <string>
#include <vector>
#include <cmath>

namespace trees {

	typedef std::pair<std::string, std::string> str_pair_t;

	template<class T>
	std::vector<T> parse(std::string str);

	template<class T>
	T parse_single(std::string str);

	template<class T>
	std::vector<std::pair<T, T>> parse_pairs(std::string str);

	template<class T>
	T find_root(std::vector<std::pair<T, T>> pairs);

	std::vector<std::string> split_to_nodes(std::string str);
}