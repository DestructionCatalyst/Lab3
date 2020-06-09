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

	
}