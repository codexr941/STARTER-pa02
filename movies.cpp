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
if (!m.name.empty() && m.name[0] == '"') {
    m.name = m.name.substr(1, m.name.size() - 2);
}
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

void MovieDatabase::sortByName() {
    sort(movies.begin(), movies.end(), nameLess);
}

void MovieDatabase::loadFromFile(const string& filename){
  movies.clear();
  ifstream fin(filename);   

    if (!fin.is_open()) {   
        cerr << "Error: cannot open file " << filename << endl;
        return;
    }
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
      cout << fixed << setprecision(1);
  for (int i = 0; i < (int)movies.size(); i++)
    cout << movies[i].name << ", " << movies[i].rating << "\n";
}

bool MovieDatabase::queryPrefix(const string& prefix, string& bestLine) const {
    auto lo = lower_bound(movies.begin(), movies.end(), prefix,
        [](const Movie& m, const string& s) { return m.name < s; });

    if (lo == movies.end() || lo->name.compare(0, prefix.size(), prefix) != 0) {
        return false;
    }

    auto hi = lo;
    while (hi != movies.end() && hi->name.compare(0, prefix.size(), prefix) == 0) {
        hi++;
    }

    cout << fixed << setprecision(1);
    const Movie* best = &(*lo);

    for (auto it = lo; it != hi; ++it) {
        cout << it->name << ", " << it->rating << "\n";
        if (it->rating > best->rating ||
            (it->rating == best->rating && it->name < best->name)) {
            best = &(*it);
        }
    }

    ostringstream oss;
    oss << fixed << setprecision(1);
    oss << "Best movie with prefix " << prefix << " is: "
        << best->name << " with rating " << best->rating;
    bestLine = oss.str();

    return true;
}

void MovieDatabase::processPrefixFile(const string& prefixFilename) const {
  ifstream pin(prefixFilename);
    if (!pin.is_open()) return;

    vector<string> bestLines;
    string prefix;

    while (getline(pin, prefix)) {
        if (!prefix.empty() && prefix.back() == '\r') prefix.pop_back();

        string bestLine;
        if (queryPrefix(prefix, bestLine)) {
            bestLines.push_back(bestLine);
        }
    }
    pin.close();

    for (int i = 0; i < (int)bestLines.size(); i++) {
        cout << bestLines[i] << "\n";
    }
}

  






























