#include "Student.h"

namespace trees {
	Student::Student(string firstname, string lastname, string group_, int age_, ID_t id_):
		Person(firstname, lastname, age_, id_),
		group(group_)
	{}
	Student::Student(string firstname, string midname, string lastname, string group_, int age_, ID_t id_) :
		Person(firstname, midname, lastname, age_, id_),
		group(group_)
	{}
	string Student::GetGroup()
	{
		return group;
	}
	void Student::SetGroup(string group_)
	{
		group = group_;
	}
	Student::operator std::string()
	{
		return "{" + GetFirstName() + ";" + GetMiddleName() + ";" + GetLastName() + ";" + GetGroup() + ";"
			+ to_string(GetAge()) + ";" + to_string(GetID()) + "}";
	}

	std::ostream& operator << (std::ostream& stream, Student z) {
		return stream << (std::string)z;
	}
}