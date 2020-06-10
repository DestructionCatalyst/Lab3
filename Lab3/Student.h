#pragma once
#include "Person.h"
#include <ostream>

namespace trees {

	using std::to_string;

	class Student : public Person
	{
	private:
		string group;
	public:
		Student(string firstname,string lastname, string group_,  int age_, ID_t id_ = time(nullptr));
		Student(string firstname, string midname, string lastname, string group_, int age_, ID_t id_ = time(nullptr));
		string GetGroup();
		void SetGroup(string group_);
		operator std::string();
	};

	std::ostream& operator << (std::ostream& stream, Student z);
}