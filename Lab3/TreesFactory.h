#pragma once

#include <fstream>
#include "NTree.h"

namespace trees {
	template<class T>
	NTree<T> fromListFile(std::string path, int n, std::string format)
	{
		std::ifstream inf(path);
		std::stringstream ss;


		if (!inf)
		{
			throw std::runtime_error("Error writing to file!");
		}

		std::string strInput;
		//while (inf)
		//{
			ss << inf.rdbuf();
			//inf >> ss;

		//}
		return NTree<T>(ss.str(), n, format);
	}

	template<class T>
	NTree<T> fromPairFile(std::string path, int n)
	{
		std::ifstream inf(path);
		std::stringstream ss;

		if (!inf)
		{
			throw std::runtime_error("Error writing to file!");
		}

		//while (inf)
		//{
			ss << inf.rdbuf();
			//inf >> ss;

		//}
		return NTree<T>(ss.str(), n);
	}

	std::string Depth(int n)
	{
		std::stringstream ss;

		for (int i = 1; i <= n; i++)
			ss << i << " ";
		ss << 0;

		return ss.str();
	}
	std::string Width(int n)
	{
		std::stringstream ss;

		for (int i = 0; i <= n; i++)
			ss << i << " ";

		return ss.str();
	}
}