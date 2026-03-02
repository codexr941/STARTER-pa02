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

bool MovieDatabase::ratingDescNameAsc(const Movie& a, const Movie& b) {
    if (a.rating != b.rating) return a.rating > b.rating;
    return a.name < b.name;
}

auto lo = lower_bound(movies.begin(), movies.end(), prefix,
    [](const Movie& m, const string& s) {
        return m.name < s;
    });
auto hi = lo;
while (hi != movies.end() && hi->name.substr(0, prefix.size()) == prefix) {
    hi++;
}































