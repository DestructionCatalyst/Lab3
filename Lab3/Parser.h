#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace trees {

	typedef std::pair<std::string, std::string> str_pair_t;

	std::string trim(std::string str, const std::string chars = "\t\n\v\f\r ");

	template<class T>
	std::vector<T> parse(std::string str);

	template<class T>
	T parse_single(std::string str);

	std::vector<std::string> split_pairs(std::string str);

	str_pair_t get_pair(std::string str);

	std::vector<std::string> split_to_nodes(std::string str);

	template<class T>
	std::vector<std::pair<T, T>> parse_pairs(std::string str)
	{
		std::vector<std::string> raw_pairs = split_pairs(str);
		str_pair_t tmp;
		std::vector<std::pair<T, T>> res;

		for (std::string s : raw_pairs) {
			tmp = get_pair(s);
			res.push_back(std::pair<T, T>(parse_single<T>(tmp.first), parse_single<T>(tmp.second)));
		}

		return res;
	}

	template<class T>
	T find_root(std::vector<std::pair<T, T>>& pairs)
	{
		T tmp;
		bool isRoot = true;

		for (int i = 0; i < pairs.size(); i++) {
			tmp = pairs[i].second;
			isRoot = true;
			for (int j = 0; j < pairs.size(); j++) {
				if (tmp == pairs[i].first)
					isRoot = false;
			}
			if (isRoot) {
				//pairs.erase(pairs.begin() + i);
				return tmp;
			}
		}
		throw std::invalid_argument("Vector format exception!");
	}
}