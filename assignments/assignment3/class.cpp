#include "class.h"

MyClass::MyClass() {}
MyClass::~MyClass() {}

MyClass::MyClass(const std::vector<std::string> list)
{
  students = list;
}

std::vector<std::string> MyClass::getStudents() const
{
  return students;
}

void MyClass::setStudents(const std::string &old, const std::string &name)
{
  for (auto &stu : students)
  {
    if (stu == old)
    {
      update_name(stu, name);
    }
  }
}

std::string MyClass::toString() const
{
  std::string ret;
  for (auto stu : students)
  {
    ret += stu + " ";
  }
  ret += "\n";
  return ret;
}

void MyClass::update_name(std::string &oldName, const std::string &newName)
{
  oldName = newName;
}