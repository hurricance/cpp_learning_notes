/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

#include <iostream>
#include <vector>
#include "class.h"

void sandbox() {
  // STUDENT TODO: Construct an instance of your class!
  std::vector<std::string> v {"anne", "bob", "cici"};
  MyClass mc {v};
  std::cout << mc.toString() << std::endl;
  mc.getStudents();
  mc.setStudents("bob", "daily");
  std::cout << mc.toString() << std::endl;
}