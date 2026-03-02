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

void MovieDatabase::sortByName() {
    sort(movies.begin(), movies.end(), nameLess);
}

void MovieDatabase::loadFromFile(const string& filename){
  movies.clear();
string line;
while (getline(fin, line)) {
 Movie m;
        if (readOneMovie(line, m)) {
            movies.push_back(m);
        }
    }
fin.close();
sortByName(); 
}

void MovieDatabase::printAllMovies() const{
  for (int i = 0; i < (int)movies.size(); i++)
    cout << movies[i].name << ", " << movies[i].rating << "\n";
}

bool MovieDatabase::queryPrefix(const string& prefix, string& bestLine) const {
  auto lo = lower_bound(movies.begin(), movies.end(), prefix,
        [](const Movie& m, const string& s) {
            return m.name < s;
        });
if (lo == movies.end() || lo->name.substr(0, prefix.size()) != prefix) {
return false;
}
auto hi = lo;
    while (hi != movies.end() && hi->name.substr(0, prefix.size()) == prefix) {
        hi++;
    }
vector<Movie> matches;
    for (auto it = lo; it != hi; it++) matches.push_back(*it);
   sort(matches.begin(), matches.end(), MovieDatabase::ratingDescNameAsc);
for (int i = 0; i < (int)matches.size(); i++) {
        cout << matches[i].name << ", " << matches[i].rating << "\n";
    }
    cout << "\n"; 
ostringstream oss;
    oss << fixed << setprecision(1);
    oss << "Best movie with prefix " << prefix << " is: "
        << matches[0].name << " with rating " << matches[0].rating;
    bestLine = oss.str();

    return true;
}

void MovieDatabase::processPrefixFile(const string& prefixFilename) const {
  vector<string> bestLines;
    string prefix;
string bestLine;
if (queryPrefix(prefix, bestLine)) {
    bestLines.push_back(bestLine);
}
pin.close();
for (int i = 0; i < bestLines.size(); i++) {
    cout << bestLines[i] << "\n";
}
}
  






























