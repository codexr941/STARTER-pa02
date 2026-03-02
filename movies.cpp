#include "movies.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

bool readOneMovie(const string& line, Movie& m){
  int comma = (int)line.rfind(',');
  if (comma == -1)
    return false;
  m.name = line.substr(0, comma);
  string rateStr = line.substr(comma + 1);
  m.rating = stod(rateStr);
  return true;
}

bool nameLess(const Movie& a, const Movie& b) {
    return a.name < b.name;
}































