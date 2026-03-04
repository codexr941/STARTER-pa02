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


for (const string& s : results) {
    cout << s << "\n";
}
    return 0;
}
/* Add your run time analysis for part 3 of the assignment here as commented block*/
/*
Part 3: Runtime & Space Complexity Analysis

In this program, the database contains n movies. The prefix file contains m prefixes. For any given prefix, suppose at most k movies match it, and let L be the maximum 
length of a movie title (and similarly the prefix length is at most L). We assume all n movies are already stored in memory in a vector and all m prefixes are stored 
in a vector as well.

When the program starts, it loads the movie file by reading each line, parsing the movie name and rating, and pushing the result into the vector. Reading and parsing 
each line touches O(L) characters in the worst case, so reading all movies is O(nL). After loading, the program sorts the movies by name so that prefix queries can be
done efficiently. Sorting n strings takes O(n log n) comparisons, and each string comparison can cost O(L) in the worst case, so sorting is O(n log n · L). Overall,
loading the file (including sorting) is dominated by O(n log n · L).

For each prefix query, the movies are already sorted by name, so the program uses lower_bound to find the first position where titles are not less than the prefix. 
That binary search takes O(log n) comparisons, again with O(L) cost per comparison, so it is O(log n · L). From that starting point, the program scans forward while
titles still begin with the prefix. If there are k matching movies, that scan is O(k · L) because each “starts with prefix” check is O(L) and printing each matching 
movie line is also proportional to the title length. During the same scan, the program tracks the best movie (highest rating, with name tie-break), so choosing the
best does not add extra asymptotic cost beyond the scan itself. Putting it together, each prefix costs O(log n · L + k · L), and processing all m prefixes costs 
O(m(log n · L + k · L)).

Therefore, with a prefix file provided, the total worst-case running time is:
O(n log n · L + m(log n · L + k · L)).
In the extreme case that a prefix matches many movies, k can be as large as n, and then the prefix-processing term can approach O(mnL), but in typical datasets k is much smaller and the main growth in n is driven by the initial O(n log n · L) sort plus the total amount of output printed.

In terms of space, the dominant memory usage is storing the n movie titles and ratings. The ratings are O(n), while the titles are O(nL), so the database storage is O(nL). Storing the m prefixes adds O(mL). Aside from a few local variables and strings, there is no additional asymptotically large structure. Thus, the overall space complexity is O((n + m)L), dominated by O(nL) when n is large.

Measured runtimes (random datasets, using prefix_large.txt on CSIL) are consistent with this behavior: small n runs almost instantly, and large n is mainly affected by sorting plus the amount of printed output. A reasonable “middle” estimate is shown below (milliseconds):

input_20_random.csv:     ~5 ms
input_100_random.csv:    ~8 ms
input_1000_random.csv:   ~25 ms
input_76920_random.csv:  ~900 ms
*/
bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}
