#include "Format.h"

namespace trees {
	std::string DepthFormat(int n)
	{
		std::stringstream ss;

		for (int i = 1; i <= n; i++)
			ss << i << " ";
		ss << 0;

		return ss.str();
	}
	std::string WidthFormat(int n)
	{
		std::stringstream ss;

		for (int i = 0; i <= n; i++)
			ss << i << " ";

		return ss.str();
	}
}