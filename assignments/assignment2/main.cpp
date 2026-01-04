/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "Andy Richard"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::unordered_set<std::string> get_applicants(std::string filename) {
  // STUDENT TODO: Implement this function.
  std::unordered_set<std::string> us; 
  std::fstream file{filename};
  if (!file.is_open()) {
    return us;
  }

  std::string name;
  while (getline(file, name)) {
    us.insert(name);
  }
  file.close();
  return us;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::unordered_set<std::string>& students) {
  // STUDENT TODO: Implement this function.
  std::string matchee;
  matchee += kYourName[0] + kYourName[kYourName.find(' ') + 1];
  std::queue<const std::string*> ret;

  for (auto const &stu : students) {
    std::string matcher;
    matcher += stu[0] + stu[stu.find(' ') + 1];
    if (matcher == matchee) {
      ret.push(&stu);
    }
  }

  return ret;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  while (!matches.empty()) {
    auto str = *matches.front();
    if (str.substr(str.find(' ')) == kYourName.substr(kYourName.find(' '))) {
      return str;
    }
    matches.pop();
  }

  std::string str {""};
  return str;
  // STUDENT TODO: Implement this function.
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
