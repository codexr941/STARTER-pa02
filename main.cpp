// Winter'24
// Instructor: Diba Mirza
// Student name: 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }
  
    MovieDatabase db;
    db.loadFromFile(argv[1]);
    
    if (argc == 2){
            db.printAllMovies();
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    string line;
    
  while (getline(prefixFile, line)) {
    if (!line.empty() && line.back() == '\r') line.pop_back();
    if (!line.empty())
        prefixes.push_back(line);
}
    

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    //cout << "No movies found with prefix "<<"<replace with prefix>" << endl;

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    //cout << "Best movie with prefix " << "<replace with prefix>" << " is: " << "replace with movie name" << " with rating " << std::fixed << std::setprecision(1) << "replace with movie rating" << endl;
vector<string> results;

for (const string& prefix : prefixes) {
    string bestLine;
    bool ok = db.queryPrefix(prefix, bestLine);

    if (ok) {
        // 这个 prefix 打印了列表，所以列表后要空一行
        cout << "\n";
        results.push_back(bestLine);
    } else {
        // 没有列表输出，所以阶段A不空行
        results.push_back("No movies found with prefix " + prefix);
    }
}

cout << "\n";

for (const string& s : results) {
    cout << s << "\n";
}
}
/* Add your run time analysis for part 3 of the assignment here as commented block*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}
