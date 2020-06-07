#include "Parser.h"


namespace trees {

	

	std::string ltrim(std::string str, const std::string chars = "\t\n\v\f\r ")
	{
		return str.erase(0, str.find_first_not_of(chars));
	}
	std::string rtrim(std::string str, const std::string chars = "\t\n\v\f\r ")
	{
		return str.erase(str.find_last_not_of(chars) + 1);
	}
	std::string trim(std::string str, const std::string chars = "\t\n\v\f\r ")
	{
		str = ltrim(str, chars);
		str = rtrim(str, chars);
		return str;
	}

	template<>
	std::vector<int> parse(std::string str)
	{
		std::vector<int> vec{};
		char cur;
		int count = 0;
		int num = 0;
		for (int i = 0; i < str.length(); i++) {
			cur = str[i];
			if (isdigit(cur)) {
				num *= 10;
				num += (cur - '0');
				count++;
			}
			else {
				if (count != 0) {
					vec.push_back(num);
					num = 0;
					count = 0;
				}
			}
		}
		if (count != 0)
			vec.push_back(num);
		return vec;
	}

	template<>
	int parse_single(std::string str) {
		return stoi(str);
	}

	template<>
	double parse_single(std::string str) {
		return stod(str);
	}

	std::vector<std::string> split_pairs(std::string str)
	{
		std::string tmp = "";
		std::vector<std::string> res;
		char cur;
		bool write = false;

		str = trim(str);

		for (int i = 0; i < str.length(); i++) {
			cur = str.c_str()[i];
			if (cur == '(') {
				write = true;	
			}
			if (write) {
				tmp += cur;
			}
			if (cur == ')') {
				write = false;
				if (tmp.length()) {
					res.push_back(tmp);
					tmp = "";
				}
			}
		}
		return res;
	}

	str_pair_t get_pair(std::string str) {
		
		str = trim(str, "()");

		std::string first = str.substr(0, str.find_first_of(";"));
		std::string second = str.substr(str.find_first_of(";") + 1);
		
		return str_pair_t(first, second);
	}

	template<class T>
	std::vector<std::pair<T, T>> parse_pairs(std::string str) {
		std::vector<std::string> raw_pairs = split_pairs(str);
		str_pair_t tmp;
		std::vector<std::pair<T, T>> res;

		for (std::string s : raw_pairs) {
			tmp = get_pair(s);
			res.push_back(new std::pair<T, T>(parse_single<T>(tmp.first), parse_single<T>(tmp.second)));
		}

		return res;
	}

	template<class T>
	T find_root(std::vector<std::pair<T, T>> pairs)
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
			if (isRoot)
				return tmp;
		}
	}

	std::vector<std::string> split_to_nodes(std::string str)
	{
		str = trim(str);
		int depth = 0;
		std::vector<std::string> res;
		std::string tmp = "";
		std::string tmp2 = "";
		char cur;

		for (int i = 1; i < str.length() - 1; i++) {
			cur = str.c_str()[i];
			if (cur == '(') {
				depth++;
			}
			else if (cur == ')')
				depth--;

			if (depth > 0) {
				tmp += cur;
			}
			else {
				if (tmp.length() > 0) {
					tmp += cur;
					res.push_back(tmp);
					tmp = "";
				}
				else {
					if (cur != ' ')
						tmp2 += cur;
					else if (tmp2.length() > 0) {
						res.push_back(tmp2);
						tmp2 = "";
					}

				}
			}

		}
		return res;
	}

	

	
}