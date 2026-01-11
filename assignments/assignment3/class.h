#include <vector>
#include <string>

class MyClass
{
public:
  MyClass();
  MyClass(const std::vector<std::string> list);
  ~MyClass();
  std::vector<std::string> getStudents() const;
  void setStudents(const std::string& old, const std::string& name);
  std::string toString() const;

private:
  std::vector<std::string> students;
  void update_name(std::string& oldName, const std::string& newName);
};